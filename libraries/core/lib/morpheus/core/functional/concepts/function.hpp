#pragma once

#include <concepts>
#include <type_traits>

namespace morpheus::functional::concepts
{

/// \concept Function
///     Concept capturing the requirements for a function object, a named requirement outlined in the standard at
///     <a href="https://eel.is/c++draft/func.require">[func.require]</a>, details at
///     <a href="https://en.cppreference.com/w/cpp/named_req/FunctionObject">FunctionObject</a>.
template <typename T, typename... Args>
concept Function = requires(T t) {
    requires std::is_object_v<T>;
    requires std::invocable<T, Args...>;
};

} // namespace morpheus::functional::concepts
