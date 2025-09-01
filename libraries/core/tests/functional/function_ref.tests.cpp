#include "morpheus/core/functional/function_ref.hpp"

#include <catch2/catch_test_macros.hpp>

#include <type_traits>

namespace morpheus::functional
{

TEST_CASE("Propagate constness and noexceptness to function_ref", "[morpheus.functional.function_ref]")
{
    using ConcreteFunctionRef = conf::func_ref::function_ref<void()>;
    STATIC_REQUIRE(std::is_nothrow_copy_constructible_v<ConcreteFunctionRef>);
    STATIC_REQUIRE(std::is_nothrow_copy_assignable_v<ConcreteFunctionRef>);
    STATIC_REQUIRE(std::is_nothrow_move_constructible_v<ConcreteFunctionRef>);
    STATIC_REQUIRE(std::is_nothrow_move_assignable_v<ConcreteFunctionRef>);
}

void testFunction()
{
    SUCCEED();
}

TEST_CASE("Verify construction of function_ref", "[morpheus.functional.function_ref]")
{
    GIVEN("A free standing function")
    {
        WHEN("Constructing a function reference to the function")
        {
            conf::func_ref::function_ref<void()> functionView = testFunction;
            THEN("Expect the function to be invocable by the function ref")
            {
                functionView();
            }
        }
    }
    GIVEN("A class member function and class instance")
    {
        struct TestForInvocable
        {
            bool mRequiredData = true;

            void function(int, int) { SUCCEED(); }
        };
        WHEN("Constructing a function reference to the function")
        {
            TestForInvocable instance;
            conf::func_ref::function_ref<void(int, int)> functionView = {conf::func_ref::nontype<&TestForInvocable::function>, instance};
            THEN("Expect the function to be invocable by the function ref")
            {
                functionView(0, 1);
            }
        }
    }
    /*    GIVEN("A class member function and class instance")
        {
            auto const lambda = [](int, int){ SUCCEED(); }

            WHEN("Constructing a function reference to the function")
            {
                TestForInvocable instance;
                conf::func_ref::function_ref<void(int, int)> functionView = { conf::func_ref::nontype<&TestForInvocable::function>, instance };
                THEN("Expect the function to be invocable by the function ref")
                {
                    functionView(0, 1);
                }
            }
        }
    */
    //    auto const lambda = [](){};
    //    conf::func_ref::function_ref<void()> lambdaView = lambda;
}

} // namespace morpheus::functional
