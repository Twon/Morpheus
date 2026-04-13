#pragma once

#include <type_traits>

namespace morpheus::meta::concepts
{

/// \concept Constructible
///     Ensures a type is constructible from a set of arguments.
template <typename T, class... Args>
concept Constructible = std::is_constructible_v<T, Args...>;

/// \concept DefaultConstructible
///     Ensures a type is default constructible.
template <typename T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

/// \concept TriviallyConstructible
///     Ensures a type is trivially constructible from a set of arguments.
template <typename T, class... Args>
concept TriviallyConstructible = std::is_trivially_constructible_v<T, Args...>;

/// \concept DefaultTriviallyConstructible
///     Ensures a type is default trivially constructible.
template <typename T>
concept DefaultTriviallyConstructible = std::is_trivially_default_constructible_v<T>;

/// \concept NothrowConstructible
///     Ensures a type is nothrow constructible from a set of arguments.
template <typename T, class... Args>
concept NothrowConstructible = std::is_nothrow_constructible_v<T, Args...>;

/// \concept DefaultNothrowConstructible
///     Ensures a type is default nothrow constructible.
template <typename T>
concept DefaultNothrowConstructible = std::is_nothrow_default_constructible_v<T>;

} // namespace morpheus::meta::concepts
