#pragma once

#include <type_traits>

namespace morpheus::meta
{

/// Traits to detect
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
inline constexpr bool IsNothrowInvocableV<Callable(Args...)> = IsNothrowInvocable<Callable, Args...>;


/// \concept IsConstInvocable
///     Ensures an callable is invokable as a constant.
template <typename Callable, typename... Args>
concept IsConstInvocable = requires(Callable const c, Args... args)
{
    c(args...);
};

template<typename T>
inline constexpr bool IsConstInvocableV = false;

template <typename Callable, typename... Args>
inline constexpr bool IsConstInvocableV<Callable(Args...)> = IsConstInvocable<Callable, Args...>;


/// \concept IsInvocableResult
///     Ensures an callable is invokable in a noexcept context.
//template <class Result, class Callable, class... Args>
//inline constexpr bool IsInvocableResult = IsNothrowInvocable<Callable, Args...> and std::is_invocable_r_v<Result, Callable, Args...>;




//constexpr auto noexcept_deduction(R() noexcept(X))->std::true_type;
//constexpr auto noexcept_deduction(...)->std::false_type;

} // namespace morpheus::meta