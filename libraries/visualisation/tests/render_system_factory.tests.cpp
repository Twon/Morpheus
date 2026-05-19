#include <morpheus/application/po/options.hpp>
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
            using namespace morpheus::application::po;
            RenderSystemFactory renderSystemFactory;
            std::array cliOptions = {"dummyProgram.exe", "--render-system", param.data()};
            auto const result = parseProgramOptions(cliOptions, HelpDocumentation(), renderSystemFactory);
            REQUIRE(!result);
            return renderSystemFactory.getActiveAPI();
        };

        REQUIRE(getAPI("Metal") == API::Metal);
        REQUIRE(getAPI("D3D12") == API::D3D12);
        REQUIRE(getAPI("OpenGL4") == API::OpenGL4);
        REQUIRE(getAPI("Vulkan") == API::Vulkan);
    }
}

TEST_CASE("A place holder test", "[morpheus.vis.render_system_factory.available_apis]")
{
    namespace hana = boost::hana;
    static constinit auto apis = RenderSystemFactory::availableAPIs();

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    STATIC_REQUIRE(!hana::contains(apis, RenderSystemType<API::D3D12>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::Metal>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::OpenGL4>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::Vulkan>));
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::D3D12>));
    STATIC_REQUIRE(!hana::contains(apis, RenderSystemType<API::Metal>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::OpenGL4>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::Vulkan>));
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)
    STATIC_REQUIRE(!hana::contains(apis, RenderSystemType<API::D3D12>));
    STATIC_REQUIRE(!hana::contains(apis, RenderSystemType<API::Metal>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::OpenGL4>));
    STATIC_REQUIRE(hana::contains(apis, RenderSystemType<API::Vulkan>));
#endif // #if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
}

} // namespace morpheus::vis
