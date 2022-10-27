#pragma once

#include "morpheus/core/meta/concepts/constructible.hpp"
#include <type_traits>
#include <utility>

namespace morpheus::meta::concepts
{

/// \concept Aggregate
///     Ensures a type is a aggregate.
template <typename T>
concept Aggregate = std::is_aggregate_v<T>;

/// \concept Aggregate
///     Ensures a type is a aggregate and is initialisable from the given argument types.
template <typename T, typename... Args>
concept AggregateConstructable = Aggregate<T> && Constructible<T, Args...>;

} // namespace morpheus::meta::concepts