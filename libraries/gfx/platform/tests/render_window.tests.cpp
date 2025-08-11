#include "morpheus/gfx/platform/render_window.hpp"
#include "morpheus/application/po/options.hpp"
#include "morpheus/application/version.hpp"
#include "morpheus/logging.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <optional>
#include <string>
#include <string_view>

namespace morpheus::gfx
{

TEST_CASE_METHOD(LoggingFixture, "Test parsing of WindowConfig options", "[morpheus.gfx.window_config.add_options]")
{
    // clang-format off
    std::array cliOptions = {
        "dummyProgram.exe",
        "--window-name", "Test Window",
        "--width", "400",
        "--height", "300",
        "--colour-depth", "64",
        "--start-x", "101",
        "--start-y", "102",
        "--full-screen", "true",
        "--visible", "true"
    };
    // clang-format on
    WindowConfig config;
    auto const result = application::po::parseProgramOptions(cliOptions, application::po::HelpDocumentation{}, config);
    REQUIRE(!result);

    REQUIRE(config.windowName == "Test Window");
    REQUIRE(config.width == 400);
    REQUIRE(config.height == 300);
    REQUIRE(config.colourDepth == 64);
    REQUIRE(config.startX == 101);
    REQUIRE(config.startY == 102);
    REQUIRE(config.fullScreen == true);
    REQUIRE(config.visible == true);
}

TEST_CASE_METHOD(LoggingFixture, "Test construction of a render window via a config", "[morpheus.gfx.window_config.add_options]")
{
    WindowConfig config;
    RenderWindow window(config);

    REQUIRE(window.name() == "MorpheusWindow");
    REQUIRE(window.width() == 800);
    REQUIRE(window.height() == 600);
    REQUIRE(window.colourDepth() == 32);
    REQUIRE(window.startX() == 0);
    REQUIRE(window.startY() == 0);
    REQUIRE(window.fullScreen() == false);
}

} // namespace morpheus::gfx
