
#pragma once

#include <concepts>
#include <memory>

namespace morpheus::memory::concepts
{

/// \concept Deleter
///     A deleter specified the destruction policity of a given type.
/// \tparam Callable The callable destruction policy.
/// \tparam Arg The argument to ne destroyed.
template <typename Callable, typename Arg>
concept Deleter = requires(Callable&& c, Arg* a) {
    { std::forward<Callable>(c)(a) } -> std::same_as<void>;
};

} // namespace morpheus::memory::concepts
