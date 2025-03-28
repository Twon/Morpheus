#include "morpheus/containers/concepts/archetypes/reversible.hpp"
#include "morpheus/core/containers/concepts/reversible.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

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

TEMPLATE_TEST_CASE("Verify containers concepts", "[morpheus.containers.concepts.iterator]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archetype test")
    {
        STATIC_REQUIRE(Reversible<archetypes::Reversible>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(Reversible<std::array<TestType, 10>>);
        STATIC_REQUIRE(Reversible<std::deque<TestType>>);
        STATIC_REQUIRE(!Reversible<std::forward_list<TestType>>);
        STATIC_REQUIRE(Reversible<std::list<TestType>>);
        STATIC_REQUIRE(Reversible<std::map<TestType, TestType>>);
        STATIC_REQUIRE(Reversible<std::multimap<TestType, TestType>>);
        STATIC_REQUIRE(Reversible<std::multiset<TestType>>);
        STATIC_REQUIRE(Reversible<std::set<TestType>>);
        STATIC_REQUIRE(!Reversible<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(!Reversible<std::unordered_multimap<TestType, TestType>>);
        STATIC_REQUIRE(!Reversible<std::unordered_multiset<TestType>>);
        STATIC_REQUIRE(!Reversible<std::unordered_set<TestType>>);
        STATIC_REQUIRE(Reversible<std::vector<TestType>>);
    }
}

} // namespace morpheus::containers::concepts
