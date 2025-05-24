#include "morpheus/core/conversion/adapters/std/chrono.hpp"
#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"

#include <catch2/catch_all.hpp>

#include <chrono>

namespace morpheus::conversion
{

TEST_CASE("Verify std::format specialisation for std::chrono::duration", "[morpheus.conversion.chrono.duration.formatter]")
{
    REQUIRE(fmt_ns::format("{}", std::chrono::nanoseconds{45}) == "45ns");
    auto const microseconds = fmt_ns::format("{}", std::chrono::microseconds{378});
    REQUIRE(microseconds.find("378") != std::string::npos);
    REQUIRE((microseconds.ends_with("us") || microseconds.ends_with("µs"))); // Check for both "us" and "µs" to accommodate different compiler versions
    REQUIRE(fmt_ns::format("{}", std::chrono::milliseconds{2}) == "2ms");
    REQUIRE(fmt_ns::format("{}", std::chrono::seconds{58}) == "58s");
    REQUIRE(fmt_ns::format("{}", std::chrono::minutes{42}) == "42min");
    REQUIRE(fmt_ns::format("{}", std::chrono::hours{5}) == "5h");
    REQUIRE(fmt_ns::format("{}", std::chrono::days{90}) == "90d");
}

TEST_CASE("Verify toString handling for std::chrono::duration types", "[morpheus.conversion.chrono.duration.toString]")
{
    REQUIRE(toString(std::chrono::nanoseconds{123}) == "123ns");
    REQUIRE(toString(std::chrono::microseconds{789}) == "789us");
    REQUIRE(toString(std::chrono::milliseconds{456}) == "456ms");
    REQUIRE(toString(std::chrono::seconds{60}) == "60s");
    REQUIRE(toString(std::chrono::minutes{15}) == "15min");
    REQUIRE(toString(std::chrono::hours{24}) == "24h");
    REQUIRE(toString(std::chrono::weeks{12}) == "12w");
    REQUIRE(toString(std::chrono::years{100}) == "100y");
    REQUIRE(toString(std::chrono::months{12}) == "12m");
}

TEST_CASE("Verify fromString handling for std::chrono::duration types", "[morpheus.conversion.chrono.duration.fromString]")
{
    REQUIRE(fromString<std::chrono::nanoseconds>("123ns") == std::chrono::nanoseconds{123});
    REQUIRE(fromString<std::chrono::microseconds>("789us") == std::chrono::microseconds{789});
    REQUIRE(fromString<std::chrono::milliseconds>("456ms") == std::chrono::milliseconds{456});
    REQUIRE(fromString<std::chrono::seconds>("60s") == std::chrono::seconds{60});
    REQUIRE(fromString<std::chrono::minutes>("15min") == std::chrono::minutes{15});
    REQUIRE(fromString<std::chrono::hours>("24h") == std::chrono::hours{24});
    REQUIRE(fromString<std::chrono::weeks>("12w") == std::chrono::weeks{12});
    REQUIRE(fromString<std::chrono::years>("100y") == std::chrono::years{100});
    REQUIRE(fromString<std::chrono::months>("12m") == std::chrono::months{12});
}

TEST_CASE("Verify std::format specialisation for std::chrono::date", "[morpheus.conversion.chrono.date.formatter]")
{
    using namespace date_ns;
    REQUIRE(fmt_ns::format("{}", day{8}) == "08");
    REQUIRE(fmt_ns::format("{}", month{10}) == "Oct");
    REQUIRE(fmt_ns::format("{}", year{1980}) == "1980");
    REQUIRE(fmt_ns::format("{}", weekday{3}) == "Wed");
    REQUIRE(fmt_ns::format("{}", weekday_indexed{Wednesday[2]}) == "Wed[2]");
    REQUIRE(fmt_ns::format("{}", weekday_last{Monday[last]}) == "Mon[last]");
    REQUIRE(fmt_ns::format("{}", month_day{month{10}, day{8}}) == "Oct/08");
    REQUIRE(fmt_ns::format("{}", month_day_last{month{10}}) == "Oct/last");
    REQUIRE(fmt_ns::format("{}", year_month{year{1980}, month{10}}) == "1980/Oct");
    REQUIRE(fmt_ns::format("{}", year_month_day{year{1980}, month{10}, day{8}}) == "1980-10-08");
    REQUIRE(fmt_ns::format("{}", year_month_day_last{year{1980}, month_day_last{month{10}}}) == "1980/Oct/last");
    REQUIRE(fmt_ns::format("{}", year_month_weekday{year{1980}, month{10}, weekday_indexed{Wednesday[2]}}) == "1980/Oct/Wed[2]");
    REQUIRE(fmt_ns::format("{}", year_month_weekday_last{year{1980}, month{10}, weekday_last{Monday[last]}}) == "1980/Oct/Mon[last]");
}

TEST_CASE("Verify toString handling for std::chrono::duration types", "[morpheus.conversion.chrono.time_zone.toString]")
{
    REQUIRE(toString(*date_ns::get_tzdb().locate_zone("Africa/Johannesburg")) == "Africa/Johannesburg");
    REQUIRE(toString(*date_ns::get_tzdb().locate_zone("America/New_York")) == "America/New_York");
    REQUIRE(toString(*date_ns::get_tzdb().locate_zone("Asia/Hong_Kong")) == "Asia/Hong_Kong");
    REQUIRE(toString(*date_ns::get_tzdb().locate_zone("Europe/London")) == "Europe/London");
}

TEST_CASE("Verify fromString handling for std::chrono::duration types", "[morpheus.conversion.chrono.time_zone.fromString]")
{
    REQUIRE(fromString<date_ns::time_zone>("Africa/Johannesburg") == *date_ns::get_tzdb().locate_zone("Africa/Johannesburg"));
    REQUIRE(fromString<date_ns::time_zone>("America/New_York") == *date_ns::get_tzdb().locate_zone("America/New_York"));
    REQUIRE(fromString<date_ns::time_zone>("Asia/Hong_Kong") == *date_ns::get_tzdb().locate_zone("Asia/Hong_Kong"));
    REQUIRE(fromString<date_ns::time_zone>("Europe/London") == *date_ns::get_tzdb().locate_zone("Europe/London"));
    REQUIRE(!fromString<date_ns::time_zone>("Invalid").has_value());
}

} // namespace morpheus::conversion
