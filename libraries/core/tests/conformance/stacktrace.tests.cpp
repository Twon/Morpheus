#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"
#include "morpheus/core/conversion/adapters/std/stacktrace.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>

namespace morpheus
{

TEST_CASE("Ensure stacktrace is supported and working", "[morpheus.conformance.stacktrace]")
{
    GIVEN("a capture of the current stack trace")
    {
        auto const st = MORPHEUS_CURRENT_STACKTRACE;

        WHEN("Using std::format to write to a string")
        {
            // Ensure time zones work
            auto const output = conf::fmt::format("{}", st);

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(output == to_string(st));
            }
        }
    }
}

} // namespace morpheus
