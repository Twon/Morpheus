#pragma once

#include "morpheus/containers/concepts/archetypes/allocator_aware.hpp"

#include "morpheus/core/conformance/ranges.hpp"

#include <compare>
#include <functional>

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
struct Unordered : public AllocatorAware, detail::Multi<multi>, detail::Mapped<mapped>
{
    using value_type = typename detail::Mapped<mapped>::value_type;
    using key_type = typename detail::Mapped<mapped>::key_type;
    using allocator_type = typename detail::Mapped<mapped>::allocator_type;
    using hasher = std::hash<int>;
    using key_equal = std::equal_to<int>;
    struct node_type{};
    struct local_iterator{};
    using const_local_iterator = local_iterator const;

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
    using AllocatorAware::begin;
    using AllocatorAware::end;

    constexpr Unordered();
    constexpr Unordered(size_type, hasher const&, key_equal const&);
    constexpr Unordered(size_type, hasher const&);
    constexpr Unordered(size_type);
    constexpr Unordered(iterator, iterator, size_type, hasher const&, key_equal const&);
    constexpr Unordered(iterator, iterator, size_type, hasher const&);
    constexpr Unordered(iterator, iterator, size_type);
    constexpr Unordered(iterator, iterator);
    //constexpr Unordered(iterator, iterator, key_compare const&);
#if (__cpp_lib_containers_ranges >= 202202L)
    constexpr Unordered(std::from_range_t, ranges::range auto, size_type, hasher const&, key_equal const&);
    constexpr Unordered(std::from_range_t, ranges::range auto, size_type, hasher const&);
    constexpr Unordered(std::from_range_t, ranges::range auto, size_type);
    constexpr Unordered(std::from_range_t, ranges::range auto);
#endif // (__cpp_lib_containers_ranges >= 202202L)
    constexpr Unordered(std::initializer_list<value_type>, size_type, hasher const&, key_equal const&);
    constexpr Unordered(std::initializer_list<value_type>, size_type, hasher const&);
    constexpr Unordered(std::initializer_list<value_type>, size_type);
    constexpr Unordered(std::initializer_list<value_type>);
    constexpr Unordered(Unordered const&);
    constexpr Unordered(Unordered&&);
    constexpr Unordered& operator=(Unordered const&);
    constexpr Unordered& operator=(Unordered&&);
    constexpr Unordered& operator=(std::initializer_list<value_type>);

    constexpr allocator_type get_allocator() const noexcept;

    constexpr hasher hash_function() const;
    constexpr key_equal key_eq() const;

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

    constexpr void merge(Unordered const&);

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

    BoundReturnType equal_range(key_type const&);
    BoundConstReturnType equal_range(key_type const&) const;

    constexpr size_type bucket_count() const;
    constexpr size_type max_bucket_count() const;
    constexpr size_type bucket(size_type) const;
    constexpr size_type bucket_size(size_type) const;
    constexpr local_iterator begin(size_type) noexcept;
    constexpr local_iterator end(size_type) noexcept;
    constexpr const_local_iterator begin(size_type) const noexcept;
    constexpr const_local_iterator end(size_type) const noexcept;
    constexpr float load_factor() const;
    constexpr float max_load_factor() const;
    constexpr void max_load_factor(float);

    constexpr void rehash(size_type);
    constexpr void reserve(size_type);

    constexpr auto operator<=>(Unordered const&) const = default;


};

} // namespace morpheus::containers::concepts::archetypes
