#pragma once

#include "morpheus/core/containers/concepts/container.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/meta/is_array.hpp"

#include <concepts>
#include <initializer_list>
#include <forward_list>
#include <string>
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
    { T(std::from_range, ranges::subrange<typename T::iterator>{}) };
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { T(il) };
    { t = il };
    { t.insert(i, v) } -> std::same_as<typename T::iterator>;
    { t.insert(i, std::move(v)) } -> std::same_as<typename T::iterator>;
    { t.insert(i, s, v) } -> std::same_as<typename T::iterator>;
    { t.insert(i, i, i) } -> std::same_as<typename T::iterator>;
#if (__cpp_lib_containers_ranges >= 202202L)
    { t.insert_range(i, ranges::subrange<typename T::iterator>{}) } -> std::same_as<typename T::iterator>;
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { t.insert(i, il) } -> std::same_as<typename T::iterator>;
    { t.erase(i) } -> std::same_as<typename T::iterator>;
    { t.erase(i, i) } -> std::same_as<typename T::iterator>;
    { t.clear() } -> std::same_as<void>;
    { t.assign(i, i) } -> std::same_as<void>;
#if (__cpp_lib_containers_ranges >= 202202L)
    { t.assign_range(ranges::subrange<typename T::iterator>{}) } -> std::same_as<void>;
#endif // (__cpp_lib_containers_ranges >= 202202L)
    { t.assign(il) } -> std::same_as<void>;
    { t.assign(s, v) } -> std::same_as<void>;
};

/// \concept StrictSequence
///     Concept strictly capturing the requirements for a sequence container as outline in the standard at
///     <a href="https://eel.is/c++draft/sequence.reqmts">[sequence.requirements]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/SequenceContainer">SequenceContainer</a>.
///     The requirements <a href="https://eel.is/c++draft/sequence.reqmts">[sequence.requirements]</a> don't
///     actually match numerous types listed as sequence containers.  This includes:
///      - std::string
///      - std::forward_list
///      - std::array
///     Hoever they are listed as as Sequence types while having interfaces that differ from the Sequence
///     container requirements so this extension concept exactly mirrors that requirement.
template <typename T>
concept StrictSequence = meta::is_array_v<T> || 
                         std::same_as<T, std::string> ||
                         std::same_as<T, std::forward_list<typename T::value_type>> ||
                         Sequence<T>; 


} // namespace morpheus::containers::concepts
