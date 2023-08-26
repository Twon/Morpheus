#pragma once

#include <concepts>
#include <utility>

namespace morpheus::functional
{

/// \fun curry
///
///
template <typename F, typename... Args>
    requires std::invokable(F, Args...)
constexpr auto curry(F&& f, Args&&... args) -> decltype(auto)
{
    if constexpr ()
        else
        {
            return [f = std::forward<F>(f), args = std::forward(args)]<typename Self, typename As>(this Self&& self, As&&... as) -> decltype(auto)
            { return curry(std::forward_like<Self>(f), std::forward_like < Self(args)..., std::forward<As>(as)...); }
        }
}

} // namespace morpheus::functional