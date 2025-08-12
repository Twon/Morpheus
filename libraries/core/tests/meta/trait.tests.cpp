#include "morpheus/core/meta/concepts/trait.hpp"

#include <catch2/catch_test_macros.hpp>

#include <type_traits>

#if !MORPHEUS_IS_CLANG_COMPILER || (MORPHEUS_COMP_VER >= 150000000)

namespace morpheus::meta
{

TEST_CASE("Meta Traits allows applying traits as a concept", "[morpheus.meta.concepts.trait]")
{
    SECTION("std::is_aggregate Test")
    {
        struct AggregateTest
        {
            double first;
            int second;
        };

        STATIC_REQUIRE(meta::concepts::Trait<AggregateTest, std::is_aggregate>);
        STATIC_REQUIRE(!meta::concepts::Trait<int, std::is_aggregate>);
    }
    SECTION("std::is_const Test")
    {
        using ConstInt = int const;
        STATIC_REQUIRE(meta::concepts::Trait<ConstInt, std::is_const>);
        STATIC_REQUIRE(!meta::concepts::Trait<int, std::is_const>);
    }
    SECTION("std::is_enum Test")
    {
        struct EmptyTest
        {};
        struct NonEmptyTest
        {
            int a;
        };

        STATIC_REQUIRE(meta::concepts::Trait<EmptyTest, std::is_empty>);
        STATIC_REQUIRE(!meta::concepts::Trait<NonEmptyTest, std::is_empty>);
    }
    SECTION("std::is_enum Test")
    {
        enum Lights
        {
            On,
            Off
        };

        STATIC_REQUIRE(meta::concepts::Trait<Lights, std::is_enum>);
        STATIC_REQUIRE(!meta::concepts::Trait<int, std::is_enum>);
    }
    SECTION("std::is_final Test")
    {
        struct FinalTest final
        {};
        struct NonFinalTest
        {};

        STATIC_REQUIRE(meta::concepts::Trait<FinalTest, std::is_final>);
        STATIC_REQUIRE(!meta::concepts::Trait<NonFinalTest, std::is_final>);
    }
    SECTION("std::is_constructible Test")
    {
        struct ConstructibleTest
        {
            ConstructibleTest(int a, int b)
                : a_(a)
                , b_(b)
            {}

            int a_;
            int b_;
        };

        STATIC_REQUIRE(meta::concepts::Trait<ConstructibleTest, std::is_constructible, int, int>);
        STATIC_REQUIRE(!meta::concepts::Trait<ConstructibleTest, std::is_constructible>);
        STATIC_REQUIRE(!meta::concepts::Trait<ConstructibleTest, std::is_constructible, int>);
        STATIC_REQUIRE(!meta::concepts::Trait<ConstructibleTest, std::is_constructible, int, int, int>);
    }
}

} // namespace morpheus::meta

#endif // !MORPHEUS_IS_CLANG_COMPILER || (MORPHEUS_COMP_VER >= 150000000)
