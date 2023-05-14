#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <vector>

namespace morpheus::serialisation::detail
{

template <typename T>
inline constexpr bool isEnabledForRangeSerialisation<std::vector<T>> = true;

} // namespace morpheus::serialisation::detail
