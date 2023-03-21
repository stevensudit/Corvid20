// Corvid20: A general-purpose C++ 20 library extending std.
// https://github.com/stevensudit/Corvid20
//
// Copyright 2022-2023 Steven Sudit
//
// Licensed under the Apache License, Version 2.0(the "License");
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
#pragma once
#include "enums_shared.h"
#include "enum_registry.h"
#include "../strings/conversion.h"

namespace corvid::enums {
namespace registry {

// TODO: Use constexpr std::min/max to allow swapping minseq/maxseq safely.

// Default specification for a scoped enum. By default, opts out of both
// sequential and bitmask while providing a simple append method that outputs
// the underlying value as a number.
template<ScopedEnum E, E minseq = E{}, E maxseq = E{}, bool validseq = false,
    bool wrapseq = false, as_underlying_t<E> bitcount = 0,
    bool bitclip = false>
struct scoped_enum_spec
    : base_spec<E, minseq, maxseq, validseq, wrapseq, bitcount, bitclip> {
  auto& append(AppendTarget auto& target, E v) const {
    return strings::append_num(target, as_underlying(v));
  }
};

// Generic support for all scoped enums. This allows outputting the value as
// its underlying integer but fails to qualify as either a bitmask or
// sequential enum. A further specialization is needed to mark a type as a
// bitmask or sequence enum.
template<ScopedEnum E>
constexpr auto enum_spec_v<E> = scoped_enum_spec<E>();

// Conversion.

// TODO: Move this into strings/conversion.h, replacing the previous version.

// Append enum to `target`.
constexpr auto& append_enumXXX(AppendTarget auto& target, ScopedEnum auto t) {
  return enum_spec_v<decltype(t)>.append(target, t);
}

// Return enum as string.
constexpr std::string enum_as_stringXXX(ScopedEnum auto t) {
  std::string target;
  return append_enumXXX(target, t);
}

} // namespace registry
} // namespace corvid::enums