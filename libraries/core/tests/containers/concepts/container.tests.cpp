#include "morpheus/containers/concepts/archtypes/container.hpp"
#include "morpheus/core/containers/concepts/container.hpp"
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

/*
template <typename T>
concept IsStdForwardList = morpheus::meta::IsSpecialisationOf<std::forward_list, T>;

namespace std {

template<IsStdForwardList C> 
constexpr auto size(C const& c)
{
    return static_cast<std::size_t>(std::distance(c.begin(), c.end()));
}

}
*/
namespace morpheus::containers::concepts
{

TEMPLATE_TEST_CASE("Verify containers concepts", "[morpheus.containers.concepts.container]", bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, float, double)
{
    SECTION("Archtype test")
    {
        STATIC_REQUIRE(Container<archtypes::Container>);
    }
    SECTION("STL container tests")
    {
        STATIC_REQUIRE(Container<std::array<TestType, 10>>);
        STATIC_REQUIRE(Container<std::deque<TestType>>);
        // std::forward_list is listed as a sequence container, but the standard makes the exception that it fits the container requirement
        // even though it does not have a size member.  To validate this the test provides a customisation of size for std::forward_list so
        // we can valid it meets all other requirements of the container.
        STATIC_REQUIRE(Container<std::forward_list<TestType>>);
        STATIC_REQUIRE(Container<std::list<TestType>>);
        STATIC_REQUIRE(Container<std::map<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::multimap<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::multiset<TestType>>);
        STATIC_REQUIRE(Container<std::set<TestType>>);
        STATIC_REQUIRE(Container<std::unordered_set<TestType>>);
        STATIC_REQUIRE(Container<std::unordered_map<TestType, TestType>>);
        STATIC_REQUIRE(Container<std::vector<TestType>>);
    }

}

} // namespace morpheus::containers::concepts
