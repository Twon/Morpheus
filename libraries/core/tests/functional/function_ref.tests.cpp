#include "morpheus/core/functional/function_ref.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::functional
{

TEST_CASE("Propagate constness and noexceptness to function_ref", "[morpheus.functional.function_ref]")
{
}

void testFunction() { SUCCEED(); };

TEST_CASE("Verify construction of function_ref", "[morpheus.functional.function_ref]")
{
    GIVEN("A free standing function")
    {
        WHEN("Constructing a function reference to the function")
        {
            func_ref_ns::function_ref<void()> functionView = testFunction;
            THEN("Expect the function to be invocable by the function ref")
            {
                functionView();
            }
        }
    }
//    auto const lambda = [](){};
//    func_ref_ns::function_ref<void()> lambdaView = lambda;
}

} // morpheus::functional