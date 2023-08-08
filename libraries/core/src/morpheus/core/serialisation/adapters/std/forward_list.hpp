#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <forward_list>

namespace morpheus::serialisation::detail
{

template <typename T, typename A>
inline constexpr bool isEnabledForRangeSerialisation<std::forward_list<T, A>> = true;

} // namespace morpheus::serialisation::detail
