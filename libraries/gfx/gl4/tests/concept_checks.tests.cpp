#include <morpheus/gfx/gl4/render_system.hpp>
#include <morpheus/gfx/gl4/traits.hpp>
#include <morpheus/gfx/platform/concepts/render_system.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::gfx::gl4
{

TEST_CASE("Test the GL render system adheres to GFX concepts", "[morpheus.gfx.gl4.concept_checks]")
{
    STATIC_REQUIRE(concepts::RenderSystem<GL4Traits>);
}

} // namespace morpheus::gfx::gl4
