#include "morpheus/gfx/platform/win32/render_window.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::win32
{

TEST_CASE("Ensure move construction of a win32 render window", "[morpheus.gfx.win32.render_window.construct.move]")
{
    //RenderWindow::Config const config;
    //RenderWindow window(config);

    //REQUIRE(!window.fullScreen());
    //REQUIRE(window.width() == config.width);
    //REQUIRE(window.height() == config.height);
    //REQUIRE(window.colourDepth() == config.colourDepth);

    //RenderWindow newWindow(std::move(window));
    //REQUIRE(!newWindow.fullScreen());
    //REQUIRE(newWindow.width() == config.width);
    //REQUIRE(newWindow.height() == config.height);
    //REQUIRE(newWindow.colourDepth() == config.colourDepth);
}

TEST_CASE("Ensure default construction of a win32 render window by defaulted config accessors", "[morpheus.gfx.win32.render_window]")
{
    //RenderWindow::Config const config;
    //RenderWindow window(config);

    //REQUIRE(!window.fullScreen());
    //REQUIRE(window.width() == config.width);
    //REQUIRE(window.height() == config.height);
    //REQUIRE(window.colourDepth() == config.colourDepth);
    //REQUIRE(IsWindowVisible(window.getHandle()));

    //RECT rect;
    //REQUIRE(GetClientRect(window.getHandle(), &rect));
    //REQUIRE(window.width() == static_cast<std::int16_t>(rect.right - rect.left));
    //REQUIRE(window.height() == static_cast<std::int16_t>(rect.bottom - rect.top));
}

} // namespace morpheus::gfx::win32
