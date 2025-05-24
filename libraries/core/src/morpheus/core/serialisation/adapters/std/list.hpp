#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <list>

namespace morpheus::serialisation::detail
{

template <typename T, typename A>
inline constexpr bool isEnabledForRangeSerialisation<std::list<T, A>> = true;

} // namespace morpheus::serialisation::detail
