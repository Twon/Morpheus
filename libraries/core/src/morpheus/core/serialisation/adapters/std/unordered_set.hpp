#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <unordered_set>

namespace morpheus::serialisation::detail
{

template <typename T, class H, class C, class A>
inline constexpr bool isEnabledForRangeSerialisation<std::unordered_set<T, H, C, A>> = true;

} // namespace morpheus::serialisation::detail
