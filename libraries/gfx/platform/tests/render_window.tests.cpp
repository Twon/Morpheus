#include "morpheus/application/application.hpp"
#include "morpheus/gfx/platform/render_window.hpp"
#include "morpheus/logging.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx
{

TEST_CASE_METHOD(LoggingFixture, "Test parsing of WindowConfig options", "[morpheus.gfx.window_config.add_options]")
{
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
    WindowConfig config;
    auto const result = application::po::parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), application::po::HelpDocumentation{}, config);
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

} // namespace morpheus::gfx
