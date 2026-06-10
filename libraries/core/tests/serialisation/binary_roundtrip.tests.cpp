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

template <typename T>
T binaryRoundtrip(T const& value)
{
    return testing::roundtrip<BinaryWriteSerialiser, BinaryReadSerialiser>(value);
}

TEST_CASE("Binary serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.binary.roundtrip.adapters.std]")
{
    SECTION("Chrono types")
    {
        REQUIRE(binaryRoundtrip(std::chrono::nanoseconds{123}) == std::chrono::nanoseconds{123});
        REQUIRE(binaryRoundtrip(std::chrono::microseconds{456}) == std::chrono::microseconds{456});
        REQUIRE(binaryRoundtrip(std::chrono::milliseconds{789}) == std::chrono::milliseconds{789});
        REQUIRE(binaryRoundtrip(std::chrono::seconds{123}) == std::chrono::seconds{123});
        REQUIRE(binaryRoundtrip(std::chrono::minutes{60}) == std::chrono::minutes{60});
        REQUIRE(binaryRoundtrip(std::chrono::hours{24}) == std::chrono::hours{24});
        REQUIRE(binaryRoundtrip(std::chrono::days{7}) == std::chrono::days{7});
        REQUIRE(binaryRoundtrip(std::chrono::weeks{52}) == std::chrono::weeks{52});
        REQUIRE(binaryRoundtrip(std::chrono::years{100}) == std::chrono::years{100});
        REQUIRE(binaryRoundtrip(std::chrono::months{12}) == std::chrono::months{12});
    }
    REQUIRE(binaryRoundtrip(std::bitset<4>{"1101"}) == std::bitset<4>{"1101"});
    REQUIRE(binaryRoundtrip(conf::vt::indirect<int>{42}) == conf::vt::indirect<int>{42});
    REQUIRE(binaryRoundtrip(std::monostate{}) == std::monostate{});
    REQUIRE(binaryRoundtrip(std::optional<int>{100}) == std::optional<int>{100});
    REQUIRE(binaryRoundtrip(std::optional<int>{}) == std::optional<int>{});
    REQUIRE(binaryRoundtrip(std::pair<int, bool>{50, true}) == std::pair<int, bool>{50, true});
    REQUIRE(binaryRoundtrip(std::string("Hello")) == std::string("Hello"));
    REQUIRE(*binaryRoundtrip(std::make_unique<int>(123)) == 123);
    REQUIRE(binaryRoundtrip(std::vector<int>{1, 2, 3, 4, 5}) == std::vector<int>{1, 2, 3, 4, 5});

    /*  REQUIRE(test::serialise(std::variant<int, bool, std::string>{true}) == R"({"type":"bool","value":true})");
     */
}

TEST_CASE("Binary serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.binary.roundtrip.adapters.boost]")
{
    auto const values = std::vector{1, 2, 3, 4, 5};
    REQUIRE(binaryRoundtrip(boost::circular_buffer<int>{values.begin(), values.end()}) == boost::circular_buffer<int>{values.begin(), values.end()});
    REQUIRE(binaryRoundtrip(boost::dynamic_bitset<>{"1101"}) == boost::dynamic_bitset<>{"1101"});
}

} // namespace morpheus::serialisation
