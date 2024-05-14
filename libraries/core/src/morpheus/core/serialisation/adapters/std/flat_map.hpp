#pragma once

#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

#include <flat_map>

namespace morpheus::serialisation::detail
{

template <typename K, typename T, class C, class KC, class M>
inline constexpr bool isEnabledForRangeSerialisation<std::flat_map<K, T, C, KC, M>> = true;

} // namespace morpheus::serialisation::detail
