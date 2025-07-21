#include <morpheus/gfx/metal/render_system.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::gfx::metal
{

TEST_CASE("Verify the Graphics API", "[morpheus.gfx.metal.render_system.api]")
{
    STATIC_REQUIRE(RenderSystem::getGraphicsApi() == "Metal");
}

} // namespace morpheus::gfx::metal
