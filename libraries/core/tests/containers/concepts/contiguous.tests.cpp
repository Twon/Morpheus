#include "morpheus/containers/concepts/archetypes/sequence.hpp"
#include "morpheus/core/containers/concepts/contiguous.hpp"
#include "morpheus/core/meta/is_specialisation.hpp"

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

TEMPLATE_TEST_CASE("Verify contiguous containers concepts", "[morpheus.containers.concepts.contiguous]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archetype test")
    {
        STATIC_REQUIRE(Contiguous<archetypes::Sequence>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(Contiguous<std::array<TestType, 10>>);
        STATIC_REQUIRE(!Contiguous<std::deque<TestType>>);
        STATIC_REQUIRE(!Contiguous<std::forward_list<TestType>>);
        STATIC_REQUIRE(!Contiguous<std::list<TestType>>);
        STATIC_REQUIRE(!Contiguous<std::map<TestType, TestType>>);
        STATIC_REQUIRE(!Contiguous<std::multimap<TestType, TestType>>);
        STATIC_REQUIRE(!Contiguous<std::multiset<TestType>>);
        STATIC_REQUIRE(!Contiguous<std::set<TestType>>);
        STATIC_REQUIRE(!Contiguous<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(!Contiguous<std::unordered_multimap<TestType, TestType>>);
        STATIC_REQUIRE(!Contiguous<std::unordered_multiset<TestType>>);
        STATIC_REQUIRE(!Contiguous<std::unordered_set<TestType>>);
        if constexpr(std::is_same_v<TestType, bool>)
        {
            STATIC_REQUIRE(!Contiguous<std::vector<TestType>>);
        }
        else
        {
            STATIC_REQUIRE(Contiguous<std::vector<TestType>>);
        }
    }
}

} // namespace morpheus::containers::concepts
