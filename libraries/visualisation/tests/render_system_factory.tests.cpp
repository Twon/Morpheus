#include <morpheus/vis/render_system_factory.hpp>

#include <catch2/catch_all.hpp>

#include <array>
#include <string_view>

namespace morpheus::vis
{

TEST_CASE("Test RenderSystem Factory command line options", "[morpheus.vis.render_system_factory]")
{
    SECTION("Ensure valid value parse correctly")
    {
        auto const getAPI = [](std::string_view param)
        {
            RenderSystemFactory renderSystemFactory;
            std::array cliOptions = {"dummyProgram.exe", "--render-system", param.data()};
            auto const result = application::po::parseProgramOptions(cliOptions, app::po::HelpDocumentation(), renderSystemFactory);
            REQUIRE(!result);
            return renderSystemFactory.getActiveAPI();
        };

        REQUIRE(getAPI("Metal") == API::Metal);
        REQUIRE(getAPI("D3D12") == API::D3D12);
        REQUIRE(getAPI("OpenGL4") == API::OpenGL4);
        REQUIRE(getAPI("Vulkan") == API::Vulkan);
    }
}

} // namespace morpheus::vis
