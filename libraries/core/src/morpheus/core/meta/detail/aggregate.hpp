#pragma once

#include "core/meta/concepts/aggregate.hpp"
#include "core/meta/detail/any.hpp"

namespace morpheus::meta::detail
{

template <concepts::Aggregate T, typename Indices>
struct AggregateConstructibleFromIndicies;

/// \struct AggregateConstructibleFromIndicies
///     Ensures a type is a aggregate and constructible from a given number of arguments.
template <concepts::Aggregate T, std::size_t... Indices>
struct AggregateConstructibleFromIndicies<T, std::index_sequence<Indices...>> : std::bool_constant<concepts::AggregateConstructable<T, IndexedAny<Indices>...>>
{};

} // namespace morpheus::meta::detail
