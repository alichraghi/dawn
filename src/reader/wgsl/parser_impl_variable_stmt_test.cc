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

#include "gtest/gtest.h"
#include "src/ast/statement.h"
#include "src/ast/variable_decl_statement.h"
#include "src/reader/wgsl/parser_impl.h"
#include "src/reader/wgsl/parser_impl_test_helper.h"

namespace tint {
namespace reader {
namespace wgsl {
namespace {

TEST_F(ParserImplTest, VariableStmt_VariableDecl) {
  auto* p = parser("var a : i32;");
  auto e = p->variable_stmt();
  EXPECT_TRUE(e.matched);
  EXPECT_FALSE(e.errored);
  EXPECT_FALSE(p->has_error()) << p->error();
  ASSERT_NE(e.value, nullptr);
  ASSERT_TRUE(e.value->IsVariableDecl());
  ASSERT_NE(e.value->variable(), nullptr);
  EXPECT_EQ(e.value->variable()->name(), "a");

  ASSERT_EQ(e.value->source().range.begin.line, 1u);
  ASSERT_EQ(e.value->source().range.begin.column, 5u);
  ASSERT_EQ(e.value->source().range.end.line, 1u);
  ASSERT_EQ(e.value->source().range.end.column, 6u);

  EXPECT_EQ(e.value->variable()->constructor(), nullptr);
}

TEST_F(ParserImplTest, VariableStmt_VariableDecl_WithInit) {
  auto* p = parser("var a : i32 = 1;");
  auto e = p->variable_stmt();
  EXPECT_TRUE(e.matched);
  EXPECT_FALSE(e.errored);
  EXPECT_FALSE(p->has_error()) << p->error();
  ASSERT_NE(e.value, nullptr);
  ASSERT_TRUE(e.value->IsVariableDecl());
  ASSERT_NE(e.value->variable(), nullptr);
  EXPECT_EQ(e.value->variable()->name(), "a");

  ASSERT_EQ(e.value->source().range.begin.line, 1u);
  ASSERT_EQ(e.value->source().range.begin.column, 5u);
  ASSERT_EQ(e.value->source().range.end.line, 1u);
  ASSERT_EQ(e.value->source().range.end.column, 6u);

  ASSERT_NE(e.value->variable()->constructor(), nullptr);
  EXPECT_TRUE(e.value->variable()->constructor()->IsConstructor());
}

TEST_F(ParserImplTest, VariableStmt_VariableDecl_Invalid) {
  auto* p = parser("var a : invalid;");
  auto e = p->variable_stmt();
  EXPECT_FALSE(e.matched);
  EXPECT_TRUE(e.errored);
  EXPECT_EQ(e.value, nullptr);
  EXPECT_TRUE(p->has_error());
  EXPECT_EQ(p->error(), "1:9: unknown constructed type 'invalid'");
}

TEST_F(ParserImplTest, VariableStmt_VariableDecl_ConstructorInvalid) {
  auto* p = parser("var a : i32 = if(a) {}");
  auto e = p->variable_stmt();
  EXPECT_FALSE(e.matched);
  EXPECT_TRUE(e.errored);
  EXPECT_EQ(e.value, nullptr);
  EXPECT_TRUE(p->has_error());
  EXPECT_EQ(p->error(), "1:15: missing constructor for variable declaration");
}

TEST_F(ParserImplTest, VariableStmt_Const) {
  auto* p = parser("const a : i32 = 1");
  auto e = p->variable_stmt();
  EXPECT_TRUE(e.matched);
  EXPECT_FALSE(e.errored);
  EXPECT_FALSE(p->has_error()) << p->error();
  ASSERT_NE(e.value, nullptr);
  ASSERT_TRUE(e.value->IsVariableDecl());

  ASSERT_EQ(e.value->source().range.begin.line, 1u);
  ASSERT_EQ(e.value->source().range.begin.column, 7u);
  ASSERT_EQ(e.value->source().range.end.line, 1u);
  ASSERT_EQ(e.value->source().range.end.column, 8u);
}

TEST_F(ParserImplTest, VariableStmt_Const_InvalidVarIdent) {
  auto* p = parser("const a : invalid = 1");
  auto e = p->variable_stmt();
  EXPECT_FALSE(e.matched);
  EXPECT_TRUE(e.errored);
  EXPECT_EQ(e.value, nullptr);
  EXPECT_TRUE(p->has_error());
  EXPECT_EQ(p->error(), "1:11: unknown constructed type 'invalid'");
}

TEST_F(ParserImplTest, VariableStmt_Const_MissingEqual) {
  auto* p = parser("const a : i32 1");
  auto e = p->variable_stmt();
  EXPECT_FALSE(e.matched);
  EXPECT_TRUE(e.errored);
  EXPECT_EQ(e.value, nullptr);
  EXPECT_TRUE(p->has_error());
  EXPECT_EQ(p->error(), "1:15: expected '=' for constant declaration");
}

TEST_F(ParserImplTest, VariableStmt_Const_MissingConstructor) {
  auto* p = parser("const a : i32 =");
  auto e = p->variable_stmt();
  EXPECT_FALSE(e.matched);
  EXPECT_TRUE(e.errored);
  EXPECT_EQ(e.value, nullptr);
  EXPECT_TRUE(p->has_error());
  EXPECT_EQ(p->error(), "1:16: missing constructor for const declaration");
}

TEST_F(ParserImplTest, VariableStmt_Const_InvalidConstructor) {
  auto* p = parser("const a : i32 = if (a) {}");
  auto e = p->variable_stmt();
  EXPECT_FALSE(e.matched);
  EXPECT_TRUE(e.errored);
  EXPECT_EQ(e.value, nullptr);
  EXPECT_TRUE(p->has_error());
  EXPECT_EQ(p->error(), "1:17: missing constructor for const declaration");
}

}  // namespace
}  // namespace wgsl
}  // namespace reader
}  // namespace tint
