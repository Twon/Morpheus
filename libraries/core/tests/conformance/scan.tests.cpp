#include "morpheus/core/conformance/scan.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string_view>

namespace morpheus::conformance
{

TEST_CASE("Verify scan conformance", "[morpheus.core.conformance.scan]")
{
    GIVEN("A string containing two integers")
    {
        std::string_view const input = "123 456";

        WHEN("Using std::scan to read from input")
        {
            auto const result = conf::scan::scan<int, int>(input, "{} {}");

            THEN("Expect the variables read from the stream in the specified order")
            {
                REQUIRE(result);
                auto [a, b] = result->values();
                REQUIRE(a == 123);
                REQUIRE(b == 456);
            }
        }
    }

    GIVEN("A string containing a hex integer")
    {
        using namespace std::string_view_literals;

        WHEN("Using std::scan to read a hex integer")
        {
            auto const input = "0x42"sv;
            auto result = conf::scan::scan<int>(input, "{:x}");
            REQUIRE(result);
            REQUIRE(result->value() == 0x42);
        }

        GIVEN("A hex string without prefix")
        {
            auto const input = "42"sv;
            auto result = conf::scan::scan<int>(input, "{:x}");
            REQUIRE(result);
            REQUIRE(result->value() == 0x42);
        }

        GIVEN("A hex string with 0X prefix")
        {
            auto const input = "0XFF"sv;
            auto result = conf::scan::scan<int>(input, "{:x}");
            REQUIRE(result);
            REQUIRE(result->value() == 0xFF);
        }
    }
}

} // namespace morpheus::conformance
