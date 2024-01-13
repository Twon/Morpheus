#pragma once

#include <functional>

namespace morpheus::meta::concepts
{

/// \concept Satisfies
///     Higher order helper concept for applying type traits as useable concepts.
/// \code
///     concept ExampleConcept = requires(T t, T const tc)
///     {
///         { T.getType() } -> Trait<std::is_enum>;
///     };
/// \endcode
/// \notes
///     See [Lightning Talk: Higher-Order Template Metaprogramming with C++23 - Ed Catmur - CppCon 2023](https://www.youtube.com/watch?v=KENynEQoqCo)
template <class T, auto C>
concept Satisfies = C.template operator()<T>();

} // namespace morpheus::meta::concepts
