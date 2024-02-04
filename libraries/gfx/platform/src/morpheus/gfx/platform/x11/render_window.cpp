#include <morpheus/core/base/exceptions.hpp>
#include <morpheus/gfx/platform/x11/render_window.hpp>

namespace morpheus::gfx::x11
{

namespace
{
/*
void test()
{
    Display	const xDisplay = XOpenDisplay(nullptr);
    if (!xDisplay)
        throwRuntimeException("Unable to connect to X server\n");

    auto xScreen = DefaultScreen(xDisplay);
    auto xRoot = RootWindow(xDisplay, xScreen);
    std::array<int, 10> const attributes =
    {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER, True,
        GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE,   8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE,  8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 16,
        None
    };

    int elements = 0;
    auto config = glXChooseFBConfig(xDisplay, xScreen, attributes.data(), &elements);
}
*/

auto createDisplay()
{
    if (auto const display = XOpenDisplay(nullptr); display)
        return display;
    else
        throwRuntimeException("Unable to open XDisplay");
}

}

RenderWindow::RenderWindow(Config const& config)
: gfx::RenderWindow(config)
, mDisplay(createDisplay())
/*
, mWindow(
    [&]{
	    auto const screen = DefaultScreenOfDisplay(display);
	    auto const screenId = DefaultScreen(display);
	    return XCreateSimpleWindow(display, RootWindowOfScreen(screen), config.startX, config.startY, config.width, config.heigh, 1, BlackPixel(display, screenId), WhitePixel(display, screenId))
    }(),
    [&](auto const window){ XDestroyWindow(mDisplay, window); }(),
  )
*/
{
}

RenderWindow::~RenderWindow()
{

}

} // namespace morpheus::gfx::x11
