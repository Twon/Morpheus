#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
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

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{
using namespace testing;

TEST_CASE("Binary serialisation can roundtrip standard library types to binary and back", "[morpheus.serialisation.binary.roundtrip.adapters.std]")
{
    SECTION("Chrono types")
    {
        REQUIRE(roundtrip(std::chrono::nanoseconds{123}) == std::chrono::nanoseconds{123});
        REQUIRE(roundtrip(std::chrono::microseconds{456}) == std::chrono::microseconds{456});
        REQUIRE(roundtrip(std::chrono::milliseconds{789}) == std::chrono::milliseconds{789});
        REQUIRE(roundtrip(std::chrono::seconds{123}) == std::chrono::seconds{123});
        REQUIRE(roundtrip(std::chrono::minutes{60}) == std::chrono::minutes{60});
        REQUIRE(roundtrip(std::chrono::hours{24}) == std::chrono::hours{24});
        REQUIRE(roundtrip(std::chrono::days{7}) == std::chrono::days{7});
        REQUIRE(roundtrip(std::chrono::weeks{52}) == std::chrono::weeks{52});
        REQUIRE(roundtrip(std::chrono::years{100}) == std::chrono::years{100});
        REQUIRE(roundtrip(std::chrono::months{12}) == std::chrono::months{12});
    }
    REQUIRE(roundtrip(std::monostate{}) == std::monostate{});
    REQUIRE(roundtrip(std::optional<int>{100}) == std::optional<int>{100});
    REQUIRE(roundtrip(std::optional<int>{}) == std::optional<int>{});
    REQUIRE(roundtrip(std::pair<int, bool>{50, true}) == std::pair<int, bool>{50, true});
    REQUIRE(*roundtrip(std::make_unique<int>(123)) == 123);

    /*  REQUIRE(test::serialise(std::variant<int, bool, std::string>{true}) == R"({"type":"bool","value":true})");
        REQUIRE(test::serialise(std::vector<int>{1, 2, 3, 4, 5}) == R"([1,2,3,4,5])");
    */
}

} // namespace morpheus::serialisation
