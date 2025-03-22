#include "morpheus/core/functional/function_ref.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::functional
{

using namespace func_ref_ns;

TEST_CASE("Propagate constness and noexceptness to function_ref", "[morpheus.functional.function_ref]")
{
    using ConcreteFunctionRef = function_ref<void()>;
    STATIC_REQUIRE(std::is_nothrow_copy_constructible_v<ConcreteFunctionRef>);
    STATIC_REQUIRE(std::is_nothrow_copy_assignable_v<ConcreteFunctionRef>);
    STATIC_REQUIRE(std::is_nothrow_move_constructible_v<ConcreteFunctionRef>);
    STATIC_REQUIRE(std::is_nothrow_move_assignable_v<ConcreteFunctionRef>);
}

TEST_CASE("Propagate constness and noexceptness to function_ref", "[morpheus.functional.function_ref.callable_qualifications]")
{
    struct TestNonConstNothrowable
    {
        void operator()() noexcept {}
    };
    STATIC_REQUIRE(meta::IsNothrowInvocable<TestNonConstNothrowable>);
    STATIC_REQUIRE(!meta::IsConstInvocable<TestNonConstNothrowable>);

    struct TestNonConstThrowable
    {
        void operator()() {}
    };
    STATIC_REQUIRE(!meta::IsNothrowInvocable<TestNonConstThrowable>);
    STATIC_REQUIRE(!meta::IsConstInvocable<TestNonConstThrowable>);

    function_ref<void() const> constFunction = [](){};
    STATIC_REQUIRE(!meta::IsNothrowInvocable<decltype(constFunction)>);
    STATIC_REQUIRE(meta::IsConstInvocable<decltype(constFunction)>);

    function_ref<void() const noexcept> noexceptConstFunction = []() noexcept {};
    STATIC_REQUIRE(meta::IsNothrowInvocable<decltype(noexceptConstFunction)>);
    STATIC_REQUIRE(meta::IsConstInvocable<decltype(noexceptConstFunction)>);
}

void testFunction() { SUCCEED(); }

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
    GIVEN("A class member function and class instance")
    {
        struct TestForInvocable
        {
            bool mRequiredData = true;

            void function(int, int)
            {
                SUCCEED();
            }
        };
        WHEN("Constructing a function reference to the function")
        {
            TestForInvocable instance;
            func_ref_ns::function_ref<void(int, int)> functionView = { func_ref_ns::nontype<&TestForInvocable::function>, instance };
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
            func_ref_ns::function_ref<void(int, int)> functionView = { func_ref_ns::nontype<&TestForInvocable::function>, instance };
            THEN("Expect the function to be invocable by the function ref")
            {
                functionView(0, 1);
            }
        }
    }
*/
//    auto const lambda = [](){};
//    func_ref_ns::function_ref<void()> lambdaView = lambda;
}

TEST_CASE("Verify use of function_ref as an argument", "[morpheus.functional.function_ref.argument]")
{
    auto const constexpr callable = [](function_ref<void(int, int)>){ SUCCEED(); };


    //auto const lambda = [](int, int){ SUCCEED(); };
    function_ref<void(int, int)> functionView([](int, int){ SUCCEED(); });
    function_ref<void(int, int)> functionView2 = functionView;
    functionView2(0, 1);
}

TEST_CASE("Verify use of function_ref as an argument", "[morpheus.functional.function_ref.deduction_guides]")
{
    // [func.wrap.ref.deduct]
    // template <class F> requires std::is_function_v<F>
    // function_ref(F*) -> function_ref<F>;
    function_ref simpleCallable = testFunction;
    simpleCallable();

    // template <auto f, class F = std::remove_pointer_t<decltype(f)>>
    // requires std::is_function_v<F>
    // function_ref(nontype_t<f>) -> function_ref<F>;
    function_ref simpleCallable2 = nontype<&testFunction>;
    simpleCallable2();
}

} // morpheus::functional
