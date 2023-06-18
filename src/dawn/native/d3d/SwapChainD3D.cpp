// Copyright 2023 The Dawn Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "dawn/native/d3d/SwapChainD3D.h"

#include <windows.ui.xaml.media.dxinterop.h>

#include <utility>

#include "dawn/native/Surface.h"
#include "dawn/native/d3d/D3DError.h"
#include "dawn/native/d3d/DeviceD3D.h"
#include "dawn/native/d3d/Forward.h"
#include "dawn/native/d3d/UtilsD3D.h"

namespace dawn::native::d3d {
namespace {

uint32_t PresentModeToBufferCount(wgpu::PresentMode mode) {
    switch (mode) {
        case wgpu::PresentMode::Immediate:
        case wgpu::PresentMode::Fifo:
            return 2;
        case wgpu::PresentMode::Mailbox:
            return 3;
    }
}

uint32_t PresentModeToSwapInterval(wgpu::PresentMode mode) {
    switch (mode) {
        case wgpu::PresentMode::Immediate:
        case wgpu::PresentMode::Mailbox:
            return 0;
        case wgpu::PresentMode::Fifo:
            return 1;
    }
}

UINT PresentModeToSwapChainFlags(wgpu::PresentMode mode) {
    UINT flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (mode == wgpu::PresentMode::Immediate) {
        flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    }

    return flags;
}

DXGI_USAGE ToDXGIUsage(wgpu::TextureUsage usage) {
    DXGI_USAGE dxgiUsage = DXGI_CPU_ACCESS_NONE;
    if (usage & wgpu::TextureUsage::TextureBinding) {
        dxgiUsage |= DXGI_USAGE_SHADER_INPUT;
    }
    if (usage & wgpu::TextureUsage::StorageBinding) {
        dxgiUsage |= DXGI_USAGE_UNORDERED_ACCESS;
    }
    if (usage & wgpu::TextureUsage::RenderAttachment) {
        dxgiUsage |= DXGI_USAGE_RENDER_TARGET_OUTPUT;
    }
    return dxgiUsage;
}

}  // namespace

SwapChain::~SwapChain() = default;

void SwapChain::DestroyImpl() {
    SwapChainBase::DestroyImpl();
    DetachFromSurface();
}

// Initializes the swapchain on the surface. Note that `previousSwapChain` may or may not be
// nullptr. If it is not nullptr it means that it is the swapchain previously in use on the
// surface and that we have a chance to reuse it's underlying IDXGISwapChain and "buffers".
MaybeError SwapChain::Initialize(SwapChainBase* previousSwapChain) {
    ASSERT(GetSurface()->GetType() == Surface::Type::WindowsHWND);

    // Precompute the configuration parameters we want for the DXGI swapchain.
    mConfig.bufferCount = PresentModeToBufferCount(GetPresentMode());
    mConfig.format = d3d::DXGITextureFormat(GetFormat());
    mConfig.swapChainFlags = PresentModeToSwapChainFlags(GetPresentMode());
    mConfig.usage = ToDXGIUsage(GetUsage());

    // There is no previous swapchain so we can create one directly and don't have anything else
    // to do.
    if (previousSwapChain == nullptr) {
        return InitializeSwapChainFromScratch();
    }

    // TODO(crbug.com/dawn/269): figure out what should happen when surfaces are used by
    // multiple backends one after the other. It probably needs to block until the backend
    // and GPU are completely finished with the previous swapchain.
    DAWN_INVALID_IF(previousSwapChain->GetBackendType() != GetBackendType(),
                    "D3D SwapChain cannot switch backend types from %s to %s.",
                    previousSwapChain->GetBackendType(), GetBackendType());

    SwapChain* previousD3DSwapChain = ToBackend(previousSwapChain);

    // TODO(crbug.com/dawn/269): Figure out switching an HWND between devices, it might
    // require just losing the reference to the swapchain, but might also need to wait for
    // all previous operations to complete.
    DAWN_INVALID_IF(GetDevice() != previousSwapChain->GetDevice(),
                    "D3D SwapChain cannot switch between D3D Devices");

    // The previous swapchain is on the same device so we want to reuse it but it is still not
    // always possible. Because DXGI requires that a new swapchain be created if the
    // DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING flag is changed.
    bool canReuseSwapChain =
        ((mConfig.swapChainFlags ^ previousD3DSwapChain->mConfig.swapChainFlags) &
         DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING) == 0;

    // We can't reuse the previous swapchain, so we destroy it and wait for all of its reference
    // to be forgotten (otherwise DXGI complains that there are outstanding references).
    if (!canReuseSwapChain) {
        DAWN_TRY(previousD3DSwapChain->DetachAndWaitForDeallocation());
        return InitializeSwapChainFromScratch();
    }

    // After all this we know we can reuse the swapchain, see if it is possible to also reuse
    // the buffers.
    mDXGISwapChain = std::move(previousD3DSwapChain->mDXGISwapChain);

    bool canReuseBuffers = GetWidth() == previousSwapChain->GetWidth() &&
                           GetHeight() == previousSwapChain->GetHeight() &&
                           GetFormat() == previousSwapChain->GetFormat() &&
                           GetPresentMode() == previousSwapChain->GetPresentMode();
    if (canReuseBuffers) {
        this->ReuseBuffers(previousSwapChain);
        return {};
    }

    // We can't reuse the buffers so we need to resize, IDXGSwapChain->ResizeBuffers requires
    // that all references to buffers are lost before it is called. Contrary to D3D11, the
    // application is responsible for keeping references to the buffers until the GPU is done
    // using them so we have no choice but to synchrounously wait for all operations to complete
    // on the previous swapchain and then lose references to its buffers.
    if (GetBackendType() == wgpu::BackendType::D3D12) {
        DAWN_TRY(previousD3DSwapChain->DetachAndWaitForDeallocation());
    } else {
        previousD3DSwapChain->DetachFromSurface();
    }
    DAWN_TRY(
        CheckHRESULT(mDXGISwapChain->ResizeBuffers(mConfig.bufferCount, GetWidth(), GetHeight(),
                                                   mConfig.format, mConfig.swapChainFlags),
                     "IDXGISwapChain::ResizeBuffer"));
    return CollectSwapChainBuffers();
}

MaybeError SwapChain::InitializeSwapChainFromScratch() {
    ASSERT(mDXGISwapChain == nullptr);

    Device* device = ToBackend(GetDevice());

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = GetWidth();
    swapChainDesc.Height = GetHeight();
    swapChainDesc.Format = mConfig.format;
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = mConfig.usage;
    swapChainDesc.BufferCount = mConfig.bufferCount;
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    swapChainDesc.Flags = mConfig.swapChainFlags;

    ComPtr<IDXGIFactory2> factory2 = nullptr;
    DAWN_TRY(CheckHRESULT(device->GetFactory()->QueryInterface(IID_PPV_ARGS(&factory2)),
                          "Getting IDXGIFactory2"));

    ComPtr<IDXGISwapChain1> swapChain1;
    switch (GetSurface()->GetType()) {
        case Surface::Type::WindowsHWND: {
            DAWN_TRY(CheckHRESULT(
                factory2->CreateSwapChainForHwnd(GetD3DDeviceForCreatingSwapChain(),
                                                 static_cast<HWND>(GetSurface()->GetHWND()),
                                                 &swapChainDesc, nullptr, nullptr, &swapChain1),
                "Creating the IDXGISwapChain1"));
            break;
        }
        case Surface::Type::WindowsCoreWindow: {
            DAWN_TRY(CheckHRESULT(
                factory2->CreateSwapChainForCoreWindow(GetD3DDeviceForCreatingSwapChain(),
                                                       GetSurface()->GetCoreWindow(),
                                                       &swapChainDesc, nullptr, &swapChain1),
                "Creating the IDXGISwapChain1"));
            break;
        }
        case Surface::Type::WindowsSwapChainPanel: {
            DAWN_TRY(CheckHRESULT(
                factory2->CreateSwapChainForComposition(GetD3DDeviceForCreatingSwapChain(),
                                                        &swapChainDesc, nullptr, &swapChain1),
                "Creating the IDXGISwapChain1"));
            ComPtr<ISwapChainPanelNative> swapChainPanelNative;
            DAWN_TRY(CheckHRESULT(GetSurface()->GetSwapChainPanel()->QueryInterface(
                                      IID_PPV_ARGS(&swapChainPanelNative)),
                                  "Getting ISwapChainPanelNative"));
            DAWN_TRY(CheckHRESULT(swapChainPanelNative->SetSwapChain(swapChain1.Get()),
                                  "Setting SwapChain"));
            break;
        }
        default:
            UNREACHABLE();
    }

    DAWN_TRY(CheckHRESULT(swapChain1.As(&mDXGISwapChain), "Gettting IDXGISwapChain1"));

    return CollectSwapChainBuffers();
}

MaybeError SwapChain::PresentDXGISwapChain() {
    // Do the actual present. DXGI_STATUS_OCCLUDED is a valid return value that's just a
    // message to the application that it could stop rendering.
    HRESULT presentResult = mDXGISwapChain->Present(PresentModeToSwapInterval(GetPresentMode()), 0);
    if (presentResult != DXGI_STATUS_OCCLUDED) {
        DAWN_TRY(CheckHRESULT(presentResult, "IDXGISwapChain::Present"));
    }

    return {};
}

void SwapChain::ReleaseDXGISwapChain() {
    mDXGISwapChain = nullptr;
}

IDXGISwapChain3* SwapChain::GetDXGISwapChain() const {
    return mDXGISwapChain.Get();
}

const SwapChain::Config& SwapChain::GetConfig() const {
    return mConfig;
}

}  // namespace dawn::native::d3d
