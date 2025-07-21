#include <morpheus/gfx/gl4/render_system.hpp>
#include <morpheus/gfx/gl4/traits.hpp>

#include <catch2/catch_test_macros.hpp>

namespace morpheus::gfx::gl4::test
{
// using namespace morpheus::gfx;

TEST_CASE("Verify the Graphics API", "[morpheus.gfx.gl4.render_system.api]")
{
    STATIC_REQUIRE(RenderSystem<GL4Traits>::getGraphicsApi() == "Open GL 4");
}

TEST_CASE("Test the GL render system", "[morpheus.gfx.gl4.render_system]")
{
}

} // namespace morpheus::gfx::gl4::test
