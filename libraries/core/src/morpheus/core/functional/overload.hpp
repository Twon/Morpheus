#pragma once

#include <utility>

namespace morpheus::functional
{

/// \class Overload
///     Starting point or an overload type build of lambdas
/// \note
///     Following the example of https://www.modernescpp.com/index.php/visiting-a-std-variant-with-the-overload-pattern
template<typename... Ts>
struct Overload : Ts...
{
    using Ts::operator()...;
};

template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;

template<class... Ts>
auto makeVisitor(Ts&&... ts)
{
    return Overload<Ts...>(std::forward<Ts>(ts)...);
}

} // namespace morpheus::functional