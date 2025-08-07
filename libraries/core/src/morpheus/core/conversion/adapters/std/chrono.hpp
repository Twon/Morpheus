#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/base/compiler.hpp"
#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conversion/string.hpp"

#include <ctll.hpp>
#include <ctre.hpp>

#include <array>
#include <string_view>

/// \def MORPHEUS_CPP_LIB_CHRONO_FORMATTING
///   Ensures that std::format support for std::chrono is implemented as specified in
///  https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0355r7.html
#define MORPHEUS_CPP_LIB_CHRONO_FORMATTING                                                                                                                     \
    (((MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER) && (__cpp_lib_chrono < 201907L)) ||                                                                \
     ((MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER) && (MORPHEUS_COMP_VER < 140000000)) ||                                                                     \
     ((MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER) && (MORPHEUS_COMP_VER < 200000000)) ||                                                                    \
     ((MORPHEUS_COMPILER == MORPHEUS_APPLE_CLANG_COMPILER) && (MORPHEUS_COMP_VER < 150000000)))

#if MORPHEUS_CPP_LIB_CHRONO_FORMATTING

/// Specialisation of the formatter for std::chrono::day.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::day>
{
    /// The presentation type for day formatting.
    char presentation = 'd';

    /// Parse the format specifier for day.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the day as a string.
    /// \param day The day to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::day const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{:02d}"sv, static_cast<unsigned>(day));
    }
};

/// Specialisation of the formatter for std::chrono::month.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for month.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
    {
        auto pos = std::begin(ctx);
        while (pos != std::end(ctx) && *pos != '}')
        {
            auto c = *pos;
            if (c != '%')
            {
                ++pos;    // LCOV_EXCL_LINE
                continue; // LCOV_EXCL_LINE
            }

            pos++; // Skip %
            if (pos == std::end(ctx))
                throw morpheus::fmt_ns::format_error("Invalid format"); // LCOV_EXCL_LINE

            c = *pos;
            switch (c)
            {
            case 'm':
                monthAsDecimal = true;
                break;
            }

            ++pos;
        }
        return pos;
    }

    /// Format the month as a string.
    /// \param month The month to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    /// \note If monthAsDecimal is true, the month is formatted as a decimal number (1-12), otherwise it is formatted as a three-letter abbreviation.
    auto format(morpheus::date_ns::month const& month, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        if (monthAsDecimal)
        {
            return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, static_cast<unsigned>(month));
        }
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, months[static_cast<unsigned>(month) - 1]);
    }

    bool monthAsDecimal = false;
    static constexpr std::array<std::string_view, 12> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
};

/// Specialisation of the formatter for std::chrono::year.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year>
{
    /// Parse the format specifier for year.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the year as a string.
    auto format(morpheus::date_ns::year const& year, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, static_cast<int>(year));
    }
};

/// Specialisation of the formatter for std::chrono::weekday.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::weekday>
{
    /// Parse the format specifier for weekday.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    auto format(morpheus::date_ns::weekday const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}"sv, weekdays[day.c_encoding()]);
    }

    static constexpr std::array<std::string_view, 7> weekdays = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
};

/// Specialisation of the formatter for std::chrono::weekday_indexed.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::weekday_indexed> : morpheus::fmt_ns::formatter<morpheus::date_ns::weekday>
{
    /// Parse the format specifier for weekday_indexed.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the weekday_indexed as a string.
    /// \param day The weekday_indexed to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::weekday_indexed const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}[{}]"sv, weekdays[day.weekday().c_encoding()], day.index());
    }
};

/// Specialisation of the formatter for std::chrono::weekday_last.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::weekday_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::weekday>
{
    /// Parse the format specifier for weekday_last.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the weekday_last as a string.
    /// \param day The weekday_last to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::weekday_last const& day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}[last]"sv, weekdays[day.weekday().c_encoding()]);
    }
};

/// Specialisation of the formatter for std::chrono::month_day.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::month_day> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for month_day.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the month_day as a string.
    /// \param month_day The month_day to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::month_day const& month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}"sv, months[static_cast<unsigned>(month_day.month()) - 1], month_day.day());
    }
};

/// Specialisation of the formatter for std::chrono::month_day_last.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::month_day_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for month_day_last.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the month_day_last as a string.
    /// \param month_day The month_day_last to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::month_day_last const& month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/last"sv, months[static_cast<unsigned>(month_day.month()) - 1]);
    }
};

/// Specialisation of the formatter for std::chrono::year_month.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for year_month.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the year_month as a string.
    /// \param year_month The year_month to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::year_month const& year_month, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}"sv, static_cast<int>(year_month.year()), months[static_cast<unsigned>(year_month.month()) - 1]);
    }
};

/// Specialisation of the formatter for std::chrono::year_month_day.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_day> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for year_month_day.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the year_month_day as a string.
    /// \param year_month_day The year_month_day to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::year_month_day const& year_month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}-{:%m}-{}"sv, year_month_day.year(), year_month_day.month(), year_month_day.day());
    }
};

/// Specialisation of the formatter for std::chrono::year_month_day_last.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_day_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for year_month_day_last.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the year_month_day_last as a string.
    /// \param year_month_day The year_month_day_last to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::year_month_day_last const& year_month_day, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}/last"sv, year_month_day.year(), months[static_cast<unsigned>(year_month_day.month()) - 1]);
    }
};

/// Specialisation of the formatter for std::chrono::year_month_weekday.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_weekday> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for year_month_weekday.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the year_month_weekday as a string.
    /// \param year_month_weekday The year_month_weekday to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted string.
    auto format(morpheus::date_ns::year_month_weekday const& year_month_weekday, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}/{}"sv, year_month_weekday.year(), months[static_cast<unsigned>(year_month_weekday.month()) - 1],
                                           year_month_weekday.weekday_indexed());
    }
};

/// Specialisation of the formatter for std::chrono::year_month_weekday_last.
template <>
struct morpheus::fmt_ns::formatter<morpheus::date_ns::year_month_weekday_last> : morpheus::fmt_ns::formatter<morpheus::date_ns::month>
{
    /// Parse the format specifier for year_month_weekday_last.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator { return std::begin(ctx); }

    /// Format the year_month_weekday_last as a string.
    /// \param year_month_weekday The year_month_weekday_last to format.
    /// \param ctx The format context.
    /// \return An iterator to the end of the formatted output.
    auto format(morpheus::date_ns::year_month_weekday_last const& year_month_weekday, format_context& ctx) const -> format_context::iterator
    {
        using namespace std::literals;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}/{}/{}"sv, year_month_weekday.year(), year_month_weekday.month(), year_month_weekday.weekday_last());
    }
};

#endif // MORPHEUS_CPP_LIB_CHRONO_FORMATTING

namespace morpheus::conversion
{

/// A specialisation of the class template customisation point to provide conversion between
/// std::chrono::duration and string representations.
template <typename Rep, typename Period>
struct StringConverter<std::chrono::duration<Rep, Period>>
{
    /// Convert a std::chrono::duration to its string representation.
    /// \param value The std::chrono::duration to convert.
    /// \return A string representation of the std::chrono::duration.
    /// \note The string representation is the count of the duration in the specified period, followed by the period's unit (e.g., "5s", "10ms").
    static std::string toString(std::chrono::duration<Rep, Period> const value)
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
        else
        {
            return fmt_ns::format("{}", value);
        }
    }

    /// Convert a string representation to a std::chrono::duration.
    /// \param value The string representation to convert.
    /// \return An expected containing the std::chrono::duration if the conversion was successful, or an unexpected error if it failed.
    /// \note The string representation should be in the format of a count followed by the period's unit (e.g., "5s", "10ms").
    static constexpr exp_ns::expected<std::chrono::duration<Rep, Period>, std::string_view> fromString(std::string_view const value)
    {
        constexpr auto matchString = []<ctll::fixed_string T>(auto const searchStr) -> exp_ns::expected<std::chrono::duration<Rep, Period>, std::string_view>
        {
            if (auto m = ctre::match<T>(searchStr))
            {
                return std::chrono::duration<Rep, Period>(std::stoi(std::string(m.template get<1>().to_view())));
            }
            else
            {
                return exp_ns::unexpected(std::string_view{"Unable to parse std::chrono::duration"});
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
        else
        {
            return matchString.template operator()<ctll::fixed_string("(\\d+)")>(value);
        }
    }
};

/// A specialisation of the class template customisation point to provide conversion between time zone and
/// string representations.
template <>
struct StringConverter<date_ns::time_zone>
{
    /// Convert a date_ns::time_zone to its string representation.
    /// \param value The date_ns::time_zone to convert.
    /// \return A string representation of the date_ns::time_zone, which is the name of the time zone.
    static std::string toString(date_ns::time_zone const& value) { return std::string(value.name()); }

    /// Convert a string representation to a date_ns::time_zone.
    /// \param value The string representation to convert.
    /// \return An expected containing the date_ns::time_zone if the conversion was successful, or an unexpected error if it failed.
    /// \note The string representation should be the name of the time zone as defined in the IANA Time Zone Database.
    static exp_ns::expected<std::reference_wrapper<date_ns::time_zone const>, std::string> fromString(std::string_view const value)
    {
        try
        {
            auto const timezone = date_ns::get_tzdb().locate_zone(value);
            return std::cref(*timezone);
        }
        catch (std::runtime_error const& e)
        {
            return exp_ns::unexpected(fmt_ns::format("Unable to locate timezone, encountered error: {}", e.what()));
        }
    }
};

} // namespace morpheus::conversion
