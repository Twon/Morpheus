#pragma once

#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/source_location.hpp"

#include <string_view>

template <>
struct morpheus::fmt_ns::formatter<morpheus::sl_ns::source_location>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::sl_ns::source_location const& location, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}({}:{}):{}"sv, location.file_name(), location.line(), location.column(), location.function_name());
    }
};
