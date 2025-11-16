#include <morpheus/vis/render_system_factory.hpp>

#include <catch2/catch_test_macros.hpp>

namespace morpheus::vis
{

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
