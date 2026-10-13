#include "morpheus/core/conformance/value_types.hpp"
#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/boost/circular_buffer.hpp"
#include "morpheus/core/serialisation/adapters/boost/dynamic_bitset.hpp"
#include "morpheus/core/serialisation/adapters/std/bitset.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/adapters/std/indirect.hpp"
#include "morpheus/core/serialisation/adapters/std/monostate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"
#include "morpheus/core/serialisation/write_serialiser.hpp"

#include "morpheus/serialisation/helpers.hpp"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <bitset>
#include <chrono>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

using namespace Catch;

namespace morpheus::serialisation
{

namespace test
{

template <class T>
static std::string serialise(std::string_view key, T const& value)
{
    std::ostringstream oss;
    TomlWriteSerialiser serialiser{std::in_place, oss};
    serialiser.serialise(key, value);
    return oss.str();
}

} // namespace test

TEMPLATE_TEST_CASE("Toml Json writer can write single native types to underlying text representation",
                   "[morpheus.serialisation.toml_reader.native]",
                   bool,
                   std::int8_t,
                   std::uint8_t,
                   std::int16_t,
                   std::uint16_t,
                   std::int32_t,
                   std::uint32_t,
                   std::int64_t,
                   std::uint64_t,
                   float,
                   double)
{
    if constexpr (std::is_integral_v<TestType>)
    {
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::min()) == conf::fmt::format("value = {}", std::numeric_limits<TestType>::min()));
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::lowest()) == conf::fmt::format("value = {}", std::numeric_limits<TestType>::lowest()));
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::max()) == conf::fmt::format("value = {}", std::numeric_limits<TestType>::max()));
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::radix) == conf::fmt::format("value = {}", std::numeric_limits<TestType>::radix));
    }
    else if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(test::serialise("value", 0) == "value = 0");
        REQUIRE(test::serialise("value", -0) == "value = 0");
        REQUIRE(test::serialise("value", TestType(2.75)) == "value = 2.75");
        REQUIRE(test::serialise("value", TestType(-2.75)) == "value = -2.75");
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::infinity()) == "value = Infinity");
        REQUIRE(test::serialise("value", -std::numeric_limits<TestType>::infinity()) == "value = -Infinity");
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::quiet_NaN()) == "value = NaN");
        REQUIRE(test::serialise("value", -std::numeric_limits<TestType>::quiet_NaN()) == "value = NaN");
        REQUIRE(test::serialise("value", std::numeric_limits<TestType>::signaling_NaN()) == "value = NaN");
        REQUIRE(test::serialise("value", -std::numeric_limits<TestType>::signaling_NaN()) == "value = NaN");
    }
}

} // namespace morpheus::serialisation
