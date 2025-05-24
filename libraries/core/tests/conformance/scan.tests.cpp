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
            auto result = scan_ns::scan<int, int>(input, "{} {}");
            auto [a, b] = result->values();

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(a == 123);
                REQUIRE(b == 456);
            }
        }
    }
}

} // morpheus
