#pragma once

// IWYU pragma: always_keep
#include <boost/lexical_cast.hpp>

#include <filesystem>
#include <string>

namespace boost
{

template <>
inline std::filesystem::path lexical_cast<std::filesystem::path, std::basic_string<char>>(std::basic_string<char> const& arg)
{
    return std::filesystem::path(arg);
}

} // namespace boost
