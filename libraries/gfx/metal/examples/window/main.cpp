#include <morpheus/core/conformance/print.hpp>
#include <morpheus/gfx/platform/macos/monitor.hpp>
#include <morpheus/gfx/platform/macos/render_window.hpp>

#include <iostream>

using namespace morpheus;
using namespace morpheus::gfx::macos;

int main(int argc, const char * argv[])
{
    // NSLog (@"Window name: %@\nWidth: %ld\nHeight: %ld\nColour Depth: %ld\n", windowName, static_cast<long>(width), static_cast<long>(height), static_cast<long>(colourDepth));
    for (const auto& monitors : enumerateMonitors())
    {
        fmt_ns::print("Monitor: {}\n", monitors);
        std::cout.flush();  // Ensure it's not buffered
    }

    RenderWindow::Config config;
    RenderWindow window(config);
}
