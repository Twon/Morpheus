#include "core/meta/is_string.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::meta
{

TEST_CASE("Meta is string allows the compile time detection of string types", "[morpheus.meta.is_string]")
{
    STATIC_REQUIRE(meta::is_string_v<std::string>);
    STATIC_REQUIRE(meta::is_string_v<std::wstring>);
    STATIC_REQUIRE(meta::is_string_v<std::u8string>);
    STATIC_REQUIRE(meta::is_string_v<std::u16string>);
    STATIC_REQUIRE(meta::is_string_v<std::u32string>);
    STATIC_REQUIRE(!meta::is_string_v<std::string_view>);
    STATIC_REQUIRE(!meta::is_string_v<std::wstring_view>);
    STATIC_REQUIRE(!meta::is_string_v<std::u8string_view>);
    STATIC_REQUIRE(!meta::is_string_v<std::u16string_view>);
    STATIC_REQUIRE(!meta::is_string_v<std::u32string_view>);
    STATIC_REQUIRE(!meta::is_string_v<std::int8_t>);
    STATIC_REQUIRE(!meta::is_string_v<bool>);
    STATIC_REQUIRE(!meta::is_string_v<std::uint8_t>);
    STATIC_REQUIRE(!meta::is_string_v<std::int16_t>);
    STATIC_REQUIRE(!meta::is_string_v<std::uint16_t>);
    STATIC_REQUIRE(!meta::is_string_v<std::int32_t>);
    STATIC_REQUIRE(!meta::is_string_v<std::uint32_t>);
    STATIC_REQUIRE(!meta::is_string_v<std::int64_t>);
    STATIC_REQUIRE(!meta::is_string_v<std::uint64_t>);
    STATIC_REQUIRE(!meta::is_string_v<float>);
    STATIC_REQUIRE(!meta::is_string_v<double>);
}

TEST_CASE("Meta is string allows the compile time detection of string view types", "[morpheus.meta.is_string_view]")
{
    STATIC_REQUIRE(!meta::is_string_view_v<std::string>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::wstring>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::u8string>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::u16string>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::u32string>);
    STATIC_REQUIRE(meta::is_string_view_v<std::string_view>);
    STATIC_REQUIRE(meta::is_string_view_v<std::wstring_view>);
    STATIC_REQUIRE(meta::is_string_view_v<std::u8string_view>);
    STATIC_REQUIRE(meta::is_string_view_v<std::u16string_view>);
    STATIC_REQUIRE(meta::is_string_view_v<std::u32string_view>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::int8_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<bool>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::uint8_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::int16_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::uint16_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::int32_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::uint32_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::int64_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<std::uint64_t>);
    STATIC_REQUIRE(!meta::is_string_view_v<float>);
    STATIC_REQUIRE(!meta::is_string_view_v<double>);
}

} // namespace morpheus::meta
