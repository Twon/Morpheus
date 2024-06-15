#pragma once

#include "morpheus/core/containers/concepts/container.hpp"

#include <concepts>
#include <utility>

namespace morpheus::containers::concepts
{

/// \concept AllocatorAware
///     Concept capturing the requirements for an allocator aware container as outline in the standard at
///     <a href="https://eel.is/c++draft/container.alloc.reqmts">[container.alloc.reqmts]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer">AllocatorAwareContainer</a>.
template <typename X>
concept AllocatorAware = Container<X> && requires(X x, X&& rx, typename X::allocator_type a){
    requires std::same_as<typename X::allocator_type::value_type, typename X::value_type>;
    requires std::default_initializable<X>;
    { X(a) };
    { X(std::as_const(x), a) };
    { X(std::move(rx)) };
    { X(std::move(rx), a) };
    { std::as_const(x).get_allocator() } -> std::same_as<typename X::allocator_type>;
    { x = x } -> std::same_as<X&>;
    { x = rx } -> std::same_as<X&>;
    { x.swap(x) } -> std::same_as<void>;
};

} // namespace morpheus::containers::concepts
