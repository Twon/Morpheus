#pragma once

#include "morpheus/containers/concepts/archetypes/allocator_aware.hpp"

#include "morpheus/core/conformance/ranges.hpp"

#include <compare>
#include <functional>
#include <initializer_list>

namespace morpheus::containers::concepts::archetypes
{

namespace detail
{

template <bool M = false>
struct Multi
{
    struct insert_return_type
    {};

    constexpr auto operator<=>(Multi const&) const = default;
};

template <>
struct Multi<true>
{
    constexpr auto operator<=>(Multi const&) const = default;
};

template <bool M = false>
struct Mapped
{
    /// The value type of the container.
    using value_type = int;
    /// The key type of the container.
    using key_type = value_type;
    /// The allocator type of the container.
    using allocator_type = std::allocator<value_type>;

    /// Spaceship operator
    constexpr auto operator<=>(Mapped const&) const = default;
};

template <>
struct Mapped<true>
{
    /// The mapped type of the container.
    using mapped_type = int;
    /// The value type of the container.
    using value_type = std::pair<int const, mapped_type>;
    /// The key type of the container.
    using key_type = typename value_type::first_type;
    /// The allocator type of the container.
    using allocator_type = std::allocator<value_type>;

    /// Spaceship operator
    constexpr auto operator<=>(Mapped const&) const = default;
};

} // namespace detail

template <bool multi = false, bool mapped = false>
struct Associative
    : AllocatorAware
    , detail::Multi<multi>
    , detail::Mapped<mapped>
{
    /// The value type of the container.
    using value_type = typename detail::Mapped<mapped>::value_type;
    /// The key type of the container.
    using key_type = typename detail::Mapped<mapped>::key_type;
    /// The allocator type of the container.
    using allocator_type = typename detail::Mapped<mapped>::allocator_type;
    /// The key comparison type of the container.
    using key_compare = std::less<int>;
    /// The value comparison type of the container.
    using value_compare = key_compare;
    struct node_type
    {};

    using InsertReturnType = std::conditional_t<multi, iterator, std::pair<iterator, bool>>;

    /// @cond INTERNAL
    using InsertNodeHandleReturnType = std::invoke_result_t<decltype([]
    {
        if constexpr (requires { requires requires {typename detail::Multi<multi>::insert_return_type; }; })
        {
            return typename detail::Multi<multi>::insert_return_type{};
        }
        else
        {
            return typename AllocatorAware::iterator{};
        }
    })>;
    /// @endcond

    using BoundReturnType = std::conditional_t<multi, iterator, std::pair<iterator, iterator>>;
    using BoundConstReturnType = std::conditional_t<multi, const_iterator, std::pair<const_iterator, const_iterator>>;

    using AllocatorAware::AllocatorAware;
    using detail::Mapped<mapped>::Mapped;

    /// Default constructor.
    constexpr Associative();
    /// Construct the container with a specific key comparison function.
    constexpr Associative(key_compare const&);
    /// Construct the container from a begin and end iterator with a specific key comparison function.
    constexpr Associative(iterator, iterator, key_compare const&);
    /// Construct the container from a begin and end iterator.
    constexpr Associative(iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    /// Construct the container from a range and key comparison function.
    constexpr Associative(std::from_range_t, conf::ranges::range auto, key_compare const&);
    /// Construct the container from a range.
    constexpr Associative(std::from_range_t, conf::ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    /// Construct the container from an initializer list and key comparison function.
    constexpr Associative(std::initializer_list<value_type>, key_compare const&);
    /// Construct the container from an initializer list.
    constexpr Associative(std::initializer_list<value_type>);
    /// Copy constructor.
    constexpr Associative(Associative const&);
    /// Move constructor.
    constexpr Associative(Associative&&);
    /// Copy assignment operator.
    constexpr Associative& operator=(Associative const&);
    /// Move assignment operator.
    constexpr Associative& operator=(Associative&&);
    /// Assignment operator for initializer list.
    constexpr Associative& operator=(std::initializer_list<value_type>);

    /// Get the allocator of the container.
    constexpr allocator_type get_allocator() const noexcept;

    /// Get the key comparison function of the container.
    constexpr key_compare key_comp() const;
    /// Get the value comparison function of the container.
    constexpr value_compare value_comp() const;

    constexpr InsertReturnType emplace(auto... args);
    constexpr iterator emplace_hint(iterator, auto... args);

    constexpr InsertReturnType insert(value_type);
    constexpr iterator insert(const_iterator, value_type);
    constexpr void insert(const_iterator, const_iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr void insert_range(conf::ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr void insert(std::initializer_list<value_type>);
    constexpr InsertNodeHandleReturnType insert(node_type&&);
    constexpr iterator insert(const_iterator, node_type&&);

    constexpr node_type extract(key_type);
    constexpr node_type extract(const_iterator);

    constexpr void merge(Associative const&);

    constexpr iterator erase(iterator);
    constexpr iterator erase(const_iterator);
    constexpr iterator erase(iterator, iterator);
    constexpr iterator erase(const_iterator, const_iterator);
    constexpr size_type erase(key_type const&);

    constexpr void clear();

    constexpr iterator find(key_type const&);
    constexpr const_iterator find(key_type const&) const;

    constexpr size_type count(key_type const&) const;

    constexpr bool contains(key_type const&) const;

    BoundReturnType lower_bound(key_type const&);
    BoundConstReturnType lower_bound(key_type const&) const;
    BoundReturnType equal_range(key_type const&);
    BoundConstReturnType equal_range(key_type const&) const;
    BoundReturnType upper_bound(key_type const&);
    BoundConstReturnType upper_bound(key_type const&) const;

    /// Spaceship operator
    constexpr auto operator<=>(Associative const&) const = default;
};

} // namespace morpheus::containers::concepts::archetypes
