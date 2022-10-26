#include <morpheus/gfx/platform/image.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

image::image(
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

} // namespace morpheus::gfx
