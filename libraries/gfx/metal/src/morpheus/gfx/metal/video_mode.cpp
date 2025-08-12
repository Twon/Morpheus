#include <morpheus/gfx/metal/video_mode.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

video_mode::video_mode(std::uint32_t const width, std::uint32_t const height, std::uint32_t const colourDepth)
    : mWidth(width)
    , mHeight(height)
    , mColourDepth(colourDepth)
{}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
