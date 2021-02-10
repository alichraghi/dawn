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

#include "src/transform/hlsl.h"

#include <utility>

#include "src/program_builder.h"

namespace tint {
namespace transform {

Hlsl::Hlsl() = default;
Hlsl::~Hlsl() = default;

Transform::Output Hlsl::Run(const Program* in) {
  ProgramBuilder out;
  CloneContext(&out, in).Clone();
  return Output{Program(std::move(out))};
}

}  // namespace transform
}  // namespace tint
