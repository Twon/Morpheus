#pragma once

#include <functional>

namespace morpheus::meta::concepts
{

/// \concept Trait
///     Higher order helper concept for applying type traits as usable concepts.
/// \code
///     concept ExampleConcept = requires(T t, T const tc)
///     {
///         { T.getType() } -> Trait<std::is_enum>;
///     };
/// \endcode
/// \note
///     See [Lightning Talk: Higher-Order Template Metaprogramming with C++23 - Ed Catmur - CppCon 2023](https://www.youtube.com/watch?v=KENynEQoqCo)
template <class T, template <typename, typename...> class TT, class... Args>
concept Trait = TT<T, Args...>::value;

} // namespace morpheus::meta::concepts
