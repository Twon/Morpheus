#pragma once

#include <morpheus/core/conformance/version.hpp>

#if (__cpp_explicit_this_parameter >= 202110L)
    #include <boost/hana/functional/curry.hpp>
#endif // (__cpp_explicit_this_parameter >= 202110L)

#include <concepts>
#include <functional>
#include <utility>

namespace morpheus::functional
{

#if (__cpp_explicit_this_parameter >= 202110L)

/// \fn curry
///     Currying is a technique in which we consider a function takign multuiple arguments and turn it into a function which takes a single argument and
///     returns a function to handle the remaining arguments.
/// \note
///     [Applicative: The Forgotten Functional Pattern in C++ - Ben Deane - CppNow 2023](https://youtu.be/At-b4PHNxMg?si=hDI3zgmfPwrrIxoe&t=1313)
template <typename F, typename... Args>
constexpr auto curry(F&& f, Args&&... args) -> decltype(auto)
{
    if constexpr (std::invocable<F, Args...>)
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    else
    {
        return [f = std::forward<F>(f), ... args = std::forward<Args>(args)]<typename Self, typename... As>(this Self&& self, As&&... as) -> decltype(auto)
        { return curry(std::forward_like<Self>(f), std::forward_like<Self>(args)..., std::forward<As>(as)...); };
    }
}

#else

namespace details
{

template <typename F, typename... Stored>
struct curried
{
    F f;
    std::tuple<Stored...> stored;

    template <typename Fn, typename Tup>
    constexpr curried(Fn&& fn, Tup&& tup)
        : f(std::forward<Fn>(fn))
        , stored(std::forward<Tup>(tup))
    {}

    template <typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const&
    {
        return call(std::forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) &&
    {
        return call(std::forward<Args>(args)...);
    }

private:
    template <typename... Args>
    constexpr decltype(auto) call(Args&&... args) const&
    {
        return std::apply([&](auto&&... stored_args) -> decltype(auto) { return curry(f, stored_args..., std::forward<Args>(args)...); }, stored);
    }

    template <typename... Args>
    constexpr decltype(auto) call(Args&&... args) &&
    {
        return std::apply([&](auto&&... stored_args) -> decltype(auto) { return curry(std::move(f), std::move(stored_args)..., std::forward<Args>(args)...); },
                          std::move(stored));
    }
};

} // namespace details

template <typename F, typename... Args>
constexpr auto curry(F&& f, Args&&... args) -> decltype(auto)
{
    if constexpr (std::invocable<F, Args...>)
    {
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    }
    else
    {
        return details::curried<std::decay_t<F>, std::decay_t<Args>...>(std::forward<F>(f), std::tuple<std::decay_t<Args>...>(std::forward<Args>(args)...));
    }
}
#endif // (__cpp_explicit_this_parameter >= 202110L)

} // namespace morpheus::functional
