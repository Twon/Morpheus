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

} // namespace


RenderWindow::RenderWindow(Config const& config, DisplayPtr&& display, WindowPtr&& window)
: gfx::RenderWindow(config)
, mDisplay(std::move(display))
, mWindow(std::move(window))
{
    // Set the window name
    XStoreName(mDisplay.get(), mWindow.get(), config.windowName.c_str());
}

exp_ns::expected<RenderWindow, std::string> RenderWindow::create(RenderWindow::Config const& config)
{
    return makeDisplay().and_then(
        [&](DisplayPtr&& display) {
            return makeWindow(std::move(display), config).and_then(
                [&](std::tuple<DisplayPtr, WindowPtr>&& resources) -> exp_ns::expected<RenderWindow, std::string> {
                    auto&& [displayPtr, windowPtr] = std::move(resources);
                    return exp_ns::expected<RenderWindow, std::string>(RenderWindow(config, std::move(displayPtr), std::move(windowPtr) ));
                }
            );
        }
    );
}


} // namespace morpheus::gfx::x11
