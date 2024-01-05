#include "morpheus/core/conversion/adapters/std/source_location.hpp"
#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"

#include <catch2/catch_all.hpp>

#include <chrono>

namespace morpheus::conversion
{

TEST_CASE("Verify std::format specialisation for std::source_location", "[morpheus.conversion.source_location.formatter]")
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

} // namespace morpheus::conversion
