#include "morpheus/core/meta/is_array.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstdint>
#include <vector>

namespace morpheus::meta
{

TEST_CASE("Meta is array allows the compile time detection of std::array specialisations", "[morpheus.meta.is_array]")
{
    STATIC_REQUIRE(meta::is_array_v<std::array<std::int8_t, 1>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::uint8_t, 2>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::int16_t, 4>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::uint16_t, 8>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::int32_t, 16>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::uint32_t, 32>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::int64_t, 64>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<std::uint64_t, 128>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<float, 256>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<double, 512>>);
    STATIC_REQUIRE(meta::is_array_v<std::array<bool, 1024>>);
    STATIC_REQUIRE(!meta::is_array_v<std::vector<bool>>);
    STATIC_REQUIRE(!meta::is_array_v<bool>);
    STATIC_REQUIRE(!meta::is_array_v<std::uint8_t>);
    STATIC_REQUIRE(!meta::is_array_v<std::int16_t>);
    STATIC_REQUIRE(!meta::is_array_v<std::uint16_t>);
    STATIC_REQUIRE(!meta::is_array_v<std::int32_t>);
    STATIC_REQUIRE(!meta::is_array_v<std::uint32_t>);
    STATIC_REQUIRE(!meta::is_array_v<std::int64_t>);
    STATIC_REQUIRE(!meta::is_array_v<std::uint64_t>);
    STATIC_REQUIRE(!meta::is_array_v<float>);
    STATIC_REQUIRE(!meta::is_array_v<double>);
}

}
