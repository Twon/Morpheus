#pragma once

#include <type_traits>

namespace morpheus::meta
{

template <class Container, class T>
struct Contains;

template <template <typename...> class Container, typename T, typename... Ts>
struct Contains<Container<Ts...>, T> : std::bool_constant<(std::is_same_v<T, Ts> || ...)>
{};

} // namespace morpheus::meta
