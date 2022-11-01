#pragma once

#include <type_traits>

namespace morpheus::meta
{

/// \var is_complete_v
///     Template variable specialises to deletect when a type is consider complete by the compiler.  Types considered
///     incomplete can only be stored indirectly (as a reference or pointer) information on which base size to store
///     the type is unknown.
template <typename T, typename = void>
constexpr bool is_complete_v = false;

template <typename T>
constexpr bool is_complete_v<T, std::enable_if_t<sizeof(T) != 0>> = true;

} // namespace morpheus::meta