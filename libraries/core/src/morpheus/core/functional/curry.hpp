#pragma once

#include <concepts>
#include <functional>
#include <utility>

namespace morpheus::functional
{

#if (__cpp_explicit_this_parameter >= 202110L)

/// \fn curry
///     Currying is a technique in which we consider a function takign multuiple arguments and turn it into a function which takes a single argument and
///     returns a funtion to handle the remaining arguments.
/// \note
///     [Applicative: The Forgotten Functional Pattern in C++ - Ben Deane - CppNow 2023](https://youtu.be/At-b4PHNxMg?si=hDI3zgmfPwrrIxoe&t=1313)
template <typename F, typename... Args>
constexpr auto curry(F&& f, Args&&... args) -> decltype(auto)
{
    if constexpr (std::invocable<F, Args...>)
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    else
    {
        return [f = std::forward<F>(f), ...args = std::forward<Args>(args)]<typename Self, typename... As>(this Self&& self, As&&... as) -> decltype(auto)
        {
            return curry(std::forward_like<Self>(f), std::forward_like<Self>(args)..., std::forward<As>(as)...);
        };
    }
}

#endif // (__cpp_explicit_this_parameter >= 202110L)

} // namespace morpheus::functional
