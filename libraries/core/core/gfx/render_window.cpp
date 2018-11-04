#include <core/gfx/render_window.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

render_window::render_window(
    const std::uint32_t width,
    const std::uint32_t height,
    const std::uint32_t colourDepth,
    const std::uint32_t startX,
    const std::uint32_t startY,
    const std::string windowName
)
:   render_target(width, height, colourDepth),
    mStartX(startX),
    mStartY(startY),
    mWindowName(windowName)
{
}

//---------------------------------------------------------------------------------------------------------------------

render_window::~render_window()
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
