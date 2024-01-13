#include "morpheus/core/meta/concepts/trait.hpp"

#include <catch2/catch_all.hpp>

#include <type_traits>

namespace morpheus::meta
{

TEST_CASE("Meta is string allows the compile time detection of string types", "[morpheus.meta.concepts.trait]")
{
    SECTION("std::is_aggregate Test")
    {
        struct AggregateTest
        {
            double first;
            int second;
        };

        STATIC_REQUIRE(meta::concepts::Trait<AggregateTest, std::is_aggregate>);
    }
    SECTION("std::is_const Test")
    {
        using ConstInt = int const;
        STATIC_REQUIRE(meta::concepts::Trait<ConstInt, std::is_const>);
    }
    SECTION("std::is_enum Test")
    {
        struct EmptyTest {};
        STATIC_REQUIRE(meta::concepts::Trait<EmptyTest, std::is_empty>);
    }
    SECTION("std::is_enum Test")
    {
        enum Lights
        {
            On,
            Off
        };

        STATIC_REQUIRE(meta::concepts::Trait<Lights, std::is_enum>);
    }
    SECTION("std::is_final Test")
    {
        struct FinalTest final {};
        STATIC_REQUIRE(meta::concepts::Trait<FinalTest, std::is_final>);
    }
}

} // namespace morpheus::meta
