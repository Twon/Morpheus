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
T tomlRoundtrip(T const& value)
{
    return testing::roundtrip<TomlWriteSerialiser, TomlReadSerialiser>(value);
}

TEST_CASE("Toml serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.toml.roundtrip.adapters.std]")
{
    SECTION("Chrono types")
    {
        REQUIRE(tomlRoundtrip(std::chrono::nanoseconds{123}) == std::chrono::nanoseconds{123});
        REQUIRE(tomlRoundtrip(std::chrono::microseconds{456}) == std::chrono::microseconds{456});
        REQUIRE(tomlRoundtrip(std::chrono::milliseconds{789}) == std::chrono::milliseconds{789});
        REQUIRE(tomlRoundtrip(std::chrono::seconds{123}) == std::chrono::seconds{123});
        REQUIRE(tomlRoundtrip(std::chrono::minutes{60}) == std::chrono::minutes{60});
        REQUIRE(tomlRoundtrip(std::chrono::hours{24}) == std::chrono::hours{24});
        REQUIRE(tomlRoundtrip(std::chrono::days{7}) == std::chrono::days{7});
        REQUIRE(tomlRoundtrip(std::chrono::weeks{52}) == std::chrono::weeks{52});
        REQUIRE(tomlRoundtrip(std::chrono::years{100}) == std::chrono::years{100});
        REQUIRE(tomlRoundtrip(std::chrono::months{12}) == std::chrono::months{12});
    }
    REQUIRE(tomlRoundtrip(std::bitset<4>{"1101"}) == std::bitset<4>{"1101"});
    REQUIRE(tomlRoundtrip(conf::vt::indirect<int>{42}) == conf::vt::indirect<int>{42});
    REQUIRE(tomlRoundtrip(std::monostate{}) == std::monostate{});
    REQUIRE(tomlRoundtrip(std::optional<int>{100}) == std::optional<int>{100});
    REQUIRE(tomlRoundtrip(std::optional<int>{}) == std::optional<int>{});
    REQUIRE(tomlRoundtrip(std::pair<int, bool>{50, true}) == std::pair<int, bool>{50, true});
    REQUIRE(tomlRoundtrip(std::string("Hello")) == std::string("Hello"));
    REQUIRE(*tomlRoundtrip(std::make_unique<int>(123)) == 123);
    REQUIRE(tomlRoundtrip(std::vector<int>{1, 2, 3, 4, 5}) == std::vector<int>{1, 2, 3, 4, 5});
    REQUIRE(tomlRoundtrip(std::variant<int, bool, std::string>{true}) == std::variant<int, bool, std::string>{true});
}

TEST_CASE("Toml serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.toml.roundtrip.adapters.boost]")
{
    auto const values = std::vector{1, 2, 3, 4, 5};
    REQUIRE(tomlRoundtrip(boost::circular_buffer<int>{values.begin(), values.end()}) == boost::circular_buffer<int>{values.begin(), values.end()});
    REQUIRE(tomlRoundtrip(boost::dynamic_bitset<>{"1101"}) == boost::dynamic_bitset<>{"1101"});
}

} // namespace morpheus::serialisation
