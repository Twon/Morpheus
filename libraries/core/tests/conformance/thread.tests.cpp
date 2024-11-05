#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conversion/adapters/std/thread.hpp"
#include "morpheus/temp_file.hpp"

#include <catch2/catch_test_macros.hpp>
#include <thread>
#include <sstream>

namespace morpheus
{

TEST_CASE("Ensure std::thread::id format specialisation is supported and working", "[morpheus.conformance.thread]")
{
    GIVEN("a capture of the current stack trace")
    {
        auto const id = std::this_thread::get_id();

        WHEN("Using std::format to write to a string")
        {
            // Ensure time zones work
            auto const output = fmt_ns::format("{}", id);

            THEN("Expect the variables wrote to the stream in the specified order")
            {
                std::stringstream str;
                str << id;
                REQUIRE(output == str.str());
            }
        }
    }
}

}
