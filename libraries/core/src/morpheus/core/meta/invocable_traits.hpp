#pragma once

#include <type_traits>

namespace morpheus::meta
{

/// Traits to detect
/// - noexcept status
/// - constness status
/// - volatile status
/// - function arguments
/// 

/// \concept IsNothrowInvocable
///     Ensures an callable is invokable in a noexcept context.
template <typename Callable, typename... Args>
concept IsNothrowInvocable = requires(Callable c, Args... args) 
{ 
    requires noexcept(c(args...));
};

template<typename T>
inline constexpr bool IsNothrowInvocableV = false;

template <typename Callable, typename... Args>
inline constexpr bool IsNothrowtInvocableV = IsNothrowInvocable<Callable, Args...>;


/// \concept IsInvocableResult
///     Ensures an callable is invokable in a noexcept context.
//template <class Result, class Callable, class... Args>
//inline constexpr bool IsInvocableResult = IsNothrowInvocable<Callable, Args...> and std::is_invocable_r_v<Result, Callable, Args...>;




//constexpr auto noexcept_deduction(R() noexcept(X))->std::true_type;
//constexpr auto noexcept_deduction(...)->std::false_type;

} // namespace morpheus::meta