#include <morpheus/gfx/platform/x11/primitives.hpp>

#include <string>

using namespace std::literals;

namespace morpheus::gfx::x11
{

namespace detail
{
void XCloseDisplayDispatch::operator()(::Display* display)
{
    XCloseDisplay(display);
}

XDestroyWindowDispatch::XDestroyWindowDispatch(::Display* display) noexcept
:   mDisplay(display)
{}

void XDestroyWindowDispatch::operator()(typename XDestroyWindowDispatch::pointer window)
{
    XDestroyWindow(mDisplay, window);
}

void XDestroyScreenResource::operator()(typename XDestroyScreenResource::pointer screenResource)
{
    XRRFreeScreenResources(screenResource);
}

} // namespace detail



exp_ns::expected<DisplayPtr, std::string> makeDisplay()
{
    // LCOV_EXCL_START
    ::Display* display = XOpenDisplay(nullptr);
    if (!display) {
        return exp_ns::unexpected("Failed to create display!"s);
    }
    return DisplayPtr(display);
    // LCOV_EXCL_STOP
}

exp_ns::expected<std::tuple<DisplayPtr, WindowPtr>, std::string> makeWindow(DisplayPtr&& display, WindowConfig const& config)
{
    // LCOV_EXCL_START
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
    // LCOV_EXCL_STOP
}

exp_ns::expected<ScreenResourcePtr, std::string> makeScreenResource(::Display* display, ::Window window)
{
    // LCOV_EXCL_START
    ::XRRScreenResources* resources = XRRGetScreenResources(display, window);
    if (!resources) {
        return exp_ns::unexpected("Failed to get screen resources!"s);
    }

    return ScreenResourcePtr(resources, detail::XDestroyScreenResource());
    // LCOV_EXCL_STOP
}

} // namespace morpheus::gfx::x11
