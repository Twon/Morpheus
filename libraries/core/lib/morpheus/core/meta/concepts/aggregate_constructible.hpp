#pragma once

#include "core/meta/concepts/aggregate.hpp"
#include "core/meta/concepts/constructible.hpp"
#include "core/meta/detail/aggregate.hpp"
#include <type_traits>
#include <utility>

namespace morpheus::meta::concepts
{

/// \concept AggregateConstructableWithNArgs
///     Ensures a type is a aggregate and constructible from a given number of arguments.
template <typename T, std::size_t N>
concept AggregateConstructableWithNArgs = detail::AggregateConstructibleFromIndicies<T, std::make_index_sequence<N>>::value;

} // namespace morpheus::meta::concepts
