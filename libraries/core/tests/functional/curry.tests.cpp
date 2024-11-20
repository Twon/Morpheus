#include "morpheus/core/functional/curry.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::functional
{

#if (__cpp_explicit_this_parameter >= 202110L)

TEST_CASE("Verify partial application via currying", "[morpheus.functional.curry]")
{
    SECTION("Zero parameters")
    {
        auto constexpr shouldCall = []()
        {
            SUCCEED();
        };
        curry(shouldCall);
    }
    SECTION("One parameters")
    {
        auto constexpr expectedParam1 = 1;
        auto constexpr identity = [](auto a) { return a; };
        curry(identity, expectedParam1);
        REQUIRE(expectedParam1 == identity(expectedParam1));
    }
    SECTION("Two parameters")
    {
        auto constexpr expectedParam1 = 1;
        auto constexpr expectedParam2 = 2;
        auto constexpr add = [](auto a, auto b)
        {
            REQUIRE(a == expectedParam1);
            REQUIRE(b == expectedParam2);
            return a + b;
        };
        auto constexpr add1 = curry(add, expectedParam1);
        REQUIRE(add1(expectedParam2) == (expectedParam1 + expectedParam2));
    }
    SECTION("Three parameters")
    {
        auto constexpr expectedParam1 = 1;
        auto constexpr expectedParam2 = 2;
        auto constexpr expectedParam3 = 3;
        auto constexpr add = [](auto a, auto b, auto c)
        {
            REQUIRE(a == expectedParam1);
            REQUIRE(b == expectedParam2);
            REQUIRE(c == expectedParam3);
            return a + b + c;
        };
        auto constexpr add1 = curry(add, expectedParam1);
        REQUIRE(add1(expectedParam2, expectedParam3) == (expectedParam1 + expectedParam2 + expectedParam3));
    }
}

#endif // (__cpp_explicit_this_parameter >= 202110L)

} // namespace morpheus::functional
