#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <array>

namespace morpheus::serialisation::detail
{

template <typename T, std::size_t N>
inline constexpr bool isEnabledForRangeSerialisation<std::array<T, N>> = true;

} // namespace morpheus::serialisation::detail
