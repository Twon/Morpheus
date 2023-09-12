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
#include "morpheus/core/serialisation/write_serialiser.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"
#include "morpheus/core/serialisation/serialisers.hpp"

#include "morpheus/serialisation/helpers.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

template <typename... Ts>
constexpr std::array<std::byte, sizeof...(Ts)> make_bytes(Ts&&... args) noexcept
{
    return {std::byte(std::forward<Ts>(args))...};
}

template <typename... Ts>
constexpr std::array<char, sizeof...(Ts)> make_char_array(Ts&&... args) noexcept
{
    return {char(std::forward<Ts>(args))...};
}

TEST_CASE("Binary writer handles error cases gracefully", "[morpheus.serialisation.binary_writer.error_handling]")
{
    auto constexpr bytes = make_bytes(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    auto constexpr string = std::string_view{"String longer than 4-bytes"};

#if (__cpp_lib_spanstream >= 202106L)
    SECTION("Serialise via spanstream to test failure condition when the the underling stream runs out of memory while writing but does not throw an exception")
    {
        REQUIRE(ranges::equal(testing::serialiseWithSpanStream<sizeof(std::int64_t)>(std::int64_t{100}),
                              make_char_array(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)));
        REQUIRE(ranges::equal(testing::serialiseWithSpanStream<sizeof(std::size_t) + string.size()>(string), testing::serialise(string)));
        REQUIRE(ranges::equal(testing::serialiseWithSpanStream<sizeof(std::size_t) + bytes.size()>(std::span{bytes}), testing::serialise(std::span{bytes})));

        REQUIRE_THROWS_AS(testing::serialiseWithSpanStream<sizeof(std::int32_t)>(std::int64_t{100}), BinaryException);
        REQUIRE_THROWS_AS(testing::serialiseWithSpanStream<sizeof(std::int64_t)>(string), BinaryException);
        REQUIRE_THROWS_AS(testing::serialiseWithSpanStream<sizeof(std::int64_t)>(std::span{bytes}), BinaryException);
    }
#endif // (__cpp_lib_spanstream >= 202106L)
    SECTION("Serialise via boost::iostream to test failure condition when the the underling stream runs out of memory while writing resulting in an exception")
    {
        REQUIRE(ranges::equal(testing::serialiseWithLimitedSpace<sizeof(std::int64_t)>(std::int64_t{100}), make_char_array(0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)));
        REQUIRE(ranges::equal(testing::serialiseWithLimitedSpace<sizeof(std::size_t) + string.size()>(string), testing::serialise(string)));
        REQUIRE(ranges::equal(testing::serialiseWithLimitedSpace<sizeof(std::size_t) + bytes.size()>(std::span{bytes}), testing::serialise(std::span{bytes})));

        REQUIRE_THROWS_AS(testing::serialiseWithLimitedSpace<sizeof(std::int32_t)>(std::int64_t{100}), std::ios_base::failure);
        REQUIRE_THROWS_AS(testing::serialiseWithLimitedSpace<sizeof(std::int32_t)>(string), std::ios_base::failure);
        REQUIRE_THROWS_AS(testing::serialiseWithLimitedSpace<sizeof(std::int32_t)>(std::span{bytes}), std::ios_base::failure);
    }
}

TEST_CASE("Binary writer can write std types to underlying text representation", "[morpheus.serialisation.binary_writer.adapters.std]")
{
    SECTION("Chrono types")
    {
        // REQUIRE(test::serialisationRoundtrip(std::chrono::nanoseconds{123}) == std::vector<char>{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B});
        // REQUIRE(test::serialisationRoundtrip(std::chrono::nanoseconds{123}) == std::chrono::nanoseconds{123});
        /* REQUIRE(test::serialisationRoundtrip(std::chrono::nanoseconds{123}) == std::chrono::nanoseconds{123});
        REQUIRE(test::serialisationRoundtrip(std::chrono::microseconds{456}) == std::chrono::microseconds{456});
        REQUIRE(test::serialisationRoundtrip(std::chrono::milliseconds{789}) == std::chrono::milliseconds{789});
        REQUIRE(test::serialisationRoundtrip(std::chrono::seconds{123}) == std::chrono::seconds{123});
        REQUIRE(test::serialisationRoundtrip(std::chrono::minutes{60}) == std::chrono::minutes{60});
        REQUIRE(test::serialisationRoundtrip(std::chrono::hours{24}) == std::chrono::hours{24});
        REQUIRE(test::serialisationRoundtrip(std::chrono::days{7}) == std::chrono::days{7});
        REQUIRE(test::serialisationRoundtrip(std::chrono::weeks{52}) == std::chrono::weeks{52});
        REQUIRE(test::serialisationRoundtrip(std::chrono::years{100}) == std::chrono::years{100});
        REQUIRE(test::serialisationRoundtrip(std::chrono::months{12}) == std::chrono::months{12});*/
    }
/*    REQUIRE(test::serialisationRoundtrip(std::monostate{}) == std::monostate{});
    REQUIRE(test::serialisationRoundtrip(std::optional<int>{100}) == std::optional<int>{100});
    REQUIRE(test::serialisationRoundtrip(std::optional<int>{}) == std::optional<int>{});
    REQUIRE(test::serialisationRoundtrip(std::pair<int, bool>{50, true}) == std::pair<int, bool>{50, true});
    REQUIRE(*test::serialisationRoundtrip(std::make_unique<int>(123)) == 123);
    */
    /*  REQUIRE(test::serialise(std::variant<int, bool, std::string>{true}) == R"({"type":"bool","value":true})");
        REQUIRE(test::serialise(std::vector<int>{1, 2, 3, 4, 5}) == R"([1,2,3,4,5])");
    */
}

} // namespace morpheus::serialisation
 