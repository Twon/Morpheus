#pragma once

#include "morpheus/core/meta/is_string.hpp"
#include <string>
#include <type_traits>

namespace morpheus::meta
{

template <class T>
concept IsString = is_string_v<std::remove_cvref_t<T>>;

template <class T>
concept IsStringView = is_string_view_v<std::remove_cvref_t<T>>;

template <class T>
concept ConvertableToStringView =
    std::is_convertible_v<std::remove_cvref_t<T>, std::string_view> || std::is_convertible_v<std::remove_cvref_t<T>, std::wstring_view> ||
    std::is_convertible_v<std::remove_cvref_t<T>, std::u8string_view> || std::is_convertible_v<std::remove_cvref_t<T>, std::u16string_view> ||
    std::is_convertible_v<std::remove_cvref_t<T>, std::u32string_view>;

} // namespace morpheus::meta