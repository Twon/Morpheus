#include "morpheus/containers/concepts/archtypes/associative.hpp"
#include "morpheus/core/containers/concepts/associative.hpp"

#include <catch2/catch_all.hpp>

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace morpheus::containers::concepts
{

TEMPLATE_TEST_CASE("Verify associative containers concepts", "[morpheus.containers.concepts.associative]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archetype test")
    {
        STATIC_REQUIRE(Associative<archetypes::Associative<false, false>>);
        STATIC_REQUIRE(Associative<archetypes::Associative<true, false>>);
        STATIC_REQUIRE(Associative<archetypes::Associative<false, true>>);
        STATIC_REQUIRE(Associative<archetypes::Associative<true, true>>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(!Associative<std::deque<TestType>>);
        STATIC_REQUIRE(!Associative<std::forward_list<TestType>>);
        STATIC_REQUIRE(!Associative<std::list<TestType>>);
        STATIC_REQUIRE(Associative<std::map<TestType, TestType>>);
        STATIC_REQUIRE(Associative<std::multimap<TestType, TestType>>);
        STATIC_REQUIRE(Associative<std::multiset<TestType>>);
        STATIC_REQUIRE(Associative<std::set<TestType>>);
        STATIC_REQUIRE(!Associative<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(!Associative<std::unordered_multimap<TestType, TestType>>);
        STATIC_REQUIRE(!Associative<std::unordered_multiset<TestType>>);
        STATIC_REQUIRE(!Associative<std::unordered_set<TestType>>);
        STATIC_REQUIRE(!Associative<std::vector<TestType>>);
    }
}

} // namespace morpheus::containers::concepts
