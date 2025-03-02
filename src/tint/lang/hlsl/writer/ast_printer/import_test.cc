// Copyright 2020 The Tint Authors.
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

#include "src/tint/lang/hlsl/writer/ast_printer/helper_test.h"
#include "src/tint/utils/text/string_stream.h"

namespace tint::hlsl::writer {
namespace {

using namespace tint::builtin::fluent_types;  // NOLINT
using namespace tint::number_suffixes;        // NOLINT

using HlslASTPrinterTest_Import = TestHelper;

struct HlslImportData {
    const char* name;
    const char* hlsl_name;
};
inline std::ostream& operator<<(std::ostream& out, HlslImportData data) {
    out << data.name;
    return out;
}

using HlslImportData_SingleParamTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_SingleParamTest, FloatScalar) {
    auto param = GetParam();

    auto* expr = Call(param.name, 1_f);
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) + "(1.0f)");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_SingleParamTest,
                         testing::Values(HlslImportData{"abs", "abs"},
                                         HlslImportData{"acos", "acos"},
                                         HlslImportData{"asin", "asin"},
                                         HlslImportData{"atan", "atan"},
                                         HlslImportData{"cos", "cos"},
                                         HlslImportData{"cosh", "cosh"},
                                         HlslImportData{"ceil", "ceil"},
                                         HlslImportData{"exp", "exp"},
                                         HlslImportData{"exp2", "exp2"},
                                         HlslImportData{"floor", "floor"},
                                         HlslImportData{"fract", "frac"},
                                         HlslImportData{"inverseSqrt", "rsqrt"},
                                         HlslImportData{"length", "length"},
                                         HlslImportData{"log", "log"},
                                         HlslImportData{"log2", "log2"},
                                         HlslImportData{"round", "round"},
                                         HlslImportData{"sin", "sin"},
                                         HlslImportData{"sinh", "sinh"},
                                         HlslImportData{"sqrt", "sqrt"},
                                         HlslImportData{"tan", "tan"},
                                         HlslImportData{"tanh", "tanh"}));

using HlslImportData_SingleIntParamTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_SingleIntParamTest, IntScalar) {
    auto param = GetParam();

    auto* expr = Call(param.name, Expr(1_i));
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) + "(1)");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_SingleIntParamTest,
                         testing::Values(HlslImportData{"abs", "abs"}));

using HlslImportData_SingleVectorParamTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_SingleVectorParamTest, FloatVector) {
    auto param = GetParam();

    auto* expr = Call(param.name, Call<vec3<f32>>(0.1_f, 0.2_f, 0.3_f));
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(
        out.str(),
        std::string(param.hlsl_name) +
            "(float3(0.10000000149011611938f, 0.20000000298023223877f, 0.30000001192092895508f))");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_SingleVectorParamTest,
                         testing::Values(HlslImportData{"abs", "abs"},
                                         HlslImportData{"acos", "acos"},
                                         HlslImportData{"asin", "asin"},
                                         HlslImportData{"atan", "atan"},
                                         HlslImportData{"cos", "cos"},
                                         HlslImportData{"cosh", "cosh"},
                                         HlslImportData{"ceil", "ceil"},
                                         HlslImportData{"exp", "exp"},
                                         HlslImportData{"exp2", "exp2"},
                                         HlslImportData{"floor", "floor"},
                                         HlslImportData{"fract", "frac"},
                                         HlslImportData{"inverseSqrt", "rsqrt"},
                                         HlslImportData{"length", "length"},
                                         HlslImportData{"log", "log"},
                                         HlslImportData{"log2", "log2"},
                                         HlslImportData{"normalize", "normalize"},
                                         HlslImportData{"round", "round"},
                                         HlslImportData{"sin", "sin"},
                                         HlslImportData{"sinh", "sinh"},
                                         HlslImportData{"sqrt", "sqrt"},
                                         HlslImportData{"tan", "tan"},
                                         HlslImportData{"tanh", "tanh"}));

using HlslImportData_DualParam_ScalarTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_DualParam_ScalarTest, Float) {
    auto param = GetParam();

    auto* expr = Call(param.name, 1_f, 2_f);
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) + "(1.0f, 2.0f)");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_DualParam_ScalarTest,
                         testing::Values(HlslImportData{"atan2", "atan2"},
                                         HlslImportData{"distance", "distance"},
                                         HlslImportData{"max", "max"},
                                         HlslImportData{"min", "min"},
                                         HlslImportData{"pow", "pow"},
                                         HlslImportData{"step", "step"}));

using HlslImportData_DualParam_VectorTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_DualParam_VectorTest, Float) {
    auto param = GetParam();

    auto* expr = Call(param.name, Call<vec3<f32>>(1_f, 2_f, 3_f), Call<vec3<f32>>(4_f, 5_f, 6_f));
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) +
                             "(float3(1.0f, 2.0f, 3.0f), float3(4.0f, 5.0f, 6.0f))");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_DualParam_VectorTest,
                         testing::Values(HlslImportData{"atan2", "atan2"},
                                         HlslImportData{"cross", "cross"},
                                         HlslImportData{"distance", "distance"},
                                         HlslImportData{"max", "max"},
                                         HlslImportData{"min", "min"},
                                         HlslImportData{"pow", "pow"},
                                         HlslImportData{"reflect", "reflect"},
                                         HlslImportData{"step", "step"}));

using HlslImportData_DualParam_Int_Test = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_DualParam_Int_Test, IntScalar) {
    auto param = GetParam();

    auto* expr = Call(param.name, 1_i, 2_i);
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) + "(1, 2)");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_DualParam_Int_Test,
                         testing::Values(HlslImportData{"max", "max"},
                                         HlslImportData{"min", "min"}));

using HlslImportData_TripleParam_ScalarTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_TripleParam_ScalarTest, Float) {
    auto param = GetParam();

    auto* expr = Call(param.name, 1_f, 2_f, 3_f);
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) + "(1.0f, 2.0f, 3.0f)");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_TripleParam_ScalarTest,
                         testing::Values(HlslImportData{"fma", "mad"},
                                         HlslImportData{"mix", "lerp"},
                                         HlslImportData{"clamp", "clamp"},
                                         HlslImportData{"smoothstep", "smoothstep"}));

using HlslImportData_TripleParam_VectorTest = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_TripleParam_VectorTest, Float) {
    auto param = GetParam();

    auto* expr = Call(param.name, Call<vec3<f32>>(1_f, 2_f, 3_f), Call<vec3<f32>>(4_f, 5_f, 6_f),
                      Call<vec3<f32>>(7_f, 8_f, 9_f));
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(
        out.str(),
        std::string(param.hlsl_name) +
            R"((float3(1.0f, 2.0f, 3.0f), float3(4.0f, 5.0f, 6.0f), float3(7.0f, 8.0f, 9.0f)))");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_TripleParam_VectorTest,
                         testing::Values(HlslImportData{"faceForward", "faceforward"},
                                         HlslImportData{"fma", "mad"},
                                         HlslImportData{"clamp", "clamp"},
                                         HlslImportData{"smoothstep", "smoothstep"}));

using HlslImportData_TripleParam_Int_Test = TestParamHelper<HlslImportData>;
TEST_P(HlslImportData_TripleParam_Int_Test, IntScalar) {
    auto param = GetParam();

    auto* expr = Call(param.name, 1_i, 2_i, 3_i);
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string(param.hlsl_name) + "(1, 2, 3)");
}
INSTANTIATE_TEST_SUITE_P(HlslASTPrinterTest_Import,
                         HlslImportData_TripleParam_Int_Test,
                         testing::Values(HlslImportData{"clamp", "clamp"}));

TEST_F(HlslASTPrinterTest_Import, HlslImportData_Determinant) {
    GlobalVar("var", ty.mat3x3<f32>(), builtin::AddressSpace::kPrivate);

    auto* expr = Call("determinant", "var");
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string("determinant(var)"));
}

TEST_F(HlslASTPrinterTest_Import, HlslImportData_QuantizeToF16_Scalar) {
    GlobalVar("v", Expr(2_f), builtin::AddressSpace::kPrivate);

    auto* expr = Call("quantizeToF16", "v");
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string("f16tof32(f32tof16(v))"));
}

TEST_F(HlslASTPrinterTest_Import, HlslImportData_QuantizeToF16_Vector) {
    GlobalVar("v", Call<vec3<f32>>(2_f), builtin::AddressSpace::kPrivate);

    auto* expr = Call("quantizeToF16", "v");
    WrapInFunction(expr);

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitCall(out, expr)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), std::string("f16tof32(f32tof16(v))"));
}

}  // namespace
}  // namespace tint::hlsl::writer
