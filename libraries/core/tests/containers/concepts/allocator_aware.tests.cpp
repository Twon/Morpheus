#include "morpheus/containers/concepts/archetypes/allocator_aware.hpp"
#include "morpheus/core/containers/concepts/allocator_aware.hpp"

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

TEMPLATE_TEST_CASE("Verify allocator aware containers concepts", "[morpheus.containers.concepts.allocator_aware]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archtype test")
    {
        STATIC_REQUIRE(AllocatorAware<archetypes::AllocatorAware>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(AllocatorAware<std::deque<TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::forward_list<TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::list<TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::map<TestType, TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::set<TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::unordered_set<TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(AllocatorAware<std::vector<TestType>>);
    }
}

} // namespace morpheus::containers::concepts
