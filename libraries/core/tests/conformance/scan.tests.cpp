#include "morpheus/core/conformance/scan.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string_view>

namespace morpheus
{

TEST_CASE("Ensure scan is supported and working", "[morpheus.conformance.scan]")
{
    GIVEN("A capture to file")
    {
        using namespace std::string_view_literals;
        auto const input = "123 456"sv;

        WHEN("Using std::scan to read from input")
        {
            auto result = conf::scan::scan<int, int>(input, "{} {}");
            auto [a, b] = result->values();

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(a == 123);
                REQUIRE(b == 456);
            }
        }
    }

    SECTION("Hexadecimal patterns using regex")
    {
        GIVEN("A hex string with 0x prefix")
        {
            auto const input = "0x42";
            auto result = conf::scan::scan<int>(input, "{:/(?:0[xX])?([0-9a-fA-F]+)/}");
            REQUIRE(result);
            REQUIRE(result->value() == 0x42);
        }

        GIVEN("A hex string without prefix")
        {
            auto const input = "42";
            auto result = conf::scan::scan<int>(input, "{:/(?:0[xX])?([0-9a-fA-F]+)/}");
            REQUIRE(result);
            REQUIRE(result->value() == 0x42);
        }

        GIVEN("A hex string with 0X prefix")
        {
            auto const input = "0XFF";
            auto result = conf::scan::scan<int>(input, "{:/(?:0[xX])?([0-9a-fA-F]+)/}");
            REQUIRE(result);
            REQUIRE(result->value() == 0xFF);
        }
    }
}

} // namespace morpheus
