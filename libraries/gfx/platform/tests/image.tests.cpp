#include "morpheus/gfx/platform/image.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx
{

TEST_CASE("Ensure image accessors", "[morpheus.gfx.image]")
{
    Image image(64, 128, 32);
    REQUIRE(image.width() == 64);
    REQUIRE(image.height() == 128);
    REQUIRE(image.colourDepth() == 32);
}

} // namespace morpheus::gfx
