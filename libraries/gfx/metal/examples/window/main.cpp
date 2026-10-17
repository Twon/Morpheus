#include <morpheus/application/po/options.hpp>
#include <morpheus/core/conformance/print.hpp>
#include <morpheus/gfx/platform/macos/monitor.hpp>
#include <morpheus/gfx/platform/macos/render_window.hpp>

#include <iostream>

using namespace morpheus;
using namespace morpheus::application::po;
using namespace morpheus::gfx::macos;

int main(int argc, char const* argv[])
{
    RenderWindow::Config config;

    if (auto const result = parseProgramOptions(argc, argv, HelpDocumentation{}, config))
    {
        return result.value();
    }

    for (auto const& monitors : enumerateMonitors())
    {
        conf::print::print("Monitor: {}\n", monitors);
        std::cout.flush(); // Ensure it's not buffered
    }

    RenderWindow window(config);
}
