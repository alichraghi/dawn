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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/lang/core/builtin/interpolation_type.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/builtin/interpolation_type.h"

#include <string>

namespace tint::builtin {

/// ParseInterpolationType parses a InterpolationType from a string.
/// @param str the string to parse
/// @returns the parsed enum, or InterpolationType::kUndefined if the string could not be parsed.
InterpolationType ParseInterpolationType(std::string_view str) {
    if (str == "flat") {
        return InterpolationType::kFlat;
    }
    if (str == "linear") {
        return InterpolationType::kLinear;
    }
    if (str == "perspective") {
        return InterpolationType::kPerspective;
    }
    return InterpolationType::kUndefined;
}

std::string_view ToString(InterpolationType value) {
    switch (value) {
        case InterpolationType::kUndefined:
            return "undefined";
        case InterpolationType::kFlat:
            return "flat";
        case InterpolationType::kLinear:
            return "linear";
        case InterpolationType::kPerspective:
            return "perspective";
    }
    return "<unknown>";
}

}  // namespace tint::builtin
