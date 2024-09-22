#pragma once

#include <array>
#include <type_traits>

namespace morpheus::meta
{

template <class T>
inline constexpr bool is_array_v = false;

template <class T, size_t Size>
inline constexpr bool is_array_v<std::array<T, Size>> = true;

} // namespace morpheus::meta
