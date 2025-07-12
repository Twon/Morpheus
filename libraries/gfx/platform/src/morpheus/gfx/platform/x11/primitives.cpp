#include <morpheus/gfx/platform/x11/primitives.hpp>

#include <string>

using namespace std::literals;

namespace morpheus::gfx::x11
{

namespace detail
{
// LCOV_EXCL_START
void XCloseDisplayDispatch::operator()(::Display* display)
{
    if (display)
    {
        XCloseDisplay(display);
    }
}

XDestroyWindowDispatch::XDestroyWindowDispatch(::Display* display) noexcept
:   mDisplay(display)
{}

void XDestroyWindowDispatch::operator()(typename XDestroyWindowDispatch::pointer window)
{
    if (mDisplay && window)
    {
        XDestroyWindow(mDisplay, window);
    }
}

void XDestroyScreenResource::operator()(typename XDestroyScreenResource::pointer screenResource)
{
    if (screenResource)
    {
        XRRFreeScreenResources(screenResource);
    }
}
// LCOV_EXCL_STOP

} // namespace detail



// LCOV_EXCL_START
exp_ns::expected<DisplayPtr, std::string> makeDisplay()
{
    ::Display* display = XOpenDisplay(nullptr);
    if (!display) {
        return exp_ns::unexpected("Failed to create display!"s);
    }
    return DisplayPtr(display);
}

exp_ns::expected<std::tuple<DisplayPtr, WindowPtr>, std::string> makeWindow(DisplayPtr&& display, WindowConfig const& config)
{
    if (!display) {
        return exp_ns::unexpected("Display pointer is null!"s);
    }

    ::Window window = XCreateSimpleWindow(
        display.get(), DefaultRootWindow(display.get()),
        config.startX, config.startY,
        config.width, config.height,
        1, BlackPixel(display.get(), 0), WhitePixel(display.get(), 0)
    );

    if (!window) {
        return exp_ns::unexpected("Failed to create window!"s);
    }

    XMapWindow(display.get(), window);
    WindowPtr windowPtr(window, detail::XDestroyWindowDispatch(display.get()));
    return std::tuple{std::move(display), std::move(windowPtr)};
}

exp_ns::expected<ScreenResourcePtr, std::string> makeScreenResource(::Display* display, ::Window window)
{
    ::XRRScreenResources* resources = XRRGetScreenResources(display, window);
    if (!resources) {
        return exp_ns::unexpected("Failed to get screen resources!"s);
    }

    return ScreenResourcePtr(resources, detail::XDestroyScreenResource());
}
// LCOV_EXCL_STOP

} // namespace morpheus::gfx::x11
