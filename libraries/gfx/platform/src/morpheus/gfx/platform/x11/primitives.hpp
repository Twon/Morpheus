#pragma once

#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/gfx/platform/render_window.hpp>

#include <boost/scope/unique_resource.hpp>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <functional>
#include <memory>

namespace morpheus::gfx::x11
{

namespace detail
{

/// \struct XCloseDisplayDispatch
///     A functor to close an X11 display.
struct XCloseDisplayDispatch
{
    void operator()(::Display* display);
};

/// \struct XDestroyWindowDispatch
///     A functor to close an X11 display.
struct XDestroyWindowDispatch
{
    explicit XDestroyWindowDispatch(::Display* display) noexcept;

    using pointer = ::Window;

    void operator()(pointer window);

private:
    ::Display* mDisplay = nullptr;
};

struct XDestroyScreenResource
{
    using pointer = ::XRRScreenResources*;

    void operator()(pointer screenResource);
};

} // namespace detail

using DisplayPtr = std::unique_ptr<::Display, detail::XCloseDisplayDispatch>;
using WindowPtr = boost::scope::unique_resource<Window, detail::XDestroyWindowDispatch>;
using ScreenResourcePtr = std::unique_ptr<::XRRScreenResources, detail::XDestroyScreenResource>;

/// Creates a display for the X11 platform.
/// \return An expected containing the display pointer or an error message.
conf::exp::expected<DisplayPtr, std::string> makeDisplay();

/// Creates a window for the X11 platform.
/// \param display The display pointer.
/// \param config The configuration for the window.
/// \return An expected containing a tuple of the display pointer and the window pointer, or an error message.
conf::exp::expected<std::tuple<DisplayPtr, WindowPtr>, std::string> makeWindow(DisplayPtr&& display, WindowConfig const& config);

/// Creates a screen resource for the X11 platform.
/// \param display The display pointer.
/// \param window The window.
/// \return An expected containing the screen resource pointer or an error message.
conf::exp::expected<ScreenResourcePtr, std::string> makeScreenResource(::Display* display, ::Window window);

} // namespace morpheus::gfx::x11
