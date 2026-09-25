#include "morpheus/core/functional/curry.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::functional
{

#if (__cpp_explicit_this_parameter >= 202110L)

TEST_CASE("Verify partial application via currying", "[morpheus.functional.curry]")
{
    SECTION("Zero parameters")
    {
        constexpr auto shouldCall = []() { SUCCEED(); };
        curry(shouldCall);
    }
    SECTION("One parameters")
    {
        constexpr auto expectedParam1 = 1;
        constexpr auto identity = [](auto a) { return a; };
        curry(identity, expectedParam1);
        REQUIRE(expectedParam1 == identity(expectedParam1));
    }
    SECTION("Two parameters")
    {
        constexpr auto expectedParam1 = 1;
        constexpr auto expectedParam2 = 2;
        constexpr auto add = [](auto a, auto b)
        {
            REQUIRE(a == expectedParam1);
            REQUIRE(b == expectedParam2);
            return a + b;
        };
        constexpr auto add1 = curry(add, expectedParam1);
        REQUIRE(add1(expectedParam2) == (expectedParam1 + expectedParam2));
    }
    SECTION("Three parameters")
    {
        constexpr auto expectedParam1 = 1;
        constexpr auto expectedParam2 = 2;
        constexpr auto expectedParam3 = 3;
        constexpr auto add = [](auto a, auto b, auto c)
        {
            REQUIRE(a == expectedParam1);
            REQUIRE(b == expectedParam2);
            REQUIRE(c == expectedParam3);
            return a + b + c;
        };
        constexpr auto add1 = curry(add, expectedParam1);
        REQUIRE(add1(expectedParam2, expectedParam3) == (expectedParam1 + expectedParam2 + expectedParam3));
    }
}

#endif // (__cpp_explicit_this_parameter >= 202110L)

} // namespace morpheus::functional
