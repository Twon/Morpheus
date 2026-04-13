#include <morpheus/gfx/platform/render_target.hpp>

namespace morpheus::gfx
{

RenderTarget::RenderTarget(std::uint16_t const width, std::uint16_t const height, std::uint16_t const colourDepth)
    : mWidth(width)
    , mHeight(height)
    , mColourDepth(colourDepth)
{}

} // namespace morpheus::gfx
