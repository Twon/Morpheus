#pragma once

#include <concepts>
#include <iterator>
#include <utility>

namespace morpheus::containers::concepts
{

/// \concept Container
///     Concept capturing the requirements for a container as outline in the standard at
///     <a href="https://eel.is/c++draft/container.requirements">[container.requirements]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/Container">Container</a>.
template <typename C>
concept Container = requires(C c) {
    typename C::value_type;
    typename C::reference;
    typename C::const_reference;
    requires std::forward_iterator<typename C::iterator>;
    requires std::forward_iterator<typename C::const_iterator>;
    requires std::signed_integral<typename C::difference_type>;
    requires std::unsigned_integral<typename C::size_type>;
    requires std::convertible_to<typename C::iterator, typename C::const_iterator>;
    requires std::regular<C>;
    { begin(c) } -> std::same_as<typename C::iterator>;
    { end(c) } -> std::same_as<typename C::iterator>;
    { cbegin(std::as_const(c)) } -> std::same_as<typename C::const_iterator>;
    { cend(std::as_const(c)) } -> std::same_as<typename C::const_iterator>;
    requires(not std::bidirectional_iterator<typename C::iterator>) or requires {
        { size(c) } -> std::same_as<typename C::size_type>;
    };
    { c.max_size() } -> std::same_as<typename C::size_type>;
    { empty(c) } -> std::same_as<bool>;
};

} // namespace morpheus::containers::concepts
