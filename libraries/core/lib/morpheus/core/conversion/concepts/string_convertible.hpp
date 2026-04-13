#pragma once

#include "morpheus/core/conversion/string.hpp"

#include <concepts>
#include <string>

namespace morpheus::conversion::concepts
{

template <typename T>
concept StringConvertible = requires(T const& t, std::string_view const& s) {
    { StringConverter<T>::toString(t) } -> std::convertible_to<std::string>;
    { StringConverter<T>::fromString(s) } -> std::convertible_to<T>;
};

} // namespace morpheus::conversion::concepts
