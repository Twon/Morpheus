#pragma once

#include "morpheus/core/containers/concepts/container.hpp"

#include <concepts>
#include <iterator>
#include <utility>

namespace morpheus::containers::concepts
{

/// \concept Reversible
///     Concept capturing the requirements for a reversible container, a named requirement outlined in the standard at
///     <a href="https://eel.is/c++draft/container.rev.reqmts">[container.rev.reqmts]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/ReversibleContainer">ReversibleContainer</a>.
template <typename T>
concept Reversible = Container<T> && requires(T t){
    typename T::reverse_iterator;
    typename T::const_reverse_iterator;
    requires std::same_as<typename T::reverse_iterator, std::reverse_iterator<typename T::iterator>>;
    requires std::same_as<typename T::const_reverse_iterator, std::reverse_iterator<typename T::const_iterator>>;
    { rbegin(t) } -> std::same_as<typename T::reverse_iterator>;
    { rend(t) } -> std::same_as<typename T::reverse_iterator>;
    { crbegin(std::as_const(t)) } -> std::same_as<typename T::const_reverse_iterator>;
    { crend(std::as_const(t)) } -> std::same_as<typename T::const_reverse_iterator>;
};

} // namespace morpheus::containers::concepts
