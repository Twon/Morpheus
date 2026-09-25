#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/containers/unordered_dense.hpp"
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

namespace morpheus::serialisation::detail
{

template <typename K, typename V, typename H, typename E, typename A, typename B, typename BC>
inline constexpr bool isEnabledForRangeSerialisation<ankerl::unordered_dense::map<K, V, H, E, A, B, BC>> = true;

template <typename K, typename V, typename H, typename E, typename A, typename B, typename BC>
inline constexpr bool isEnabledForRangeSerialisation<ankerl::unordered_dense::segmented_map<K, V, H, E, A, B, BC>> = true;

template <typename K, typename V, typename A>
inline constexpr bool isEnabledForRangeSerialisation<morpheus::containers::UnorderedDenseMap<K, V, A>> = true;

} // namespace morpheus::serialisation::detail
