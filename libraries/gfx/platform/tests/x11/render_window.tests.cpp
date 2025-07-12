#include "morpheus/gfx/platform/x11/render_window.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::x11
{

TEST_CASE("Ensure move construction of a x11 render window", "[morpheus.gfx.x11.render_window.construct.move]")
{
    RenderWindow::Config const config;
    auto result = RenderWindow::create(config);
    REQUIRE(result);

    auto window(std::move(result).value());

    REQUIRE(!window.fullScreen());
    REQUIRE(window.width() == config.width);
    REQUIRE(window.height() == config.height);
    REQUIRE(window.colourDepth() == config.colourDepth);

    RenderWindow newWindow(std::move(window));
    REQUIRE(!newWindow.fullScreen());
    REQUIRE(newWindow.width() == config.width);
    REQUIRE(newWindow.height() == config.height);
    REQUIRE(newWindow.colourDepth() == config.colourDepth);
}

TEST_CASE("Ensure default construction of a x11 render window by defaulted config accessors", "[morpheus.gfx.x11.render_window]")
{
/*
    RenderWindow::Config const config;
    RenderWindow window(config);

    REQUIRE(!window.fullScreen());
    REQUIRE(window.width() == config.width);
    REQUIRE(window.height() == config.height);
    REQUIRE(window.colourDepth() == config.colourDepth);
    REQUIRE(IsWindowVisible(window.getHandle()));

    RECT rect;
    REQUIRE(GetClientRect(window.getHandle(), &rect));
    REQUIRE(window.width() == static_cast<std::int16_t>(rect.right - rect.left));
    REQUIRE(window.height() == static_cast<std::int16_t>(rect.bottom - rect.top));
*/
}

} // namespace morpheus::gfx::win32
