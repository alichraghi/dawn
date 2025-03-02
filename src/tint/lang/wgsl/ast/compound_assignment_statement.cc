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

#include "src/tint/lang/wgsl/ast/compound_assignment_statement.h"

#include "src/tint/lang/wgsl/ast/builder.h"
#include "src/tint/lang/wgsl/ast/clone_context.h"

TINT_INSTANTIATE_TYPEINFO(tint::ast::CompoundAssignmentStatement);

namespace tint::ast {

CompoundAssignmentStatement::CompoundAssignmentStatement(GenerationID pid,
                                                         NodeID nid,
                                                         const Source& src,
                                                         const Expression* l,
                                                         const Expression* r,
                                                         BinaryOp o)
    : Base(pid, nid, src), lhs(l), rhs(r), op(o) {
    TINT_ASSERT(lhs);
    TINT_ASSERT_GENERATION_IDS_EQUAL_IF_VALID(lhs, generation_id);
    TINT_ASSERT(rhs);
    TINT_ASSERT_GENERATION_IDS_EQUAL_IF_VALID(rhs, generation_id);
}

CompoundAssignmentStatement::~CompoundAssignmentStatement() = default;

const CompoundAssignmentStatement* CompoundAssignmentStatement::Clone(CloneContext& ctx) const {
    // Clone arguments outside of create() call to have deterministic ordering
    auto src = ctx.Clone(source);
    auto* l = ctx.Clone(lhs);
    auto* r = ctx.Clone(rhs);
    return ctx.dst->create<CompoundAssignmentStatement>(src, l, r, op);
}

}  // namespace tint::ast
