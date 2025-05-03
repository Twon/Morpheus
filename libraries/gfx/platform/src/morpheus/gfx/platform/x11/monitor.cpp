
#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/x11/monitor.hpp>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

namespace morpheus::gfx::x11
{

concurrency::Generator<Monitor> enumerateMonitors() noexcept
{
    Display* display = XOpenDisplay(nullptr);
    if (!display) return result;

    Window root = DefaultRootWindow(display);
    XRRScreenResources* resources = XRRGetScreenResources(display, root);

    for (int i = 0; i < resources->noutput; ++i) {
        XRROutputInfo* output = XRRGetOutputInfo(display, resources, resources->outputs[i]);
        if (output && output->connection == RR_Connected) {
            XRRCrtcInfo* crtc = XRRGetCrtcInfo(display, resources, output->crtc);
            if (crtc) {
                co_yield Monitor{
                    output->name,
                    static_cast<Monitor::Pixels>(crtc->x),
                    static_cast<Monitor::Pixels>(crtc->y),
                    static_cast<Monitor::PixelDiff>(crtc->width),
                    static_cast<Monitor::PixelDiff>(crtc->height),
                    (resources->outputs[i] == XRRGetOutputPrimary(display, root))
                };
                XRRFreeCrtcInfo(crtc);
            }
        }
        if (output) XRRFreeOutputInfo(output);
    }
    XRRFreeScreenResources(resources);
    XCloseDisplay(display);
}

} // namespace morpheus::gfx::x11
