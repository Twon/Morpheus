#pragma once

#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"

#include <array>
#include <string_view>

#if (__cpp_lib_formatters < 202302L)

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::day>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    auto format(morpheus::date_ns::day const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{:02d}"sv, static_cast<unsigned>(day));
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    auto format(morpheus::date_ns::month const& month, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        std::array<std::string_view, 12> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, months[static_cast<unsigned>(month)]);
    }
};

#endif