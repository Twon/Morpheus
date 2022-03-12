#include <gl4/wgl/adapters/wgl_adapter.hpp>

namespace morpheus::gfx::gl4::wgl
{

//---------------------------------------------------------------------------------------------------------------------

adapter::adapter(
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
