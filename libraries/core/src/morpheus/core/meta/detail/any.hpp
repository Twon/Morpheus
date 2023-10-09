#pragma once

#include <cstdint>

namespace morpheus::meta::detail
{

/// \struct Any
///     To be used in a SFINAE context to detect if a parameter exists.
/// \code
///     std::void_t<
/// \endcode
struct Any
{
    /// Conversion operator to any type.  Only to be used in meta context to not implemented to guard against
    /// inappropriate use
    template <typename T>
    constexpr operator T() const noexcept;
};

/// \struct IndexedAny
///     Allows for use anywhere, but accepts an index value.
template <std::size_t I>
using IndexedAny = Any;

} // namespace morpheus::meta::detail
