#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"
#include "morpheus/serialisation/helpers.hpp"
#include "morpheus/serialisation/types/simple_tuple.hpp"

#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include <cstddef>
#include <string>
#include <string_view>

namespace morpheus::serialisation
{

using namespace ::testing;
using namespace morpheus::serialisation::testing;

using namespace std::literals::string_view_literals;

TEST_CASE("Verify serialisation of std::expected", "[morpheus.serialisation.types.simple_tuple.fmt]")
{
    auto const a = SimpleTuple{
        1, true, {std::byte{1}, std::byte{2}, std::byte{3}}
    };
    auto const b = SimpleTuple{
        2, true, {std::byte{10}, std::byte{20}, std::byte{30}}
    };
    auto const c = SimpleTuple{
        3, true, {std::byte{100}, std::byte{200}, std::byte{255}}
    };

    REQUIRE(conf::fmt::format("{}", a) == "{first=1,second=true,data=[1, 2, 3]}");
    REQUIRE(conf::fmt::format("{}", b) == "{first=2,second=true,data=[10, 20, 30]}");
    REQUIRE(conf::fmt::format("{}", c) == "{first=3,second=true,data=[100, 200, 255]}");
}

TEST_CASE("Json writer can write ranges of composites", "[morpheus.serialisation.types.simple_tuple.rountdtrip]")
{
    auto const value = std::vector<testing::SimpleTuple>{
        {1, true,       {std::byte{1}, std::byte{2}, std::byte{3}}},
        {2, true,    {std::byte{10}, std::byte{20}, std::byte{30}}},
        {3, true, {std::byte{100}, std::byte{200}, std::byte{255}}}
    };
    REQUIRE(testing::roundtrip(value) == value);
}

} // namespace morpheus::serialisation
