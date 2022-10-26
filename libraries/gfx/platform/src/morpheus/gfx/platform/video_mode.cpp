#include <core/gfx/video_mode.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

constexpr VideoMode::VideoMode(
    const std::uint16_t width,
    const std::uint16_t height,
    const std::uint16_t colourDepth,
    const std::uint16_t refreshRate
)
:   mWidth(width),
    mHeight(height),
    mColourDepth(colourDepth),
    mRefreshRate(refreshRate)
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
