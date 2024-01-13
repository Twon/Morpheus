#pragma once

#include "morpheus/core/meta/concepts/constructible.hpp"
#include "morpheus/core/meta/concepts/trait.hpp"
#include <type_traits>
#include <utility>

namespace morpheus::meta::concepts
{

/// \concept Aggregate
///     Ensures a type is a aggregate and is initialisable from the given argument types.
template <typename T, typename... Args>
concept AggregateConstructable = Trait<T, std::is_aggregate> && Constructible<T, Args...>;

} // namespace morpheus::meta::concepts
