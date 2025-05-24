#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <vector>

namespace morpheus::serialisation::detail
{

template <typename T, typename A>
inline constexpr bool isEnabledForRangeSerialisation<std::vector<T, A>> = true;

} // namespace morpheus::serialisation::detail
