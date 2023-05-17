// Copyright 2023 The Tint Authors.
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

#include "src/tint/writer/spirv/test_helper_ir.h"

using namespace tint::number_suffixes;  // NOLINT

namespace tint::writer::spirv {
namespace {

TEST_F(SpvGeneratorImplTest, If_TrueEmpty_FalseEmpty) {
    auto* func = b.CreateFunction(mod.symbols.Register("foo"), mod.types.Get<type::Void>());

    auto* i = b.CreateIf(b.Constant(true));
    b.Branch(i->true_.target->As<ir::Block>(), i->merge.target);
    b.Branch(i->false_.target->As<ir::Block>(), i->merge.target);
    b.Branch(i->merge.target->As<ir::Block>(), func->end_target);

    b.Branch(func->start_target, i);

    generator_.EmitFunction(func);
    EXPECT_EQ(DumpModule(generator_.Module()), R"(OpName %1 "foo"
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%7 = OpTypeBool
%6 = OpConstantTrue %7
%1 = OpFunction %2 None %3
%4 = OpLabel
OpSelectionMerge %5 None
OpBranchConditional %6 %5 %5
%5 = OpLabel
OpReturn
OpFunctionEnd
)");
}

TEST_F(SpvGeneratorImplTest, If_FalseEmpty) {
    auto* func = b.CreateFunction(mod.symbols.Register("foo"), mod.types.Get<type::Void>());

    auto* i = b.CreateIf(b.Constant(true));
    b.Branch(i->false_.target->As<ir::Block>(), i->merge.target);
    b.Branch(i->merge.target->As<ir::Block>(), func->end_target);

    auto* true_block = i->true_.target->As<ir::Block>();
    true_block->instructions.Push(
        b.Add(mod.types.Get<type::I32>(), b.Constant(1_i), b.Constant(1_i)));
    b.Branch(true_block, i->merge.target);

    b.Branch(func->start_target, i);

    generator_.EmitFunction(func);
    EXPECT_EQ(DumpModule(generator_.Module()), R"(OpName %1 "foo"
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%8 = OpTypeBool
%7 = OpConstantTrue %8
%10 = OpTypeInt 32 1
%11 = OpConstant %10 1
%1 = OpFunction %2 None %3
%4 = OpLabel
OpSelectionMerge %5 None
OpBranchConditional %7 %6 %5
%6 = OpLabel
%9 = OpIAdd %10 %11 %11
OpBranch %5
%5 = OpLabel
OpReturn
OpFunctionEnd
)");
}

TEST_F(SpvGeneratorImplTest, If_TrueEmpty) {
    auto* func = b.CreateFunction(mod.symbols.Register("foo"), mod.types.Get<type::Void>());

    auto* i = b.CreateIf(b.Constant(true));
    b.Branch(i->true_.target->As<ir::Block>(), i->merge.target);
    b.Branch(i->merge.target->As<ir::Block>(), func->end_target);

    auto* false_block = i->false_.target->As<ir::Block>();
    false_block->instructions.Push(
        b.Add(mod.types.Get<type::I32>(), b.Constant(1_i), b.Constant(1_i)));
    b.Branch(false_block, i->merge.target);

    b.Branch(func->start_target, i);

    generator_.EmitFunction(func);
    EXPECT_EQ(DumpModule(generator_.Module()), R"(OpName %1 "foo"
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%8 = OpTypeBool
%7 = OpConstantTrue %8
%10 = OpTypeInt 32 1
%11 = OpConstant %10 1
%1 = OpFunction %2 None %3
%4 = OpLabel
OpSelectionMerge %5 None
OpBranchConditional %7 %5 %6
%6 = OpLabel
%9 = OpIAdd %10 %11 %11
OpBranch %5
%5 = OpLabel
OpReturn
OpFunctionEnd
)");
}

TEST_F(SpvGeneratorImplTest, If_BothBranchesReturn) {
    auto* func = b.CreateFunction(mod.symbols.Register("foo"), mod.types.Get<type::Void>());

    auto* i = b.CreateIf(b.Constant(true));
    b.Branch(i->true_.target->As<ir::Block>(), func->end_target);
    b.Branch(i->false_.target->As<ir::Block>(), func->end_target);
    i->merge.target->As<ir::Block>()->branch.target = nullptr;

    b.Branch(func->start_target, i);

    generator_.EmitFunction(func);
    EXPECT_EQ(DumpModule(generator_.Module()), R"(OpName %1 "foo"
%2 = OpTypeVoid
%3 = OpTypeFunction %2
%9 = OpTypeBool
%8 = OpConstantTrue %9
%1 = OpFunction %2 None %3
%4 = OpLabel
OpSelectionMerge %5 None
OpBranchConditional %8 %6 %7
%6 = OpLabel
OpReturn
%7 = OpLabel
OpReturn
%5 = OpLabel
OpUnreachable
OpFunctionEnd
)");
}

}  // namespace
}  // namespace tint::writer::spirv
