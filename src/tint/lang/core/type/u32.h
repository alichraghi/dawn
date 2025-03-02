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

#ifndef SRC_TINT_LANG_CORE_TYPE_U32_H_
#define SRC_TINT_LANG_CORE_TYPE_U32_H_

#include <string>

#include "src/tint/lang/core/type/numeric_scalar.h"

namespace tint::type {

/// A unsigned int 32 type.
class U32 final : public Castable<U32, NumericScalar> {
  public:
    /// Constructor
    U32();

    /// Destructor
    ~U32() override;

    /// @returns the name for this type that closely resembles how it would be
    /// declared in WGSL.
    std::string FriendlyName() const override;

    /// @returns the size in bytes of the type.
    uint32_t Size() const override;

    /// @returns the alignment in bytes of the type.
    uint32_t Align() const override;

    /// @param ctx the clone context
    /// @returns a clone of this type
    U32* Clone(CloneContext& ctx) const override;
};

}  // namespace tint::type

#endif  // SRC_TINT_LANG_CORE_TYPE_U32_H_
