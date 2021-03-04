// Copyright 2021 The Tint Authors.
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

#include "src/transform/renamer.h"

#include "gmock/gmock.h"
#include "src/transform/test_helper.h"

namespace tint {
namespace transform {
namespace {

using ::testing::ContainerEq;

using RenamerTest = TransformTest;

TEST_F(RenamerTest, EmptyModule) {
  auto* src = "";
  auto* expect = "";

  auto got = Transform<Renamer>(src);

  EXPECT_EQ(expect, str(got));

  auto* data = got.data.Get<Renamer::Data>();

  ASSERT_EQ(data->remappings.size(), 0u);
}

TEST_F(RenamerTest, BasicModuleVertexIndex) {
  auto* src = R"(
[[builtin(vertex_index)]] var<in> vert_idx : u32;

fn test() -> u32 {
  return vert_idx;
}

[[stage(vertex)]]
fn entry() -> void {
  test();
}
)";

  auto* expect = R"(
[[builtin(vertex_index)]] var<in> _tint_1 : u32;

fn _tint_2() -> u32 {
  return _tint_1;
}

[[stage(vertex)]]
fn _tint_3() -> void {
  _tint_2();
}
)";

  auto got = Transform<Renamer>(src);

  EXPECT_EQ(expect, str(got));

  auto* data = got.data.Get<Renamer::Data>();

  ASSERT_NE(data, nullptr);
  Renamer::Data::Remappings expected_remappings = {
      {"vert_idx", "_tint_1"},
      {"test", "_tint_2"},
      {"entry", "_tint_3"},
  };
  EXPECT_THAT(data->remappings, ContainerEq(expected_remappings));
}

}  // namespace
}  // namespace transform
}  // namespace tint
