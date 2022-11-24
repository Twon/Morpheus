#include "morpheus/core/serialisation/adapters/std/ranges.hpp"
#include "morpheus/core/meta/concepts/string.hpp"

#include <catch2/catch_all.hpp>

#include <string_view>
#include <utility>

namespace morpheus::serialisation
{

TEST_CASE("Verify serialisation of ranges", "[morpheus.serialisation.ranges]")
{
    STATIC_REQUIRE(detail::IsRange<std::vector<int>>);
//    STATIC_REQUIRE(detail::IsRange<std::string_view>);
//    STATIC_REQUIRE(meta::IsString<std::string_view>);
    STATIC_REQUIRE(meta::IsStringView<std::string_view>);
}

} // morpheus::serialisation