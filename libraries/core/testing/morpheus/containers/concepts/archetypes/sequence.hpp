#pragma once

#include "morpheus/containers/concepts/archetypes/container.hpp"

#include "morpheus/core/conformance/ranges.hpp"

#include <compare>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <ranges>
#include <vector>

namespace morpheus::containers::concepts::archetypes
{

/// \brief Sequence
///      Archetypes providing the minimal interface required to meet the concepts::Sequence constraints.
struct Sequence : Container
{
    constexpr Sequence();
    constexpr Sequence(size_type, value_type);
    constexpr Sequence(iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr Sequence(std::from_range_t, ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr Sequence(std::initializer_list<int>);
    constexpr Sequence(Sequence const&);
    constexpr Sequence(Sequence&&);
    constexpr ~Sequence();
    constexpr Sequence& operator=(Sequence const&);
    constexpr Sequence& operator=(Sequence&&);
    constexpr Sequence& operator=(std::initializer_list<int>);

    constexpr auto operator<=>(Sequence const&) const = default;

    constexpr iterator insert(iterator, value_type);
    constexpr iterator insert(iterator, size_type, value_type);
    constexpr iterator insert(iterator, iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr iterator insert_range(iterator, ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr iterator insert(iterator, std::initializer_list<int>);
    constexpr iterator erase(iterator);
    constexpr iterator erase(iterator, iterator);
    constexpr void clear();
    constexpr void assign(iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr void assign_range(ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr void assign(std::initializer_list<int>);
    constexpr void assign(size_type, value_type);
};

} // namespace morpheus::containers::concepts::archetypes
