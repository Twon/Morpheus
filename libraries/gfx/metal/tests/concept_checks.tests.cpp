#include <morpheus/gfx/metal/render_system.hpp>
#include <morpheus/gfx/platform/concepts/render_system.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::gfx::metal
{

TEST_CASE("Test the Metal render system adheres to GFX concepts", "[morpheus.gfx.metal.concept_checks]")
{
    STATIC_REQUIRE(concepts::RenderSystem<RenderSystem>);
}

} // namespace morpheus::gfx::metal
