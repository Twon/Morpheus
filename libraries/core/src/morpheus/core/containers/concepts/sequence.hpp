#pragma once

#include "morpheus/core/containers/concepts/container.hpp"

#include "morpheus/core/conformance/ranges.hpp"

#include <concepts>
#include <initializer_list>
#include <version>

namespace morpheus::containers::concepts
{

/// \concept Sequence
///     Concept capturing the requirements for a sequence container as outline in the standard at
///     <a href="https://eel.is/c++draft/sequence.reqmts">[sequence.requirements]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/SequenceContainer">SequenceContainer</a>.
template <typename T>
concept Sequence = Container<T> && requires(T t, typename T::value_type v, typename T::size_type s, typename T::iterator i, std::initializer_list<typename T::value_type> il){
    { T(s, v) };
    { T(i, i) };
#if (__cpp_lib_containers_ranges >= 202202L)
    { T(std::from_range, ranges::subrange<typename T::value_type>{}) };
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { T(il) };
    { t = il };
    { t.insert(i, v) } -> std::same_as<typename T::iterator>;
    { t.insert(i, std::move(v)) } -> std::same_as<typename T::iterator>;
    { t.insert(i, s, v) } -> std::same_as<typename T::iterator>;
    { t.insert(i, i, i) } -> std::same_as<typename T::iterator>;
#if (__cpp_lib_containers_ranges >= 202202L)
    { t.insert(i, ranges::subrange<typename T::value_type>{}) } -> std::same_as<typename T::iterator>;
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { t.insert(i, il) } -> std::same_as<typename T::iterator>;
    { t.erase(i) } -> std::same_as<typename T::iterator>;
    { t.erase(i, i) } -> std::same_as<typename T::iterator>;
    { t.clear() } -> std::same_as<void>;
    { t.assign(i, i) } -> std::same_as<void>;
#if (__cpp_lib_containers_ranges >= 202202L)
    { t.assign_range(ranges::subrange<typename T::value_type>{}) } -> std::same_as<void>;
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { t.assign(il) } -> std::same_as<void>;
    { t.assign(s, v) } -> std::same_as<void>;
};

} // namespace morpheus::containers::concepts
