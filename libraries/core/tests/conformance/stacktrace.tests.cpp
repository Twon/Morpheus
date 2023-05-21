#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"
#include "morpheus/temp_file.hpp"

#include <catch2/catch_all.hpp>
#include <iostream>

namespace morpheus
{

TEST_CASE("Ensure stacktrace is supported and working", "[morpheus.conformance.stacktrace]")
{
    GIVEN("a capture of the current stack trace")
    {
        auto st = st_ns::stacktrace(); 
        
        WHEN("Using std::format to write to a string")
        {
            // Ensure time zones work
            auto const output = fmt_ns::format("{}", st);
            
            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(output == to_string(st));
            }
        }
    }
}

}