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

#include <memory>

#include "gtest/gtest.h"
#include "src/ast/identifier_expression.h"
#include "src/ast/member_accessor_expression.h"
#include "src/writer/wgsl/generator_impl.h"
#include "src/writer/wgsl/test_helper.h"

namespace tint {
namespace writer {
namespace wgsl {
namespace {

using WgslGeneratorImplTest = TestHelper;

TEST_F(WgslGeneratorImplTest, EmitExpression_MemberAccessor) {
  auto str = create<ast::IdentifierExpression>("str");
  auto mem = create<ast::IdentifierExpression>("mem");

  ast::MemberAccessorExpression expr(std::move(str), std::move(mem));

  ASSERT_TRUE(gen.EmitExpression(&expr)) << gen.error();
  EXPECT_EQ(gen.result(), "str.mem");
}

}  // namespace
}  // namespace wgsl
}  // namespace writer
}  // namespace tint
