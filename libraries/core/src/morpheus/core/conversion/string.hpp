#pragma once

#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::conversion
{

template<typename T>
struct StringConverter 
{
    /// A deleted constructor indicates a disabled string converter
    StringConverter() = delete;
};

template<typename T>
concept StringConvertionEnabled = std::is_constructible_v<StringConverter<T>>;

template <StringConvertionEnabled T>
std::string toString(T const& value)
{
    return StringConverter<T>::toString(value);
}

template <StringConvertionEnabled T>
T fromString(std::string_view const value)
{
    return StringConverter<T>::fromString(value);
}


}