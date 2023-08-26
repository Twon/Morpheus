#include "morpheus/core/functional/curry.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::functional
{

TEST_CASE("Verify construction of function_ref", "[morpheus.functional.function_ref]")
{
    GIVEN("A free standing function")
    {
        WHEN("Constructing a function reference to the function")
        {
            THEN("Expect the function to be invocable by the function ref") {}
        }
    }
    GIVEN("A class member function and class instance")
    {
        WHEN("Constructing a function reference to the function")
        {
            THEN("Expect the function to be invocable by the function ref") {}
        }
    }
}

} // namespace morpheus::functional