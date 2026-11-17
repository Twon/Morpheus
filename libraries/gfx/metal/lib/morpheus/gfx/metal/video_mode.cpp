#include <morpheus/gfx/metal/video_mode.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

VideoMode::VideoMode(std::uint32_t const width, std::uint32_t const height, std::uint32_t const colourDepth, std::uint32_t const refreshRate)
    : mWidth(width)
    , mHeight(height)
    , mColourDepth(colourDepth)
    , mRefreshRate(refreshRate)
{}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
