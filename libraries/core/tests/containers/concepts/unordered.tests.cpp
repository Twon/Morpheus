#include "morpheus/containers/concepts/archtypes/unordered.hpp"
#include "morpheus/core/containers/concepts/unordered.hpp"

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

TEMPLATE_TEST_CASE("Verify unordered containers concepts", "[morpheus.containers.concepts.unordered]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archtype test")
    {
        STATIC_REQUIRE(Unordered<archtypes::Unordered<false, false>>);
        STATIC_REQUIRE(Unordered<archtypes::Unordered<true, false>>);
        STATIC_REQUIRE(Unordered<archtypes::Unordered<false, true>>);
        STATIC_REQUIRE(Unordered<archtypes::Unordered<true, true>>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(!Unordered<std::deque<TestType>>);
        STATIC_REQUIRE(!Unordered<std::forward_list<TestType>>);
        STATIC_REQUIRE(!Unordered<std::list<TestType>>);
        STATIC_REQUIRE(!Unordered<std::map<TestType, TestType>>);
        STATIC_REQUIRE(!Unordered<std::multimap<TestType, TestType>>);
        STATIC_REQUIRE(!Unordered<std::multiset<TestType>>);
        STATIC_REQUIRE(!Unordered<std::set<TestType>>);
        STATIC_REQUIRE(Unordered<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(Unordered<std::unordered_multimap<TestType, TestType>>);
        STATIC_REQUIRE(Unordered<std::unordered_multiset<TestType>>);
        STATIC_REQUIRE(Unordered<std::unordered_set<TestType>>);
        STATIC_REQUIRE(!Unordered<std::vector<TestType>>);
    }
}

} // namespace morpheus::containers::concepts
