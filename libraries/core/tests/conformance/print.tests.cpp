#include "morpheus/core/conformance/print.hpp"
#include "morpheus/temp_file.hpp"

#include <catch2/catch_all.hpp>
#include <iostream>

namespace morpheus
{

TEST_CASE("Ensure print is supported and working", "[morpheus.conformance.print]")
{
    GIVEN("A capture to file")
    {
        TempFile temp;
        
        WHEN("Using std::print to write output")
        {
            // Ensure time zones work
            print_ns::print(temp.getFile(), "{2} {1} {0}", true, 3.14, 100);
            
            THEN("Expect the variables wrote to the stream in the specified order")
            {
                REQUIRE(temp.contents() == "100 3.14 true");
            }
        }
    }
}

} // morpheus