#pragma once

#include <type_traits>

namespace morpheus::meta
{
/*
// https://stackoverflow.com/questions/11251376/how-can-i-check-if-a-type-is-an-instantiation-of-a-given-class-template#comment14786989_11251408
template < class T >
struct is_specialisation_of : std::false_type {};

template < template <typename...> class Template, typename... Args >
struct is_specialisation_of< Template<Args...> > : std::true_type {};

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2098r0.pdf
template< class T >
inline constexpr bool is_specialisation_of_v = false;

template < template <typename...> class Template, typename... Args >
inline constexpr bool is_specialisation_of_v< Template<Args...> > = true;
*/

template <template <typename...> class Template, typename T>
struct is_specialisation_of : std::false_type {};

template <template <typename...> class Template, typename... T>
struct is_specialisation_of<Template, Template<T...>> : std::true_type {};

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2098r0.pdf
template <template <typename...> class Template, typename T>
inline constexpr bool is_specialisation_of_v = false;

template <template <typename...> class Template, typename... T>
inline constexpr bool is_specialisation_of_v<Template, Template<T...>> = true;

template <template <typename...> class Template, typename... T>
concept IsSpecialisationOf = is_specialisation_of_v<Template, T...>;

} // namespace morpheus::meta
