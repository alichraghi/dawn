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
//   src/tint/lang/core/builtin/interpolation_sampling.h.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_LANG_CORE_BUILTIN_INTERPOLATION_SAMPLING_H_
#define SRC_TINT_LANG_CORE_BUILTIN_INTERPOLATION_SAMPLING_H_

#include <string>

#include "src/tint/utils/traits/traits.h"

namespace tint::builtin {

/// The interpolation sampling.
enum class InterpolationSampling {
    kUndefined,
    kCenter,
    kCentroid,
    kSample,
};

/// @param value the enum value
/// @returns the string for the given enum value
std::string_view ToString(InterpolationSampling value);

/// @param out the stream to write to
/// @param value the InterpolationSampling
/// @returns @p out so calls can be chained
template <typename STREAM, typename = traits::EnableIfIsOStream<STREAM>>
auto& operator<<(STREAM& out, InterpolationSampling value) {
    return out << ToString(value);
}

/// ParseInterpolationSampling parses a InterpolationSampling from a string.
/// @param str the string to parse
/// @returns the parsed enum, or InterpolationSampling::kUndefined if the string could not be
/// parsed.
InterpolationSampling ParseInterpolationSampling(std::string_view str);

constexpr const char* kInterpolationSamplingStrings[] = {
    "center",
    "centroid",
    "sample",
};

}  // namespace tint::builtin

#endif  // SRC_TINT_LANG_CORE_BUILTIN_INTERPOLATION_SAMPLING_H_
