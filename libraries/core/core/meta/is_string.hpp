#pragma once

#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::meta
{

template< class T >
inline constexpr bool is_string_v = false;

template <class T, class Traits, class Alloc>
inline constexpr bool is_string_v< std::basic_string<T, Traits, Alloc> > = true;

template< class T >
inline constexpr bool is_string_view_v = false;

template <class T, class Traits>
inline constexpr bool is_string_view_v< std::basic_string_view<T, Traits> > = true;

} // namespace morpheus::meta