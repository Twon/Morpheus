#pragma once

#include "morpheus/core/conformance/expected.hpp"

#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::conversion
{

/// \struct StringConverter
///     A class template the represents a customisation point to specialise to provide conversion between a type and
///     its string representation.
/// \tparam T The type to convert to and from a string.
template<typename T>
struct StringConverter
{
    /// A deleted constructor indicates a disabled string converter
    StringConverter() = delete;
};

template<typename T>
concept StringConvertionEnabled = std::is_constructible_v<StringConverter<T>>;

/// Convert a value of type T to its string representation.
/// \tparam T The type to convert.
/// \param value The value to convert.
/// \return A string representation of the value.
template <StringConvertionEnabled T>
std::string toString(T const& value)
{
    return StringConverter<T>::toString(value);
}

/// Convert a string representation to a value of type T.
/// \tparam T The type to convert to.
/// \param value The string representation to convert.
/// \return An expected containing the value if the conversion was successful, or an unexpected error if it failed.
template <StringConvertionEnabled T>
auto fromString(std::string_view const value)
{
    return StringConverter<T>::fromString(value);
}

} // namespace morpheus::conversion
