#include "morpheus/core/serialisation/adapters/aggregate.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/adapters/std/monostate.hpp"
#include "morpheus/core/serialisation/adapters/std/optional.hpp"
#include "morpheus/core/serialisation/adapters/std/pair.hpp"
#include "morpheus/core/serialisation/adapters/std/tuple.hpp"
#include "morpheus/core/serialisation/adapters/std/unique_ptr.hpp"
#include "morpheus/core/serialisation/adapters/std/variant.hpp"
#include "morpheus/core/serialisation/adapters/std/vector.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"

#include "morpheus/serialisation/helpers.hpp"

#include <catch2/catch_all.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>


using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Binary reader handles error cases gracefully", "[morpheus.serialisation.binary_reader.error_handling]")
{
    auto constexpr bytes = testing::makeBytes(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    auto constexpr string = std::string_view{"String longer than 4-bytes"};

#if (__cpp_lib_spanstream >= 202106L)
    SECTION("Serialise via spanstream to test failure condition when the the underling stream runs out of memory while writing but does not throw an exception")
    {
        REQUIRE(testing::deserialiseWithSpanStream<std::int64_t>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)) == std::int64_t{100});
        REQUIRE(testing::deserialiseWithSpanStream<std::string>(testing::serialise(string)) == string);
        //REQUIRE(testing::deserialiseWithSpanStream<std::vector<>string>(testing::serialise(std::span{bytes})) == string);
        
        REQUIRE_THROWS_AS(testing::deserialiseWithSpanStream<std::int64_t>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00)), BinaryException);
        REQUIRE_THROWS_AS(testing::deserialiseWithSpanStream<std::string>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)), BinaryException);
        //REQUIRE_THROWS_AS(testing::deserialiseWithSpanStream<std::vector<std::byte>>(testing::makeCharArray(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)),
        //                  BinaryException);
    }
#endif // (__cpp_lib_spanstream >= 202106L)
    SECTION("Serialise via boost::iostream to test failure condition when the the underling stream runs out of memory while writing resulting in an exception")
    {
        /*
        REQUIRE(ranges::equal(testing::serialiseWithLimitedSpace<sizeof(std::int64_t)>(std::int64_t{100}),
                              make_char_array(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)));
        REQUIRE(ranges::equal(testing::serialiseWithLimitedSpace<sizeof(std::size_t) + string.size()>(string), testing::serialise(string)));
        REQUIRE(ranges::equal(testing::serialiseWithLimitedSpace<sizeof(std::size_t) + bytes.size()>(std::span{bytes}), testing::serialise(std::span{bytes})));

        REQUIRE_THROWS_AS(testing::serialiseWithLimitedSpace<sizeof(std::int32_t)>(std::int64_t{100}), std::ios_base::failure);
        REQUIRE_THROWS_AS(testing::serialiseWithLimitedSpace<sizeof(std::int32_t)>(string), std::ios_base::failure);
        REQUIRE_THROWS_AS(testing::serialiseWithLimitedSpace<sizeof(std::int32_t)>(std::span{bytes}), std::ios_base::failure);
        */
    }
}

} // namespace morpheus::serialisation
 