// Copyright 2022 The Dawn Authors
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

#include <numeric>
#include <string>
#include <vector>

#include "dawn/tests/DawnTest.h"
#include "dawn/utils/ComboRenderPipelineDescriptor.h"
#include "dawn/utils/WGPUHelpers.h"

// The compute shader workgroup size is settled at compute pipeline creation time.
// The validation code in dawn is in each backend (not including Null backend) thus this test needs
// to be as part of a dawn_end2end_tests instead of the dawn_unittests
// TODO(dawn:1504): Add support for GL backend.
class WorkgroupSizeValidationTest : public DawnTest {
  public:
    wgpu::ShaderModule SetUpShaderWithValidDefaultValueConstants() {
        return utils::CreateShaderModule(device, R"(
override x: u32 = 1u;
override y: u32 = 1u;
override z: u32 = 1u;

@compute @workgroup_size(x, y, z) fn main() {
    _ = 0u;
})");
    }

    wgpu::ShaderModule SetUpShaderWithZeroDefaultValueConstants() {
        return utils::CreateShaderModule(device, R"(
override x: u32 = 0u;
override y: u32 = 0u;
override z: u32 = 0u;

@compute @workgroup_size(x, y, z) fn main() {
    _ = 0u;
})");
    }

    wgpu::ShaderModule SetUpShaderWithOutOfLimitsDefaultValueConstants() {
        return utils::CreateShaderModule(device, R"(
override x: u32 = 1u;
override y: u32 = 1u;
override z: u32 = 9999u;

@compute @workgroup_size(x, y, z) fn main() {
    _ = 0u;
})");
    }

    wgpu::ShaderModule SetUpShaderWithUninitializedConstants() {
        return utils::CreateShaderModule(device, R"(
override x: u32;
override y: u32;
override z: u32;

@compute @workgroup_size(x, y, z) fn main() {
    _ = 0u;
})");
    }

    wgpu::ShaderModule SetUpShaderWithPartialConstants() {
        return utils::CreateShaderModule(device, R"(
override x: u32;

@compute @workgroup_size(x, 1, 1) fn main() {
    _ = 0u;
})");
    }

    void TestCreatePipeline(const wgpu::ShaderModule& module) {
        wgpu::ComputePipelineDescriptor csDesc;
        csDesc.compute.module = module;
        csDesc.compute.entryPoint = "main";
        csDesc.compute.constants = nullptr;
        csDesc.compute.constantCount = 0;
        wgpu::ComputePipeline pipeline = device.CreateComputePipeline(&csDesc);
    }

    void TestCreatePipeline(const wgpu::ShaderModule& module,
                            const std::vector<wgpu::ConstantEntry>& constants) {
        wgpu::ComputePipelineDescriptor csDesc;
        csDesc.compute.module = module;
        csDesc.compute.entryPoint = "main";
        csDesc.compute.constants = constants.data();
        csDesc.compute.constantCount = constants.size();
        wgpu::ComputePipeline pipeline = device.CreateComputePipeline(&csDesc);
    }

    void TestInitializedWithZero(const wgpu::ShaderModule& module) {
        std::vector<wgpu::ConstantEntry> constants{
            {nullptr, "x", 0}, {nullptr, "y", 0}, {nullptr, "z", 0}};
        TestCreatePipeline(module, constants);
    }

    void TestInitializedWithOutOfLimitValue(const wgpu::ShaderModule& module) {
        std::vector<wgpu::ConstantEntry> constants{
            {nullptr, "x",
             static_cast<double>(GetSupportedLimits().limits.maxComputeWorkgroupSizeX + 1)},
            {nullptr, "y", 1},
            {nullptr, "z", 1}};
        TestCreatePipeline(module, constants);
    }

    void TestInitializedWithValidValue(const wgpu::ShaderModule& module) {
        std::vector<wgpu::ConstantEntry> constants{
            {nullptr, "x", 4}, {nullptr, "y", 4}, {nullptr, "z", 4}};
        TestCreatePipeline(module, constants);
    }

    void TestInitializedPartially(const wgpu::ShaderModule& module) {
        std::vector<wgpu::ConstantEntry> constants{{nullptr, "y", 4}};
        TestCreatePipeline(module, constants);
    }

    wgpu::Buffer buffer;
};

// Test workgroup size validation with fixed values.
TEST_P(WorkgroupSizeValidationTest, WithFixedValues) {
    auto CheckShaderWithWorkgroupSize = [this](bool success, uint32_t x, uint32_t y, uint32_t z) {
        std::ostringstream ss;
        ss << "@compute @workgroup_size(" << x << "," << y << "," << z << ") fn main() {}";

        wgpu::ComputePipelineDescriptor desc;
        desc.compute.entryPoint = "main";
        desc.compute.module = utils::CreateShaderModule(device, ss.str().c_str());

        if (success) {
            device.CreateComputePipeline(&desc);
        } else {
            ASSERT_DEVICE_ERROR(device.CreateComputePipeline(&desc));
        }
    };

    wgpu::Limits supportedLimits = GetSupportedLimits().limits;

    CheckShaderWithWorkgroupSize(true, 1, 1, 1);
    CheckShaderWithWorkgroupSize(true, supportedLimits.maxComputeWorkgroupSizeX, 1, 1);
    CheckShaderWithWorkgroupSize(true, 1, supportedLimits.maxComputeWorkgroupSizeY, 1);
    CheckShaderWithWorkgroupSize(true, 1, 1, supportedLimits.maxComputeWorkgroupSizeZ);

    CheckShaderWithWorkgroupSize(false, supportedLimits.maxComputeWorkgroupSizeX + 1, 1, 1);
    CheckShaderWithWorkgroupSize(false, 1, supportedLimits.maxComputeWorkgroupSizeY + 1, 1);
    CheckShaderWithWorkgroupSize(false, 1, 1, supportedLimits.maxComputeWorkgroupSizeZ + 1);

    // No individual dimension exceeds its limit, but the combined size should definitely exceed the
    // total invocation limit.
    DAWN_ASSERT(supportedLimits.maxComputeWorkgroupSizeX *
                    supportedLimits.maxComputeWorkgroupSizeY *
                    supportedLimits.maxComputeWorkgroupSizeZ >
                supportedLimits.maxComputeInvocationsPerWorkgroup);
    CheckShaderWithWorkgroupSize(false, supportedLimits.maxComputeWorkgroupSizeX,
                                 supportedLimits.maxComputeWorkgroupSizeY,
                                 supportedLimits.maxComputeWorkgroupSizeZ);
}

// Test workgroup size validation with fixed values (storage size limits validation).
TEST_P(WorkgroupSizeValidationTest, WithFixedValuesStorageSizeLimits) {
    wgpu::Limits supportedLimits = GetSupportedLimits().limits;

    constexpr uint32_t kVec4Size = 16;
    const uint32_t maxVec4Count = supportedLimits.maxComputeWorkgroupStorageSize / kVec4Size;
    constexpr uint32_t kMat4Size = 64;
    const uint32_t maxMat4Count = supportedLimits.maxComputeWorkgroupStorageSize / kMat4Size;

    auto CheckPipelineWithWorkgroupStorage = [this](bool success, uint32_t vec4_count,
                                                    uint32_t mat4_count) {
        std::ostringstream ss;
        std::ostringstream body;
        if (vec4_count > 0) {
            ss << "var<workgroup> vec4_data: array<vec4<f32>, " << vec4_count << ">;";
            body << "_ = vec4_data;";
        }
        if (mat4_count > 0) {
            ss << "var<workgroup> mat4_data: array<mat4x4<f32>, " << mat4_count << ">;";
            body << "_ = mat4_data;";
        }
        ss << "@compute @workgroup_size(1) fn main() { " << body.str() << " }";

        wgpu::ComputePipelineDescriptor desc;
        desc.compute.entryPoint = "main";
        desc.compute.module = utils::CreateShaderModule(device, ss.str().c_str());

        if (success) {
            device.CreateComputePipeline(&desc);
        } else {
            ASSERT_DEVICE_ERROR(device.CreateComputePipeline(&desc));
        }
    };

    CheckPipelineWithWorkgroupStorage(true, 1, 1);
    CheckPipelineWithWorkgroupStorage(true, maxVec4Count, 0);
    CheckPipelineWithWorkgroupStorage(true, 0, maxMat4Count);
    CheckPipelineWithWorkgroupStorage(true, maxVec4Count - 4, 1);
    CheckPipelineWithWorkgroupStorage(true, 4, maxMat4Count - 1);

    CheckPipelineWithWorkgroupStorage(false, maxVec4Count + 1, 0);
    CheckPipelineWithWorkgroupStorage(false, maxVec4Count - 3, 1);
    CheckPipelineWithWorkgroupStorage(false, 0, maxMat4Count + 1);
    CheckPipelineWithWorkgroupStorage(false, 4, maxMat4Count);
}

// Test workgroup size validation with valid overrides default values.
TEST_P(WorkgroupSizeValidationTest, OverridesWithValidDefault) {
    wgpu::ShaderModule module = SetUpShaderWithValidDefaultValueConstants();
    {
        // Valid default
        TestCreatePipeline(module);
    }
    {
        // Error: invalid value (zero)
        ASSERT_DEVICE_ERROR(TestInitializedWithZero(module));
    }
    {
        // Error: invalid value (out of device limits)
        ASSERT_DEVICE_ERROR(TestInitializedWithOutOfLimitValue(module));
    }
    {
        // Valid: initialized partially
        TestInitializedPartially(module);
    }
    {
        // Valid
        TestInitializedWithValidValue(module);
    }
}

// Test workgroup size validation with zero as the overrides default values.
TEST_P(WorkgroupSizeValidationTest, OverridesWithZeroDefault) {
    // Error: zero is detected as invalid at shader creation time
    ASSERT_DEVICE_ERROR(SetUpShaderWithZeroDefaultValueConstants());
}

// Test workgroup size validation with out-of-limits overrides default values.
TEST_P(WorkgroupSizeValidationTest, OverridesWithOutOfLimitsDefault) {
    wgpu::ShaderModule module = SetUpShaderWithOutOfLimitsDefaultValueConstants();
    {
        // Error: invalid default
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module));
    }
    {
        // Error: invalid value (zero)
        ASSERT_DEVICE_ERROR(TestInitializedWithZero(module));
    }
    {
        // Error: invalid value (out of device limits)
        ASSERT_DEVICE_ERROR(TestInitializedWithOutOfLimitValue(module));
    }
    {
        // Error: initialized partially
        ASSERT_DEVICE_ERROR(TestInitializedPartially(module));
    }
    {
        // Valid
        TestInitializedWithValidValue(module);
    }
}

// Test workgroup size validation without overrides default values specified.
TEST_P(WorkgroupSizeValidationTest, OverridesWithUninitialized) {
    wgpu::ShaderModule module = SetUpShaderWithUninitializedConstants();
    {
        // Error: uninitialized
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module));
    }
    {
        // Error: invalid value (zero)
        ASSERT_DEVICE_ERROR(TestInitializedWithZero(module));
    }
    {
        // Error: invalid value (out of device limits)
        ASSERT_DEVICE_ERROR(TestInitializedWithOutOfLimitValue(module));
    }
    {
        // Error: initialized partially
        ASSERT_DEVICE_ERROR(TestInitializedPartially(module));
    }
    {
        // Valid
        TestInitializedWithValidValue(module);
    }
}

// Test workgroup size validation with only partial dimensions are overrides.
TEST_P(WorkgroupSizeValidationTest, PartialOverrides) {
    wgpu::ShaderModule module = SetUpShaderWithPartialConstants();
    {
        // Error: uninitialized
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module));
    }
    {
        // Error: invalid value (zero)
        std::vector<wgpu::ConstantEntry> constants{{nullptr, "x", 0}};
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module, constants));
    }
    {
        // Error: invalid value (out of device limits)
        std::vector<wgpu::ConstantEntry> constants{
            {nullptr, "x",
             static_cast<double>(GetSupportedLimits().limits.maxComputeWorkgroupSizeX + 1)}};
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module, constants));
    }
    {
        // Valid
        std::vector<wgpu::ConstantEntry> constants{{nullptr, "x", 16}};
        TestCreatePipeline(module, constants);
    }
}

// Test workgroup size validation after being overrided with invalid values.
TEST_P(WorkgroupSizeValidationTest, ValidationAfterOverride) {
    wgpu::ShaderModule module = SetUpShaderWithUninitializedConstants();
    wgpu::Limits supportedLimits = GetSupportedLimits().limits;
    {
        // Error: exceed maxComputeWorkgroupSizeZ
        std::vector<wgpu::ConstantEntry> constants{
            {nullptr, "x", 1},
            {nullptr, "y", 1},
            {nullptr, "z", static_cast<double>(supportedLimits.maxComputeWorkgroupSizeZ + 1)}};
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module, constants));
    }
    {
        // Error: exceed maxComputeInvocationsPerWorkgroup
        DAWN_ASSERT(supportedLimits.maxComputeWorkgroupSizeX *
                        supportedLimits.maxComputeWorkgroupSizeY *
                        supportedLimits.maxComputeWorkgroupSizeZ >
                    supportedLimits.maxComputeInvocationsPerWorkgroup);
        std::vector<wgpu::ConstantEntry> constants{
            {nullptr, "x", static_cast<double>(supportedLimits.maxComputeWorkgroupSizeX)},
            {nullptr, "y", static_cast<double>(supportedLimits.maxComputeWorkgroupSizeY)},
            {nullptr, "z", static_cast<double>(supportedLimits.maxComputeWorkgroupSizeZ)}};
        ASSERT_DEVICE_ERROR(TestCreatePipeline(module, constants));
    }
}

// Test workgroup size validation after being overrided with invalid values (storage size limits
// validation).
// TODO(tint:1660): re-enable after override can be used as array size.
TEST_P(WorkgroupSizeValidationTest, DISABLED_ValidationAfterOverrideStorageSize) {
    wgpu::Limits supportedLimits = GetSupportedLimits().limits;

    constexpr uint32_t kVec4Size = 16;
    const uint32_t maxVec4Count = supportedLimits.maxComputeWorkgroupStorageSize / kVec4Size;
    constexpr uint32_t kMat4Size = 64;
    const uint32_t maxMat4Count = supportedLimits.maxComputeWorkgroupStorageSize / kMat4Size;

    auto CheckPipelineWithWorkgroupStorage = [this](bool success, uint32_t vec4_count,
                                                    uint32_t mat4_count) {
        std::ostringstream ss;
        std::ostringstream body;
        ss << "override a: u32;";
        ss << "override b: u32;";
        if (vec4_count > 0) {
            ss << "var<workgroup> vec4_data: array<vec4<f32>, a>;";
            body << "_ = vec4_data;";
        }
        if (mat4_count > 0) {
            ss << "var<workgroup> mat4_data: array<mat4x4<f32>, b>;";
            body << "_ = mat4_data;";
        }
        ss << "@compute @workgroup_size(1) fn main() { " << body.str() << " }";

        wgpu::ComputePipelineDescriptor desc;
        desc.compute.entryPoint = "main";
        desc.compute.module = utils::CreateShaderModule(device, ss.str().c_str());

        std::vector<wgpu::ConstantEntry> constants{{nullptr, "a", static_cast<double>(vec4_count)},
                                                   {nullptr, "b", static_cast<double>(mat4_count)}};
        desc.compute.constants = constants.data();
        desc.compute.constantCount = constants.size();

        if (success) {
            device.CreateComputePipeline(&desc);
        } else {
            ASSERT_DEVICE_ERROR(device.CreateComputePipeline(&desc));
        }
    };

    CheckPipelineWithWorkgroupStorage(false, maxVec4Count + 1, 0);
    CheckPipelineWithWorkgroupStorage(false, 0, maxMat4Count + 1);
}

DAWN_INSTANTIATE_TEST(WorkgroupSizeValidationTest, D3D12Backend(), MetalBackend(), VulkanBackend());
