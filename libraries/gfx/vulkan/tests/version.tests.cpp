#include "morpheus/gfx/vulkan/version.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::vulkan {

TEST_CASE("Test construction of std::error_code object via make_error_code", "[vulkan.version]")
{
    constexpr std::uint8_t expectedVariant = 0;
    constexpr std::uint8_t expectedMajor = 1;
    constexpr std::uint8_t expectedMinor = 3;
    constexpr std::uint8_t expectedPatch = VK_HEADER_VERSION;
    constexpr Version version(VK_MAKE_API_VERSION(expectedVariant, expectedMajor, expectedMinor, expectedPatch));
    STATIC_REQUIRE(version.variant() == expectedVariant);
    STATIC_REQUIRE(version.major() == expectedMajor);
    STATIC_REQUIRE(version.minor() == expectedMinor);
    STATIC_REQUIRE(version.patch() == expectedPatch);
}

}
