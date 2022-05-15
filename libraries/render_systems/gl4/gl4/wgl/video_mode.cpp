#include <gl4/wgl/adapters/wgl_video_mode.hpp>

namespace morpheus::gfx::gl4::wgl
{

//---------------------------------------------------------------------------------------------------------------------

video_mode::video_mode(
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
