#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <set>

namespace morpheus::serialisation::detail
{

template <typename T, typename C, typename A>
inline constexpr bool isEnabledForRangeSerialisation<std::set<T, C, A>> = true;

} // namespace morpheus::serialisation::detail
