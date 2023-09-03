#pragma once

#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"

#include <array>
#include <string_view>

#if (__cpp_lib_formatters < 202302L)

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::day>
{
    char presentation = 'd';
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

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

    auto format(morpheus::date_ns::month const& month, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, months[static_cast<unsigned>(month) - 1]);
    }

    static constexpr std::array<std::string_view, 12> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::year const& year, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, static_cast<int>(year));
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::weekday>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::weekday const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, weekdays[day.c_encoding()]);
    }

    static constexpr std::array<std::string_view, 7> weekdays = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::weekday_indexed> : morpheus::fmt_ns::formatter<morpheus::date_ns::weekday>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::weekday_indexed const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}[{}]"sv, weekdays[day.weekday().c_encoding()], day.index());
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::weekday_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::weekday>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::weekday_last const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}[last]"sv, weekdays[day.weekday().c_encoding()]);
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::month_day> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::month_day const& month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}"sv, months[static_cast<unsigned>(month_day.month()) - 1], month_day.day());
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::month_day_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::month_day_last const& month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/last"sv, months[static_cast<unsigned>(month_day.month()) - 1]);
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::year_month const& year_month, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}"sv, static_cast<int>(year_month.year()), months[static_cast<unsigned>(year_month.month()) - 1]);
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_day> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::year_month_day const& year_month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}-{}-{}"sv, year_month_day.year(), months[static_cast<unsigned>(year_month_day.month()) - 1],
                                           year_month_day.day());
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_day_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::year_month_day_last const& year_month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}/last"sv, year_month_day.year(), months[static_cast<unsigned>(year_month_day.month()) - 1]);
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_weekday> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::year_month_weekday const& year_month_weekday, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}/{}"sv, year_month_weekday.year(), months[static_cast<unsigned>(year_month_weekday.month()) - 1],
                                           year_month_weekday.weekday_indexed());
    }
};

template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_weekday_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::year_month_weekday_last const& year_month_weekday, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}/last"sv, year_month_weekday.year(), months[static_cast<unsigned>(year_month_weekday.month()) - 1]);
    }
};


#endif