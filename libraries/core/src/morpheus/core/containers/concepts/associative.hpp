#pragma once

#include "morpheus/core/containers/concepts/detail/return_types.hpp"
#include "morpheus/core/containers/concepts/allocator_aware.hpp"

#include <concepts>
#include <initializer_list>

namespace morpheus::containers::concepts
{

/// \concept Associative
///     Concept capturing the requirements for an associative container as outline in the standard at
///     <a href="https://eel.is/c++draft/container.requirements#associative.reqmts">[associative.reqmts]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/AssociativeContainer">AssociativeContainer</a>.
template <typename T>
concept Associative = AllocatorAware<T> && requires(T t, typename T::value_type v, typename T::key_type k, typename T::size_type s, typename T::iterator i,
                                                    typename T::const_iterator ci, typename T::key_compare c, typename T::node_type n,
                                                    std::initializer_list<typename T::value_type> il)
{
    requires (std::default_initializable<typename T::key_compare>) and (std::copy_constructible<typename T::key_compare>);
    { T(c) };
    { T(i, i, c) };
    { T(i, i) };
#if (__cpp_lib_containers_ranges >= 202202L)
    { T(std::from_range, ranges::subrange<typename T::iterator>{}, c) };
    { T(std::from_range, ranges::subrange<typename T::iterator>{}) };
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { T(il, c) };
    { T(il) };
    { t = il };
    { std::as_const(t).key_comp() } -> std::same_as<typename T::key_compare>;
    { std::as_const(t).value_comp() } -> std::same_as<typename T::value_compare>;
    { t.emplace() } -> detail::InsertReturnType<T>;
    { t.emplace_hint(i) } -> std::same_as<typename T::iterator>;
    { t.insert(v) } -> detail::InsertReturnType<T>;
    { t.insert(ci, v) } -> std::same_as<typename T::iterator>;
    { t.insert(i, i) } -> std::same_as<void>;
#if (__cpp_lib_containers_ranges >= 202202L)
    { t.insert_range(ranges::subrange<typename T::iterator>{}) } -> std::same_as<void>;
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { t.insert(il) } -> std::same_as<void>;
    { t.insert(std::move(n)) } -> detail::InsertNodeHandleReturnType<T>;
    { t.insert(ci, std::move(n)) } -> std::same_as<typename T::iterator>;
    { t.extract(k) } -> std::same_as<typename T::node_type>;
    { t.extract(ci) } -> std::same_as<typename T::node_type>;
    { t.merge(t) } -> std::same_as<void>;
    { t.erase(i) } -> std::same_as<typename T::iterator>;
    { t.erase(ci) } -> std::same_as<typename T::iterator>;
    { t.erase(i, i) } -> std::same_as<typename T::iterator>;
    { t.erase(ci, ci) } -> std::same_as<typename T::iterator>;
    { t.erase(k) } -> std::same_as<typename T::size_type>;
    { t.clear() } -> std::same_as<void>;
    { t.find(k) } -> std::same_as<typename T::iterator>;
    { std::as_const(t).find(k) } -> std::same_as<typename T::const_iterator>;
    { std::as_const(t).count(k) } -> std::same_as<typename T::size_type>;
    { std::as_const(t).contains(k) } -> std::same_as<bool>;
    { t.lower_bound(k) } -> detail::BoundReturnType<T>;
    { std::as_const(t).lower_bound(k) } -> detail::BoundConstReturnType<T>;
    { t.equal_range(k) } -> detail::BoundReturnType<T>;
    { std::as_const(t).equal_range(k) } -> detail::BoundConstReturnType<T>;
    { t.upper_bound(k) } -> detail::BoundReturnType<T>;
    { std::as_const(t).upper_bound(k) } -> detail::BoundConstReturnType<T>;
};

} // namespace morpheus::containers::concepts
