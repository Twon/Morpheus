#include "morpheus/containers/concepts/archetypes/container.hpp"
#include "morpheus/core/containers/concepts/container.hpp"
#include "morpheus/core/meta/is_specialisation.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

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

TEMPLATE_TEST_CASE("Verify containers concepts", "[morpheus.containers.concepts.container]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archetype test")
    {
        STATIC_REQUIRE(Container<archetypes::Container>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(Container<std::array<TestType, 10>>);
        STATIC_REQUIRE(Container<std::deque<TestType>>);
        STATIC_REQUIRE(Container<std::forward_list<TestType>>);
        STATIC_REQUIRE(Container<std::list<TestType>>);
        STATIC_REQUIRE(Container<std::map<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::multimap<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::multiset<TestType>>);
        STATIC_REQUIRE(Container<std::set<TestType>>);
        STATIC_REQUIRE(Container<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::unordered_multimap<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::unordered_multiset<TestType>>);
        STATIC_REQUIRE(Container<std::unordered_set<TestType>>);
        STATIC_REQUIRE(Container<std::vector<TestType>>);
    }
}

} // namespace morpheus::containers::concepts
