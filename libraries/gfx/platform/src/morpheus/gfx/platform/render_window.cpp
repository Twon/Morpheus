#include <morpheus/gfx/platform/render_window.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

RenderWindow::RenderWindow(Config const& config)
:   RenderTarget(config.width, config.height, config.colourDepth)
,   mStartX(config.startX)
,   mStartY(config.startY)
,   mWindowName(config.windowName)
{
}

//---------------------------------------------------------------------------------------------------------------------

RenderWindow::~RenderWindow()
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
