#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <map>

namespace morpheus::serialisation::detail
{

template <typename K, typename V, class C, class A>
inline constexpr bool isEnabledForRangeSerialisation<std::map<K,V, C, A>> = true;

} // namespace morpheus::serialisation::detail
