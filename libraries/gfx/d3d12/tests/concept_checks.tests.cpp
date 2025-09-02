#include <morpheus/gfx/d3d12/render_system.hpp>
#include <morpheus/gfx/platform/concepts/render_system.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::gfx::gl4
{

TEST_CASE("Test the D3D12 render system adheres to GFX concepts", "[morpheus.gfx.d3d12.concept_checks]")
{
    STATIC_REQUIRE(concepts::RenderSystem<RenderSystem>);
}

} // namespace morpheus::gfx::gl4
