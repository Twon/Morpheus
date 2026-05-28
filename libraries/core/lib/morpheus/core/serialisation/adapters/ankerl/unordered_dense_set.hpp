#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/containers/unordered_dense.hpp"
#include "morpheus/core/serialisation/adapters/std/ranges.hpp"

namespace morpheus::serialisation::detail
{

template <typename K, typename H, typename E, typename A, typename B, typename BC>
inline constexpr bool isEnabledForRangeSerialisation<ankerl::unordered_dense::set<K, H, E, A, B, BC>> = true;

template <typename K, typename H, typename E, typename A, typename B, typename BC>
inline constexpr bool isEnabledForRangeSerialisation<ankerl::unordered_dense::segmented_set<K, H, E, A, B, BC>> = true;

template <typename K, typename A>
inline constexpr bool isEnabledForRangeSerialisation<morpheus::containers::UnorderedDenseSet<K, A>> = true;

} // namespace morpheus::serialisation::detail
