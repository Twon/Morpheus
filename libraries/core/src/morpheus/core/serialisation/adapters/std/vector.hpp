#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <vector>

namespace morpheus::serialisation::detail
{

template <typename T, typename A>
inline constexpr bool isEnabledForRangeSerialisation<std::vector<T, A>> = true;

/// std::vector<std::byte>> is handled by the native interface.
template <>
inline constexpr bool isEnabledForRangeSerialisation<std::vector<std::byte>> = false;

} // namespace morpheus::serialisation::detail
