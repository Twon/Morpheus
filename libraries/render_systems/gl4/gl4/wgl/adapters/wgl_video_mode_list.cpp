#include <gl4/wgl/adapters/wgl_video_mode_list.hpp>

namespace morpheus::gfx::gl4::wgl
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

} // namespace morpheus::gfx::gl4::wgl
