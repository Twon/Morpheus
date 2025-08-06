#pragma once

#include "morpheus/core/functional/concepts/function.hpp"

#include <concepts>

namespace morpheus::functional::concepts
{

/// \concept Hash
///     Concept capturing the requirements for a hash, a named requirement outlined in the standard at
///     <a href="https://eel.is/c++draft/hash.requirements">[hash.requirements]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/Hash">Hash</a>.
template <typename T, typename Arg>
concept Hash = requires(T t) {
    requires std::copy_constructible<T>;
    requires std::destructible<T>;
    requires Function<T, Arg>;
};

} // namespace morpheus::functional::concepts
