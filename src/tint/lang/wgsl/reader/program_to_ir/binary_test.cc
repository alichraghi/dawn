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

#include "gmock/gmock.h"
#include "src/tint/lang/core/constant/scalar.h"
#include "src/tint/lang/wgsl/ast/case_selector.h"
#include "src/tint/lang/wgsl/ast/int_literal_expression.h"
#include "src/tint/lang/wgsl/helpers/ir_program_test.h"

namespace tint::wgsl::reader {
namespace {

using namespace tint::number_suffixes;  // NOLINT

using ProgramToIRBinaryTest = helpers::IRProgramTest;

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Add) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Add(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = add %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Increment) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = Increment("v1");
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = add %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundAdd) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kAdd);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = add %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Subtract) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Sub(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = sub %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Decrement) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.i32());
    auto* expr = Decrement("v1");
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, i32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:i32 = load %v1
    %4:i32 = sub %3, 1i
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundSubtract) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kSubtract);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = sub %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Multiply) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Mul(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = mul %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundMultiply) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kMultiply);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = mul %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Div) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Div(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = div %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundDiv) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kDivide);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = div %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Modulo) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Mod(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = mod %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundModulo) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kModulo);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = mod %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_And) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = And(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = and %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundAnd) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.bool_());
    auto* expr = CompoundAssign("v1", false, ast::BinaryOp::kAnd);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, bool, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:bool = load %v1
    %4:bool = and %3, false
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Or) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Or(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = or %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundOr) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.bool_());
    auto* expr = CompoundAssign("v1", false, ast::BinaryOp::kOr);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, bool, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:bool = load %v1
    %4:bool = or %3, false
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Xor) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Xor(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = xor %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundXor) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kXor);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = xor %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_LogicalAnd) {
    Func("my_func", tint::Empty, ty.bool_(), Vector{Return(true)});
    auto* let = Let("logical_and", LogicalAnd(Call("my_func"), false));
    auto* expr = If(let, Block());
    WrapInFunction(let, expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():bool -> %b1 {
  %b1 = block {
    ret true
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:bool = call %my_func
    %logical_and:bool = if %3 [t: %b3, f: %b4] {  # if_1
      %b3 = block {  # true
        exit_if false  # if_1
      }
      %b4 = block {  # false
        exit_if false  # if_1
      }
    }
    if %logical_and [t: %b5] {  # if_2
      %b5 = block {  # true
        exit_if  # if_2
      }
    }
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_LogicalOr) {
    Func("my_func", tint::Empty, ty.bool_(), Vector{Return(true)});
    auto* let = Let("logical_or", LogicalOr(Call("my_func"), true));
    auto* expr = If(let, Block());
    WrapInFunction(let, expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():bool -> %b1 {
  %b1 = block {
    ret true
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:bool = call %my_func
    %logical_or:bool = if %3 [t: %b3, f: %b4] {  # if_1
      %b3 = block {  # true
        exit_if true  # if_1
      }
      %b4 = block {  # false
        exit_if true  # if_1
      }
    }
    if %logical_or [t: %b5] {  # if_2
      %b5 = block {  # true
        exit_if  # if_2
      }
    }
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Equal) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Equal(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:bool = eq %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_NotEqual) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = NotEqual(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:bool = neq %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_LessThan) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = LessThan(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:bool = lt %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_GreaterThan) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = GreaterThan(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:bool = gt %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_LessThanEqual) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = LessThanEqual(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:bool = lte %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_GreaterThanEqual) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = GreaterThanEqual(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:bool = gte %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_ShiftLeft) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Shl(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = shiftl %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundShiftLeft) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kShiftLeft);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = shiftl %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_ShiftRight) {
    Func("my_func", tint::Empty, ty.u32(), Vector{Return(0_u)});
    auto* expr = Shr(Call("my_func"), 4_u);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():u32 -> %b1 {
  %b1 = block {
    ret 0u
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = call %my_func
    %tint_symbol:u32 = shiftr %3, 4u
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_CompoundShiftRight) {
    GlobalVar("v1", builtin::AddressSpace::kPrivate, ty.u32());
    auto* expr = CompoundAssign("v1", 1_u, ast::BinaryOp::kShiftRight);
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%b1 = block {  # root
  %v1:ptr<private, u32, read_write> = var
}

%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:u32 = load %v1
    %4:u32 = shiftr %3, 1u
    store %v1, %4
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Compound) {
    Func("my_func", tint::Empty, ty.f32(), Vector{Return(0_f)});

    auto* expr = LogicalAnd(LessThan(Call("my_func"), 2_f),
                            GreaterThan(2.5_f, Div(Call("my_func"), Mul(2.3_f, Call("my_func")))));
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func():f32 -> %b1 {
  %b1 = block {
    ret 0.0f
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %3:f32 = call %my_func
    %4:bool = lt %3, 2.0f
    %tint_symbol:bool = if %4 [t: %b3, f: %b4] {  # if_1
      %b3 = block {  # true
        %6:f32 = call %my_func
        %7:f32 = call %my_func
        %8:f32 = mul 2.29999995231628417969f, %7
        %9:f32 = div %6, %8
        %10:bool = gt 2.5f, %9
        exit_if %10  # if_1
      }
      %b4 = block {  # false
        exit_if false  # if_1
      }
    }
    ret
  }
}
)");
}

TEST_F(ProgramToIRBinaryTest, EmitExpression_Binary_Compound_WithConstEval) {
    Func("my_func", Vector{Param("p", ty.bool_())}, ty.bool_(), Vector{Return(true)});
    auto* expr = Call("my_func", LogicalAnd(LessThan(2.4_f, 2_f),
                                            GreaterThan(2.5_f, Div(10_f, Mul(2.3_f, 9.4_f)))));
    WrapInFunction(expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(%my_func = func(%p:bool):bool -> %b1 {
  %b1 = block {
    ret true
  }
}
%test_function = @compute @workgroup_size(1, 1, 1) func():void -> %b2 {
  %b2 = block {
    %tint_symbol:bool = call %my_func, false
    ret
  }
}
)");
}

}  // namespace
}  // namespace tint::wgsl::reader
