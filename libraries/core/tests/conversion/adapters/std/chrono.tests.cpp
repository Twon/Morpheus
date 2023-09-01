#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/std/expected.hpp"

#include <catch2/catch_all.hpp>

#include <chrono>

namespace morpheus::serialisation
{

TEST_CASE("Verify std::format specialisation for std::chrono::duration", "[morpheus.conversion.chrono.duration.formatter]")
{
    REQUIRE(fmt_ns::format("{}", std::chrono::nanoseconds{45}) == "45ns");
    REQUIRE(fmt_ns::format("{}", std::chrono::microseconds{378}) == "378us");
    REQUIRE(fmt_ns::format("{}", std::chrono::milliseconds{2}) == "2ms");
    REQUIRE(fmt_ns::format("{}", std::chrono::seconds{58}) == "58s");
    REQUIRE(fmt_ns::format("{}", std::chrono::minutes{42}) == "42m");
    REQUIRE(fmt_ns::format("{}", std::chrono::hours{5}) == "5h");
    REQUIRE(fmt_ns::format("{}", std::chrono::days{90}) == "90d");
}

} // namespace morpheus::serialisation