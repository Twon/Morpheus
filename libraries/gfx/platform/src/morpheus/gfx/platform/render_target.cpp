#include <morpheus/gfx/platform/render_target.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

RenderTarget::RenderTarget(
    const std::uint32_t width,
    const std::uint32_t height,
    const std::uint32_t colourDepth
)
:   mWidth(width),
    mHeight(height),
    mColourDepth(colourDepth)
{
}

//---------------------------------------------------------------------------------------------------------------------

RenderTarget::~RenderTarget()
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
