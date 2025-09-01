#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/adapters/std/monostate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"

#include "morpheus/serialisation/helpers.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Binary reader handles error cases gracefully", "[morpheus.serialisation.binary_reader.error_handling]")
{
    constexpr auto bytes = testing::makeBytes(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    constexpr auto string = std::string_view{"String longer than 4-bytes"};

#if (__cpp_lib_spanstream >= 202106L)
    SECTION("Serialise via spanstream to test failure condition when the the underling stream runs out of memory while writing but does not throw an exception")
    {
        REQUIRE(testing::deserialiseWithSpanStream<std::int64_t>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)) == std::int64_t{100});
        REQUIRE(testing::deserialiseWithSpanStream<std::string>(testing::serialise(string)) == string);
        REQUIRE(conf::ranges::equal(testing::deserialiseWithSpanStream<std::vector<std::byte>>(testing::serialise(std::span{bytes})), std::span{bytes}));

        REQUIRE_THROWS_AS(testing::deserialiseWithSpanStream<std::int64_t>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00)), BinaryException);
        REQUIRE_THROWS_AS(testing::deserialiseWithSpanStream<std::string>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)),
                          BinaryException);
        REQUIRE_THROWS_AS(testing::deserialiseWithSpanStream<std::vector<std::byte>>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)),
                          BinaryException);
    }
#endif // (__cpp_lib_spanstream >= 202106L)
    SECTION("Serialise via boost::iostream to test failure condition when the the underling stream runs out of memory while writing resulting in an exception")
    {
        REQUIRE(testing::deserialiseWithIoStream<std::int64_t>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)) == std::int64_t{100});
        REQUIRE(testing::deserialiseWithIoStream<std::string>(testing::serialise(string)) == string);
        REQUIRE(conf::ranges::equal(testing::deserialiseWithIoStream<std::vector<std::byte>>(testing::serialise(std::span{bytes})), std::span{bytes}));

        REQUIRE_THROWS_AS(testing::deserialiseWithIoStream<std::int64_t>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00)), BinaryException);
        REQUIRE_THROWS_AS(testing::deserialiseWithIoStream<std::string>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)),
                          BinaryException);
        REQUIRE_THROWS_AS(testing::deserialiseWithIoStream<std::vector<std::byte>>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)),
                          BinaryException);
    }
}

} // namespace morpheus::serialisation
