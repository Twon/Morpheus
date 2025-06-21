#pragma once

#include <functional>

namespace morpheus::meta::concepts
{

/// \concept Satisfies
///     Higher order helper concept for ensureing a concept satisfies an input trait.  The apply the trait this should be wrapped in shark quotes, i.e
///     []< traits to constraint >{}
/// \code
///     concept RangeOver = std::ranges::range<T> and Satisfies<std::ranges::range_value_t<T>, C>
///
///     concept ExampleUsage = requires(T t)
///     {
///         { t.ids() } -> RangeOver<[]<std::integral>()>;
///     }
/// \endcode
/// \note
///     See [Lightning Talk: Higher-Order Template Metaprogramming with C++23 - Ed Catmur - CppCon 2023](https://www.youtube.com/watch?v=KENynEQoqCo)
template <class T, auto C>
concept Satisfies = requires { C.template operator()<T>(); };

/// \concept SatisfiesAfter
///     Higher order helper concept for ensureing a concept satisfies an input trait, after an applied transformation.  The apply the trait this should
///     be wrapped in shark quotes, i.e []< traits to constraint >{}
/// \code
///     class B {};
///     class D : public B {};
///
///     concept ExampleUsage = requires(T t)
///     {
///         { t.d() } -> SatisfiesAfter<std::remove_cvref, []<std::derived_from<B>>()>;
///     }
/// \endcode
/// \note
///     See [Lightning Talk: Higher-Order Template Metaprogramming with C++23 - Ed Catmur - CppCon 2023](https://www.youtube.com/watch?v=KENynEQoqCo)
template <class T, template <typename> class TT, auto C>
concept SatisfiesAfter = Satisfies<typename TT<T>::type, C>;

} // namespace morpheus::meta::concepts
