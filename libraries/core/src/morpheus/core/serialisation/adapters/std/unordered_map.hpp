#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <unordered_map>

namespace morpheus::serialisation::detail
{

template <typename K, typename V, class H, class C, class A>
inline constexpr bool isEnabledForRangeSerialisation<std::unordered_map<K, V, H, C, A>> = true;

} // namespace morpheus::serialisation::detail
