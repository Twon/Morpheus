#pragma once

#include <type_traits>

namespace morpheus::meta::concepts
{

/// \concept Copyable
///     Verifies a given T as copyable type.
template <typename T>
concept Copyable = requires(T t)
{
    requires !std::copy_constructible<T>;
    requires !std::assignable_from<T&, T>;
};

} // namespace morpheus::meta::concepts
