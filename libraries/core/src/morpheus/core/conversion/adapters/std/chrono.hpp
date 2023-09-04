#pragma once

#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conversion/string.hpp"

#include <ctll.hpp>
#include <ctre.hpp>

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


namespace morpheus::conversion
{

template <typename Rep, typename Period>
struct StringConverter<std::chrono::duration<Rep, Period>>
{
    static constexpr std::string toString(std::chrono::duration<Rep, Period> const value)
    {
        if constexpr (std::is_same_v<Period, std::micro>)
        {
            return fmt_ns::format("{}us", value.count());
        }
        else if constexpr (std::is_same_v<Period, std::chrono::minutes::period>)
        {
            return fmt_ns::format("{}min", value.count());
        }
        else if constexpr (std::is_same_v<Period, std::chrono::days::period>)
        {
            return fmt_ns::format("{}d", value.count());
        }
        else if constexpr (std::is_same_v<Period, std::chrono::weeks::period>)
        {
            return fmt_ns::format("{}w", value.count());
        }
        else if constexpr (std::is_same_v<Period, std::chrono::years::period>)
        {
            return fmt_ns::format("{}y", value.count());
        }
        else if constexpr (std::is_same_v<Period, std::chrono::months::period>)
        {
            return fmt_ns::format("{}m", value.count());
        }
        else {
            return fmt_ns::format("{}", value);
        }
    }

    static constexpr exp_ns::expected<std::chrono::duration<Rep, Period>, std::string_view> fromString(std::string_view const value)
    {
        /*
        constexpr auto regex = []<typename T>
        {
            if constexpr (std::is_same_v<Period, std::micro>)
            {
                return ctll::fixed_string(R"((\\d*)ms)");
            }
            return ctll::fixed_string(R"((\\d*))");
        }.template operator()<std::chrono::duration<Rep, Period>>();
        */
        constexpr auto matchString = []<ctll::fixed_string T>(auto const value) -> exp_ns::expected<std::chrono::duration<Rep, Period>, std::string_view>
        {
            if (auto m = ctre::match<T>(value)) {
                return std::chrono::duration<Rep, Period>(std::stoi(std::string(m.get<1>().to_view())));
            }
            else {
                return exp_ns::unexpected("Unable to parse std::chrono::duration");
            }
        };

        if constexpr (std::is_same_v<Period, std::nano>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)ns")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::micro>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)us")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::milli>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)ms")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::seconds::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)s")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::minutes::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)min")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::hours::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)h")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::days::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)d")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::weeks::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)w")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::months::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)m")>(value);
        }
        else if constexpr (std::is_same_v<Period, std::chrono::years::period>)
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)y")>(value);
        }
        return matchString.template operator()<ctll::fixed_string("(\\d+)")>(value);
    }
};

}