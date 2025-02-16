#pragma once

#include "morpheus/containers/concepts/archetypes/allocator_aware.hpp"

#include "morpheus/core/conformance/ranges.hpp"

#include <compare>
#include <functional>
#include <initializer_list>
#include <type_traits>

namespace morpheus::containers::concepts::archetypes
{

namespace detail
{

template<bool M = false>
struct Multi
{
    struct insert_return_type {};

    constexpr auto operator<=>(Multi const&) const = default;
};

template<>
struct Multi<true>
{
    constexpr auto operator<=>(Multi const&) const = default;
};


template<bool M = false>
struct Mapped
{
    using value_type = int;
    using key_type = value_type;
    using allocator_type = std::allocator<value_type>;

    constexpr auto operator<=>(Mapped const&) const = default;
};

template<>
struct Mapped<true>
{
    using mapped_type = int;
    using value_type = std::pair<const int, mapped_type>;
    using key_type = typename value_type::first_type;
    using allocator_type = std::allocator<value_type>;
    constexpr auto operator<=>(Mapped const&) const = default;
};

} // namespace morpheus::containers::concepts::archetypes::detail

template<bool multi = false, bool mapped = false>
struct Associative : AllocatorAware, detail::Multi<multi>, detail::Mapped<mapped>
{
    using value_type = typename detail::Mapped<mapped>::value_type;
    using key_type = typename detail::Mapped<mapped>::key_type;
    using allocator_type = typename detail::Mapped<mapped>::allocator_type;
    using key_compare = std::less<int>;
    using value_compare = key_compare;
    struct node_type{};

    using InsertReturnType = std::conditional_t<multi, iterator, std::pair<iterator, bool>>;

    template <typename, typename = void>
    struct GetInsertReturnType {
        using type = typename AllocatorAware::iterator; // Default if not available
    };

    template <typename T>
    struct GetInsertReturnType<T, std::void_t<typename T::insert_return_type>> {
        using type = typename T::insert_return_type; // Use if available
    };

    // Alias to extract type easily
    using InsertNodeHandleReturnType = typename GetInsertReturnType<detail::Multi<multi>>::type;

    using BoundReturnType = std::conditional_t<multi, iterator, std::pair<iterator, iterator>>;
    using BoundConstReturnType = std::conditional_t<multi, const_iterator, std::pair<const_iterator, const_iterator>>;

    using AllocatorAware::AllocatorAware;
    using detail::Mapped<mapped>::Mapped;

    constexpr Associative();
    constexpr Associative(key_compare const&);
    constexpr Associative(iterator, iterator, key_compare const&);
    constexpr Associative(iterator, iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr Associative(std::from_range_t, ranges::range auto, key_compare const&);
    constexpr Associative(std::from_range_t, ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr Associative(std::initializer_list<value_type>, key_compare const&);
    constexpr Associative(std::initializer_list<value_type>);
    constexpr Associative(Associative const&);
    constexpr Associative(Associative&&);
    constexpr Associative& operator=(Associative const&);
    constexpr Associative& operator=(Associative&&);
    constexpr Associative& operator=(std::initializer_list<value_type>);

    constexpr allocator_type get_allocator() const noexcept;

    constexpr key_compare key_comp() const;
    constexpr value_compare value_comp() const;

    constexpr InsertReturnType emplace(auto... args);
    constexpr iterator emplace_hint(iterator, auto... args);

    constexpr InsertReturnType insert(value_type);
    constexpr iterator insert(const_iterator, value_type);
    constexpr void insert(const_iterator, const_iterator);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr void insert_range(ranges::range auto);
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

    constexpr auto operator<=>(Associative const&) const = default;


};

} // namespace morpheus::containers::concepts::archetypes
