#include <morpheus/vis/render_system_factory.hpp>
#include <morpheus/vis/tui.hpp>
#include <morpheus/vis/visualisation.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::vis
{

TEST_CASE("Test VisualisationConfig default and custom configuration", "[morpheus.vis.config]")
{
    SECTION("Default configuration has expected values")
    {
        VisualisationConfig config;
        REQUIRE(config.windowConfig.windowName == "MorpheusWindow");
        REQUIRE(config.windowConfig.width == 800);
        REQUIRE(config.windowConfig.height == 600);
        REQUIRE(config.windowConfig.colourDepth == 32);
        REQUIRE(!config.windowConfig.fullScreen);
        REQUIRE(config.windowConfig.visible);
        REQUIRE(config.vsync);
        REQUIRE(config.msaaSamples == 1);
        REQUIRE(config.targetFps == 60);
    }

    SECTION("Custom configuration updates appropriately")
    {
        VisualisationConfig config;
        config.selectedApi = API::Metal;
        config.renderSystemName = "Metal";
        config.windowConfig.windowName = "Custom Viewer";
        config.windowConfig.width = 1920;
        config.windowConfig.height = 1080;
        config.windowConfig.fullScreen = true;
        config.msaaSamples = 4;
        config.vsync = true;
        config.targetFps = 120;
        config.enableValidationLayers = true;

        REQUIRE(config.selectedApi == API::Metal);
        REQUIRE(config.windowConfig.windowName == "Custom Viewer");
        REQUIRE(config.windowConfig.width == 1920);
        REQUIRE(config.windowConfig.height == 1080);
        REQUIRE(config.windowConfig.fullScreen);
        REQUIRE(config.msaaSamples == 4);
        REQUIRE(config.targetFps == 120);
        REQUIRE(config.enableValidationLayers);
    }
}

TEST_CASE("Test available rendering APIs query", "[morpheus.vis.render_system_factory]")
{
    SECTION("Querying available APIs info returns valid values")
    {
        std::size_t count = 0;
        boost::hana::for_each(RenderSystemFactory::availableAPIs(),
                              [&](auto const& pair)
                              {
                                  auto value = boost::hana::second(pair);
                                  using RenderSystem = typename decltype(value)::type;
                                  REQUIRE(!RenderSystem::getGraphicsApi().empty());
                                  REQUIRE(!RenderSystem::getGraphicsApiDescription().empty());
                                  ++count;
                              });

        REQUIRE(count > 0);
    }
}

TEST_CASE("Test Visualisation template and window association", "[morpheus.vis.visualisation]")
{
    SECTION("Window type is deduced directly from RenderSystem::Window")
    {
#if (MORPHEUS_RENDER_SYSTEM_METAL)
        STATIC_REQUIRE(std::is_same_v<Visualisation<gfx::metal::RenderSystem>::RenderSystemType, gfx::metal::RenderSystem>);
        STATIC_REQUIRE(std::is_same_v<Visualisation<gfx::metal::RenderSystem>::WindowType, gfx::metal::RenderSystem::Window>);
        STATIC_REQUIRE(std::is_same_v<Visualisation<gfx::metal::RenderSystem>::WindowType, gfx::macos::RenderWindow>);
#endif
    }
}

} // namespace morpheus::vis
