
#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/x11/monitor.hpp>
#include <morpheus/gfx/platform/x11/primitives.hpp>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <string>

using namespace std::literals;

namespace morpheus::gfx::x11
{

concurrency::Generator<Monitor> enumerateMonitors() noexcept
{
    // LCOV_EXCL_START
    auto gfxPimitives =
        makeDisplay()
            .and_then(
                [](DisplayPtr&& display) -> exp_ns::expected<std::tuple<DisplayPtr, Window>, std::string>
                {
                    auto window = DefaultRootWindow(display.get());
                    return std::tuple{std::move(display), std::move(window)};
                })
            .and_then(
                [](std::tuple<DisplayPtr, Window>&& resources) -> exp_ns::expected<std::tuple<DisplayPtr, Window, ScreenResourcePtr>, std::string>
                {
                    auto&& [display, root] = std::move(resources);
                    auto screenRes = makeScreenResource(display.get(), root);
                    if (!screenRes.has_value())
                    {
                        return exp_ns::unexpected("Failed to create screen resource!"s);
                    }
                    return std::tuple(std::move(display), std::move(root), std::move(screenRes).value());
                });

    if (!gfxPimitives.has_value())
    {
        co_return;
    }

    auto& [display, root, resources] = gfxPimitives.value();
    RROutput primary = XRRGetOutputPrimary(display.get(), root);

    for (int i = 0; i < resources->noutput; ++i)
    {
        XRROutputInfo* output = XRRGetOutputInfo(display.get(), resources.get(), resources->outputs[i]);
        if (output && output->connection == RR_Connected)
        {
            XRRCrtcInfo* crtc = XRRGetCrtcInfo(display.get(), resources.get(), output->crtc);
            if (crtc)
            {
                co_yield Monitor{output->name, static_cast<Monitor::PixelDiff>(crtc->x), static_cast<Monitor::PixelDiff>(crtc->y),
                                 static_cast<Monitor::Pixels>(crtc->width), static_cast<Monitor::Pixels>(crtc->height),
                                 // X11 allows for there to be no primary monitor set, in which case we just the monitor as coordinates (0, 0) as primary.

                                 (primary == 0) ? crtc->x == 0 && crtc->y == 0 : (resources->outputs[i] == primary)};
                XRRFreeCrtcInfo(crtc);
            }
        }
        if (output)
            XRRFreeOutputInfo(output);
    }
    // LCOV_EXCL_STOP
}

} // namespace morpheus::gfx::x11
