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

#include <catch2/catch_test_macros.hpp>

#include <bitset>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

using namespace Catch;

namespace morpheus::serialisation
{
using namespace testing;

template <typename T>
T jsonRoundtrip(T const& value)
{
    return testing::roundtrip<JsonWriteSerialiser, JsonReadSerialiser>(value);
}

TEST_CASE("Json serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.json.roundtrip.adapters.std]")
{
    SECTION("Chrono types")
    {
        REQUIRE(jsonRoundtrip(std::chrono::nanoseconds{123}) == std::chrono::nanoseconds{123});
        REQUIRE(jsonRoundtrip(std::chrono::microseconds{456}) == std::chrono::microseconds{456});
        REQUIRE(jsonRoundtrip(std::chrono::milliseconds{789}) == std::chrono::milliseconds{789});
        REQUIRE(jsonRoundtrip(std::chrono::seconds{123}) == std::chrono::seconds{123});
        REQUIRE(jsonRoundtrip(std::chrono::minutes{60}) == std::chrono::minutes{60});
        REQUIRE(jsonRoundtrip(std::chrono::hours{24}) == std::chrono::hours{24});
        REQUIRE(jsonRoundtrip(std::chrono::days{7}) == std::chrono::days{7});
        REQUIRE(jsonRoundtrip(std::chrono::weeks{52}) == std::chrono::weeks{52});
        REQUIRE(jsonRoundtrip(std::chrono::years{100}) == std::chrono::years{100});
        REQUIRE(jsonRoundtrip(std::chrono::months{12}) == std::chrono::months{12});
    }
    REQUIRE(jsonRoundtrip(std::bitset<4>{"1101"}) == std::bitset<4>{"1101"});
    REQUIRE(jsonRoundtrip(conf::vt::indirect<int>{42}) == conf::vt::indirect<int>{42});
    REQUIRE(jsonRoundtrip(std::monostate{}) == std::monostate{});
    REQUIRE(jsonRoundtrip(std::optional<int>{100}) == std::optional<int>{100});
    REQUIRE(jsonRoundtrip(std::optional<int>{}) == std::optional<int>{});
    REQUIRE(jsonRoundtrip(std::pair<int, bool>{50, true}) == std::pair<int, bool>{50, true});
    REQUIRE(jsonRoundtrip(std::string("Hello")) == std::string("Hello"));
    REQUIRE(*jsonRoundtrip(std::make_unique<int>(123)) == 123);
    REQUIRE(jsonRoundtrip(std::vector<int>{1, 2, 3, 4, 5}) == std::vector<int>{1, 2, 3, 4, 5});
    REQUIRE(jsonRoundtrip(std::variant<int, bool, std::string>{true}) == std::variant<int, bool, std::string>{true});
}

TEST_CASE("Json serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.json.roundtrip.adapters.boost]")
{
    auto const values = std::vector{1, 2, 3, 4, 5};
    REQUIRE(jsonRoundtrip(boost::circular_buffer<int>{values.begin(), values.end()}) == boost::circular_buffer<int>{values.begin(), values.end()});
    REQUIRE(jsonRoundtrip(boost::dynamic_bitset<>{"1101"}) == boost::dynamic_bitset<>{"1101"});
}

} // namespace morpheus::serialisation
