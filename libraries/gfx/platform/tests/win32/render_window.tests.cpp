#include "morpheus/gfx/platform/win32/render_window.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::win32
{

TEST_CASE("Ensure image accessors", "[morpheus.gfx.win32.render_window]")
{
    RenderWindow::Config const config;
    RenderWindow window(config);

    REQUIRE(!window.isFullScreen());
    REQUIRE(window.width() == config.width);
    REQUIRE(window.height() == config.height);
    REQUIRE(window.colourDepth() == config.colourDepth);

    RECT rect;
    if (GetClientRect(window.getHandle(), &rect))
    {
        REQUIRE(window.width() == static_cast<std::int16_t>(rect.right - rect.left));
        REQUIRE(window.height() == static_cast<std::int16_t>(rect.bottom - rect.top));
    }
}

} // namespace morpheus::gfx::win32
