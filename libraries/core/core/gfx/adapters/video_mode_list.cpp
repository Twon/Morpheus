#include <core/gfx/adapters/video_mode_list.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

video_mode_list::video_mode_list(
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
