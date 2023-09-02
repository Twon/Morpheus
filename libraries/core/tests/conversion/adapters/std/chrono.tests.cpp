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
#if (__cpp_lib_format >= 201907L)
    REQUIRE(fmt_ns::format("{}", std::chrono::microseconds{378}) == "378us");
#else
    REQUIRE(fmt_ns::format("{}", std::chrono::microseconds{378}) == "378\u00b5s");
#endif // (__cpp_lib_format >= 201907L)
    REQUIRE(fmt_ns::format("{}", std::chrono::milliseconds{2}) == "2ms");
    REQUIRE(fmt_ns::format("{}", std::chrono::seconds{58}) == "58s");
#if (__cpp_lib_format >= 201907L)
    REQUIRE(fmt_ns::format("{}", std::chrono::minutes{42}) == "42min");
#else
    REQUIRE(fmt_ns::format("{}", std::chrono::minutes{42}) == "42m");
#endif // (__cpp_lib_format >= 201907L)
    REQUIRE(fmt_ns::format("{}", std::chrono::hours{5}) == "5h");
#if (__cpp_lib_format >= 201907L)
    REQUIRE(fmt_ns::format("{}", std::chrono::days{90}) == "90d");
#else
    REQUIRE(fmt_ns::format("{}", std::chrono::days{90}) == "90[86400]s");
#endif // (__cpp_lib_format >= 201907L)
}

TEST_CASE("Verify std::format specialisation for std::chrono::date", "[morpheus.conversion.chrono.date.formatter]")
{
    using namespace date_ns;
    REQUIRE(fmt_ns::format("{}", day{8}) == "08");
    REQUIRE(fmt_ns::format("{}", month{10}) == "Oct");
    REQUIRE(fmt_ns::format("{}", year{1980}) == "1980");
    REQUIRE(fmt_ns::format("{}", weekday{3}) == "Wed");
    /*REQUIRE(fmt_ns::format("{}", weekday_indexed{Wednesday[2]}) == "Wed[2]");
    REQUIRE(fmt_ns::format("{}", weekday_last{Monday[last]}) == "Mon[last]");
    REQUIRE(fmt_ns::format("{}", month_day{month{10}, day{8}}) == "Oct/08");
    REQUIRE(fmt_ns::format("{}", month_day_last{month{10}}) == "Oct/last");
    REQUIRE(fmt_ns::format("{}", year_month{year{1980}, month{10}}) == "1980/Oct");
    REQUIRE(fmt_ns::format("{}", year_month_day{year{1980}, month{10}, day{8}}) == "1980-10-08");
    REQUIRE(fmt_ns::format("{}", year_month_day_last{year{1980}, month_day_last{month{10}}}) == "1980/Oct/last");
    REQUIRE(fmt_ns::format("{}", year_month_weekday{year{1980}, month{10}, weekday_indexed{Wednesday[2]}}) == "1980/Oct/Wed[2]");
    REQUIRE(fmt_ns::format("{}", year_month_weekday_last{year{1980}, month{10}, weekday_last{Monday[last]}}) == "1980/Oct/last");
    */
}

} // namespace morpheus::conversion