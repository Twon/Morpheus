#include "morpheus/containers/concepts/archetypes/sequence.hpp"
#include "morpheus/core/containers/concepts/sequence.hpp"

#include <catch2/catch_all.hpp>

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <vector>

namespace morpheus::containers::concepts
{

TEMPLATE_TEST_CASE("Verify sequence containers concepts", "[morpheus.containers.concepts.sequence]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archetype test")
    {
        STATIC_REQUIRE(Sequence<archetypes::Sequence>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(!Sequence<std::array<TestType, 10>>);
        STATIC_REQUIRE(Sequence<std::deque<TestType>>);
        STATIC_REQUIRE(!Sequence<std::forward_list<TestType>>);
        STATIC_REQUIRE(Sequence<std::list<TestType>>);
        STATIC_REQUIRE(!Sequence<std::string>);
        STATIC_REQUIRE(Sequence<std::vector<TestType>>);
    }
    SECTION("Test strict sequence matches exact STL sequence containers")
    {
        STATIC_REQUIRE(StrictSequence<std::array<TestType, 10>>);
        STATIC_REQUIRE(StrictSequence<std::deque<TestType>>);
        STATIC_REQUIRE(StrictSequence<std::forward_list<TestType>>);
        STATIC_REQUIRE(StrictSequence<std::list<TestType>>);
        STATIC_REQUIRE(StrictSequence<std::string>);
        STATIC_REQUIRE(StrictSequence<std::vector<TestType>>);
    }
}

}
