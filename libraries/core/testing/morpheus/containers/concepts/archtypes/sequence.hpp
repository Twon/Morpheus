#pragma once

#include "morpheus/containers/concepts/archtypes/container.hpp"

#include <cstddef>
#include <compare>
#include <initializer_list>
#include <iterator>

namespace morpheus::containers::concepts::archtypes
{

struct Sequence : Container
{
    constexpr Sequence();
    constexpr Sequence(size_type, value_type);
    constexpr Sequence(iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr Sequence(ranges::from_range, ranges::subrange<typename T::value_type>{});
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
    constexpr iterator insert(iterator, ranges::subrange<value_type>{});
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr iterator insert(iterator, std::initializer_list<int>);
    constexpr iterator erase(iterator);
    constexpr iterator erase(iterator, iterator);
    constexpr void clear();
    constexpr void assign(iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr void assign_range(ranges::subrange<value_type>{});
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr void assign(std::initializer_list<int>);
    constexpr void assign(size_type, value_type);
};

} // namespace morpheus::containers::concepts::archtypes 
