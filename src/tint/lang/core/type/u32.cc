// Copyright 2022 The Tint Authors.
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

#include "src/tint/lang/core/type/u32.h"

#include "src/tint/lang/core/type/manager.h"

TINT_INSTANTIATE_TYPEINFO(tint::type::U32);

namespace tint::type {

U32::U32()
    : Base(static_cast<size_t>(tint::TypeInfo::Of<U32>().full_hashcode),
           type::Flags{
               Flag::kConstructable,
               Flag::kCreationFixedFootprint,
               Flag::kFixedFootprint,
           }) {}

U32::~U32() = default;

std::string U32::FriendlyName() const {
    return "u32";
}

uint32_t U32::Size() const {
    return 4;
}

uint32_t U32::Align() const {
    return 4;
}

U32* U32::Clone(CloneContext& ctx) const {
    return ctx.dst.mgr->Get<U32>();
}

}  // namespace tint::type
