#include <type_traits>

namespace morpheus
{

// https://stackoverflow.com/questions/11251376/how-can-i-check-if-a-type-is-an-instantiation-of-a-given-class-template#comment14786989_11251408
template < template <typename...> class Template, typename T >
struct is_specialisation_of : std::false_type {};

template < template <typename...> class Template, typename... Args >
struct is_specialisation_of< Template, Template<Args...> > : std::true_type {};

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2098r0.pdf
template< class T, template<class...> class Primary >
inline constexpr bool is_specialization_of_v = is_specialisation_of<T, Primary>::value;

} // namespace morpheus