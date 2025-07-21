#include <morpheus/gfx/d3d12/render_system.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::gfx::d3d12::test
{
// using namespace morpheus::gfx;

TEST_CASE("Verify the Graphics API", "[morpheus.gfx.d3d12.render_system.api]")
{
    STATIC_REQUIRE(RenderSystem::getGraphicsApi() == "Direct X 12");
}

} // namespace morpheus::gfx::d3d12::test
