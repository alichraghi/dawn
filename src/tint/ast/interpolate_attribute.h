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

#ifndef SRC_TINT_AST_INTERPOLATE_ATTRIBUTE_H_
#define SRC_TINT_AST_INTERPOLATE_ATTRIBUTE_H_

#include <string>

#include "src/tint/ast/attribute.h"

// Forward declarations
namespace tint::ast {
class Expression;
}

namespace tint::ast {

/// An interpolate attribute
class InterpolateAttribute final : public utils::Castable<InterpolateAttribute, Attribute> {
  public:
    /// Create an interpolate attribute.
    /// @param pid the identifier of the program that owns this node
    /// @param nid the unique node identifier
    /// @param src the source of this node
    /// @param type the interpolation type
    /// @param sampling the interpolation sampling
    InterpolateAttribute(ProgramID pid,
                         NodeID nid,
                         const Source& src,
                         const Expression* type,
                         const Expression* sampling);
    ~InterpolateAttribute() override;

    /// @returns the WGSL name for the attribute
    std::string Name() const override;

    /// Clones this node and all transitive child nodes using the `CloneContext`
    /// `ctx`.
    /// @param ctx the clone context
    /// @return the newly cloned node
    const InterpolateAttribute* Clone(CloneContext* ctx) const override;

    /// The interpolation type
    const Expression* const type;

    /// The interpolation sampling
    const Expression* const sampling;
};

}  // namespace tint::ast

#endif  // SRC_TINT_AST_INTERPOLATE_ATTRIBUTE_H_
