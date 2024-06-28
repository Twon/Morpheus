#pragma once

#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace boost
{

/// The default behaviour for parsing of std::filesystem::path is fine except for the handling of spaces.  However specialising
/// boost::lexical_cast for std::filesystem::path so strings are directly convertible to paths is enough to ensure correct
/// handling of paths
/// @note
///     https://github.com/boostorg/program_options/issues/69
template <>
inline std::filesystem::path lexical_cast<std::filesystem::path, std::basic_string<char>>(const std::basic_string<char>& arg)
{
    return std::filesystem::path(arg);
}

} // namespace boost
