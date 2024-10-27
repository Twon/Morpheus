#pragma once

#include "morpheus/core/containers/concepts/detail/return_types.hpp"
#include "morpheus/core/containers/concepts/allocator_aware.hpp"
#include "morpheus/core/functional/concepts/hash.hpp"

#include <concepts>
#include <initializer_list>

namespace morpheus::containers::concepts
{

/// \concept Unordered
///     Concept capturing the requirements for an unordered associative container as outline in the standard at
///     <a href="https://eel.is/c++draft/unord.req">[unord.req]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer">UnorderedAssociativeContainerr</a>.
template <typename T>
concept Unordered = AllocatorAware<T> && requires(T t, typename T::value_type v, typename T::key_type k, typename T::size_type s, typename T::iterator i,
                                                  typename T::const_iterator ci, typename T::hasher h, typename T::key_equal e, typename T::local_iterator l,
                                                  typename T::node_type n, std::initializer_list<typename T::value_type> il)
{
    requires functional::concepts::Hash<typename T::hasher, typename T::key_type>;
    requires (std::default_initializable<typename T::key_equal>) && (std::copy_constructible<typename T::key_equal>);
    { T(s, h, e) };
    { T(s, h) };
    { T(s) };
    { T(i, i, s, h, e) };
    { T(i, i, s, h) };
    { T(i, i, s) };
    { T(i, i) };
#if (__cpp_lib_containers_ranges >= 202202L)
    { T(std::from_range, ranges::subrange<typename T::iterator>{}, s, h, e) };
    { T(std::from_range, ranges::subrange<typename T::iterator>{}, s, h) };
    { T(std::from_range, ranges::subrange<typename T::iterator>{}, s) };
    { T(std::from_range, ranges::subrange<typename T::iterator>{}) };
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { T(il, s, h, e) };
    { T(il, s, h) };
    { T(il, s) };
    { T(il) };
    { t = il };
    { std::as_const(t).hash_function() } -> std::same_as<typename T::hasher>;
    { std::as_const(t).key_eq() } -> std::same_as<typename T::key_equal>;
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
    { t.equal_range(k) } -> detail::BoundReturnType<T>;
    { std::as_const(t).equal_range(k) } -> detail::BoundConstReturnType<T>;
    { std::as_const(t).bucket_count() } -> std::same_as<typename T::size_type>;
    { std::as_const(t).max_bucket_count() } -> std::same_as<typename T::size_type>;
    { std::as_const(t).bucket(s) } -> std::same_as<typename T::size_type>;
    { std::as_const(t).bucket_size(s) } -> std::same_as<typename T::size_type>;
    { t.begin(s) } -> std::same_as<typename T::local_iterator>;
    { std::as_const(t).begin(s) } -> std::same_as<typename T::const_local_iterator>;
    { t.end(s) } -> std::same_as<typename T::local_iterator>;
    { std::as_const(t).end(s) } -> std::same_as<typename T::const_local_iterator>;
    { std::as_const(t).load_factor() } -> std::same_as<float>;
    { std::as_const(t).max_load_factor() } -> std::same_as<float>;
    { t.max_load_factor(float{}) } -> std::same_as<void>;
    { t.rehash(s) } -> std::same_as<void>;
    { t.reserve(s) } -> std::same_as<void>;
};

} // namespace morpheus::containers::concepts
