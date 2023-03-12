#include <morpheus/gfx/platform/image.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

Image::Image(
    std::uint32_t const width,
    std::uint32_t const height,
    std::uint32_t const colourDepth
)
:   mWidth(width),
    mHeight(height),
    mColourDepth(colourDepth)
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
