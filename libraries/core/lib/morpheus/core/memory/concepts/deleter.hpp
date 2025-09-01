
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

/// \struct default_copy
///     Default copier uses default allocation in conjunction with copy assignment operator of T.
// template <class T>
// struct default_copy
// {
//     /// The deleter type to be used to deallocate objects created by the copier.
//     using deleter_type = std::default_delete<T>;

//     /// Create a copy of the input.
//     constexpr T* operator()(T const& t) const { return new T(t); }
// };

} // namespace morpheus::memory::concepts
