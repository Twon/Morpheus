#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <vector>

namespace morpheus::serialisation::detail
{

template <typename T>
inline constexpr bool isEnabledForRangeSerialisation<std::span<T>> = true;

/// std::span<std::byte> is handled by the native interface.
template <>
inline constexpr bool isEnabledForRangeSerialisation<std::span<std::byte>> = false;

} // namespace morpheus::serialisation::detail
