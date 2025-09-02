#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/source_location.hpp"

#include <string_view>

template <>
struct morpheus::conf::fmt::formatter<morpheus::conf::sl::source_location>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    constexpr auto format(morpheus::conf::sl::source_location const& location, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::conf::fmt::format_to(ctx.out(), "{}({}:{}):{}"sv, location.file_name(), location.line(), location.column(), location.function_name());
    }
};
