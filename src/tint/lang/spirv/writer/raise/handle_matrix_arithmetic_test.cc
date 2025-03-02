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

#include "src/tint/lang/spirv/writer/raise/handle_matrix_arithmetic.h"

#include <utility>

#include "src/tint/lang/core/ir/transform/helper_test.h"
#include "src/tint/lang/core/type/matrix.h"

namespace tint::spirv::writer::raise {
namespace {

using namespace tint::builtin::fluent_types;  // NOLINT
using namespace tint::number_suffixes;        // NOLINT

using SpirvWriter_HandleMatrixArithmeticTest = ir::transform::TransformTest;

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Add_Mat2x3f) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat2x3<f32>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat2x3<f32>());
    auto* func = b.Function("foo", ty.mat2x3<f32>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Add(ty.mat2x3<f32>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat2x3<f32>, %arg2:mat2x3<f32>):mat2x3<f32> -> %b1 {
  %b1 = block {
    %4:mat2x3<f32> = add %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat2x3<f32>, %arg2:mat2x3<f32>):mat2x3<f32> -> %b1 {
  %b1 = block {
    %4:vec3<f32> = access %arg1, 0u
    %5:vec3<f32> = access %arg2, 0u
    %6:vec3<f32> = add %4, %5
    %7:vec3<f32> = access %arg1, 1u
    %8:vec3<f32> = access %arg2, 1u
    %9:vec3<f32> = add %7, %8
    %10:mat2x3<f32> = construct %6, %9
    ret %10
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Add_Mat4x2h) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat4x2<f16>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat4x2<f16>());
    auto* func = b.Function("foo", ty.mat4x2<f16>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Add(ty.mat4x2<f16>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat4x2<f16>, %arg2:mat4x2<f16>):mat4x2<f16> -> %b1 {
  %b1 = block {
    %4:mat4x2<f16> = add %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat4x2<f16>, %arg2:mat4x2<f16>):mat4x2<f16> -> %b1 {
  %b1 = block {
    %4:vec2<f16> = access %arg1, 0u
    %5:vec2<f16> = access %arg2, 0u
    %6:vec2<f16> = add %4, %5
    %7:vec2<f16> = access %arg1, 1u
    %8:vec2<f16> = access %arg2, 1u
    %9:vec2<f16> = add %7, %8
    %10:vec2<f16> = access %arg1, 2u
    %11:vec2<f16> = access %arg2, 2u
    %12:vec2<f16> = add %10, %11
    %13:vec2<f16> = access %arg1, 3u
    %14:vec2<f16> = access %arg2, 3u
    %15:vec2<f16> = add %13, %14
    %16:mat4x2<f16> = construct %6, %9, %12, %15
    ret %16
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Subtract_Mat3x2f) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat3x2<f32>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat3x2<f32>());
    auto* func = b.Function("foo", ty.mat3x2<f32>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Subtract(ty.mat3x2<f32>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat3x2<f32>, %arg2:mat3x2<f32>):mat3x2<f32> -> %b1 {
  %b1 = block {
    %4:mat3x2<f32> = sub %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat3x2<f32>, %arg2:mat3x2<f32>):mat3x2<f32> -> %b1 {
  %b1 = block {
    %4:vec2<f32> = access %arg1, 0u
    %5:vec2<f32> = access %arg2, 0u
    %6:vec2<f32> = sub %4, %5
    %7:vec2<f32> = access %arg1, 1u
    %8:vec2<f32> = access %arg2, 1u
    %9:vec2<f32> = sub %7, %8
    %10:vec2<f32> = access %arg1, 2u
    %11:vec2<f32> = access %arg2, 2u
    %12:vec2<f32> = sub %10, %11
    %13:mat3x2<f32> = construct %6, %9, %12
    ret %13
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Subtract_Mat2x4h) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat2x4<f16>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat2x4<f16>());
    auto* func = b.Function("foo", ty.mat2x4<f16>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Subtract(ty.mat2x4<f16>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat2x4<f16>, %arg2:mat2x4<f16>):mat2x4<f16> -> %b1 {
  %b1 = block {
    %4:mat2x4<f16> = sub %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat2x4<f16>, %arg2:mat2x4<f16>):mat2x4<f16> -> %b1 {
  %b1 = block {
    %4:vec4<f16> = access %arg1, 0u
    %5:vec4<f16> = access %arg2, 0u
    %6:vec4<f16> = sub %4, %5
    %7:vec4<f16> = access %arg1, 1u
    %8:vec4<f16> = access %arg2, 1u
    %9:vec4<f16> = sub %7, %8
    %10:mat2x4<f16> = construct %6, %9
    ret %10
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Mul_Mat2x3f_Scalar) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat2x3<f32>());
    auto* arg2 = b.FunctionParam("arg2", ty.f32());
    auto* func = b.Function("foo", ty.mat2x3<f32>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Multiply(ty.mat2x3<f32>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat2x3<f32>, %arg2:f32):mat2x3<f32> -> %b1 {
  %b1 = block {
    %4:mat2x3<f32> = mul %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat2x3<f32>, %arg2:f32):mat2x3<f32> -> %b1 {
  %b1 = block {
    %4:mat2x3<f32> = spirv.matrix_times_scalar %arg1, %arg2
    ret %4
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Mul_Mat3x4f_Vector) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat3x4<f32>());
    auto* arg2 = b.FunctionParam("arg2", ty.vec3<f32>());
    auto* func = b.Function("foo", ty.vec4<f32>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Multiply(ty.vec4<f32>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat3x4<f32>, %arg2:vec3<f32>):vec4<f32> -> %b1 {
  %b1 = block {
    %4:vec4<f32> = mul %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat3x4<f32>, %arg2:vec3<f32>):vec4<f32> -> %b1 {
  %b1 = block {
    %4:vec4<f32> = spirv.matrix_times_vector %arg1, %arg2
    ret %4
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Mul_Mat4x2f_Mat2x4) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat4x2<f32>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat2x4<f32>());
    auto* func = b.Function("foo", ty.mat2x2<f32>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Multiply(ty.mat2x2<f32>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat4x2<f32>, %arg2:mat2x4<f32>):mat2x2<f32> -> %b1 {
  %b1 = block {
    %4:mat2x2<f32> = mul %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat4x2<f32>, %arg2:mat2x4<f32>):mat2x2<f32> -> %b1 {
  %b1 = block {
    %4:mat2x2<f32> = spirv.matrix_times_matrix %arg1, %arg2
    ret %4
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Mul_Scalar_Mat3x2h) {
    auto* arg1 = b.FunctionParam("arg1", ty.f16());
    auto* arg2 = b.FunctionParam("arg2", ty.mat3x2<f16>());
    auto* func = b.Function("foo", ty.mat3x2<f16>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Multiply(ty.mat3x2<f16>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:f16, %arg2:mat3x2<f16>):mat3x2<f16> -> %b1 {
  %b1 = block {
    %4:mat3x2<f16> = mul %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:f16, %arg2:mat3x2<f16>):mat3x2<f16> -> %b1 {
  %b1 = block {
    %4:mat3x2<f16> = spirv.matrix_times_scalar %arg2, %arg1
    ret %4
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Mul_Vector_Mat3x4f) {
    auto* arg1 = b.FunctionParam("arg1", ty.vec3<f16>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat4x3<f16>());
    auto* func = b.Function("foo", ty.vec4<f16>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Multiply(ty.vec4<f16>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:vec3<f16>, %arg2:mat4x3<f16>):vec4<f16> -> %b1 {
  %b1 = block {
    %4:vec4<f16> = mul %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:vec3<f16>, %arg2:mat4x3<f16>):vec4<f16> -> %b1 {
  %b1 = block {
    %4:vec4<f16> = spirv.vector_times_matrix %arg1, %arg2
    ret %4
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Mul_Mat3x3f_Mat3x3) {
    auto* arg1 = b.FunctionParam("arg1", ty.mat3x3<f16>());
    auto* arg2 = b.FunctionParam("arg2", ty.mat3x3<f16>());
    auto* func = b.Function("foo", ty.mat3x3<f16>());
    func->SetParams({arg1, arg2});

    b.Append(func->Block(), [&] {
        auto* result = b.Multiply(ty.mat3x3<f16>(), arg1, arg2);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg1:mat3x3<f16>, %arg2:mat3x3<f16>):mat3x3<f16> -> %b1 {
  %b1 = block {
    %4:mat3x3<f16> = mul %arg1, %arg2
    ret %4
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg1:mat3x3<f16>, %arg2:mat3x3<f16>):mat3x3<f16> -> %b1 {
  %b1 = block {
    %4:mat3x3<f16> = spirv.matrix_times_matrix %arg1, %arg2
    ret %4
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Convert_Mat2x3_F32_to_F16) {
    auto* arg = b.FunctionParam("arg", ty.mat2x3<f32>());
    auto* func = b.Function("foo", ty.mat2x3<f16>());
    func->SetParams({arg});

    b.Append(func->Block(), [&] {
        auto* result = b.Convert(ty.mat2x3<f16>(), arg);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg:mat2x3<f32>):mat2x3<f16> -> %b1 {
  %b1 = block {
    %3:mat2x3<f16> = convert %arg
    ret %3
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg:mat2x3<f32>):mat2x3<f16> -> %b1 {
  %b1 = block {
    %3:vec3<f32> = access %arg, 0u
    %4:vec3<f16> = convert %3
    %5:vec3<f32> = access %arg, 1u
    %6:vec3<f16> = convert %5
    %7:mat2x3<f16> = construct %4, %6
    ret %7
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Convert_Mat4x4_F32_to_F16) {
    auto* arg = b.FunctionParam("arg", ty.mat4x4<f32>());
    auto* func = b.Function("foo", ty.mat4x4<f16>());
    func->SetParams({arg});

    b.Append(func->Block(), [&] {
        auto* result = b.Convert(ty.mat4x4<f16>(), arg);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg:mat4x4<f32>):mat4x4<f16> -> %b1 {
  %b1 = block {
    %3:mat4x4<f16> = convert %arg
    ret %3
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg:mat4x4<f32>):mat4x4<f16> -> %b1 {
  %b1 = block {
    %3:vec4<f32> = access %arg, 0u
    %4:vec4<f16> = convert %3
    %5:vec4<f32> = access %arg, 1u
    %6:vec4<f16> = convert %5
    %7:vec4<f32> = access %arg, 2u
    %8:vec4<f16> = convert %7
    %9:vec4<f32> = access %arg, 3u
    %10:vec4<f16> = convert %9
    %11:mat4x4<f16> = construct %4, %6, %8, %10
    ret %11
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Convert_Mat4x3_F16_to_F32) {
    auto* arg = b.FunctionParam("arg", ty.mat4x3<f16>());
    auto* func = b.Function("foo", ty.mat4x3<f32>());
    func->SetParams({arg});

    b.Append(func->Block(), [&] {
        auto* result = b.Convert(ty.mat4x3<f32>(), arg);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg:mat4x3<f16>):mat4x3<f32> -> %b1 {
  %b1 = block {
    %3:mat4x3<f32> = convert %arg
    ret %3
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg:mat4x3<f16>):mat4x3<f32> -> %b1 {
  %b1 = block {
    %3:vec3<f16> = access %arg, 0u
    %4:vec3<f32> = convert %3
    %5:vec3<f16> = access %arg, 1u
    %6:vec3<f32> = convert %5
    %7:vec3<f16> = access %arg, 2u
    %8:vec3<f32> = convert %7
    %9:vec3<f16> = access %arg, 3u
    %10:vec3<f32> = convert %9
    %11:mat4x3<f32> = construct %4, %6, %8, %10
    ret %11
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

TEST_F(SpirvWriter_HandleMatrixArithmeticTest, Convert_Mat2x2_F16_to_F32) {
    auto* arg = b.FunctionParam("arg", ty.mat2x2<f32>());
    auto* func = b.Function("foo", ty.mat2x2<f16>());
    func->SetParams({arg});

    b.Append(func->Block(), [&] {
        auto* result = b.Convert(ty.mat2x2<f16>(), arg);
        b.Return(func, result);
    });

    auto* src = R"(
%foo = func(%arg:mat2x2<f32>):mat2x2<f16> -> %b1 {
  %b1 = block {
    %3:mat2x2<f16> = convert %arg
    ret %3
  }
}
)";
    EXPECT_EQ(src, str());

    auto* expect = R"(
%foo = func(%arg:mat2x2<f32>):mat2x2<f16> -> %b1 {
  %b1 = block {
    %3:vec2<f32> = access %arg, 0u
    %4:vec2<f16> = convert %3
    %5:vec2<f32> = access %arg, 1u
    %6:vec2<f16> = convert %5
    %7:mat2x2<f16> = construct %4, %6
    ret %7
  }
}
)";

    Run(HandleMatrixArithmetic);

    EXPECT_EQ(expect, str());
}

}  // namespace
}  // namespace tint::spirv::writer::raise
