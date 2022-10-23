#pragma once

#include <type_traits>

namespace morpheus::meta
{

template <typename T, typename = void>
constexpr bool is_complete_v = false;

template <typename T>
constexpr bool is_complete_v<T, std::enable_if_t<sizeof(T) != 0>> = true;

} // namespace morpheus::meta