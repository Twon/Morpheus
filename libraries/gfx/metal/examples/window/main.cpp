#include <morpheus/application/po/options.hpp>
#include <morpheus/core/conformance/print.hpp>
#include <morpheus/gfx/metal/render_system.hpp>
#include <morpheus/gfx/platform/macos/monitor.hpp>
#include <morpheus/vis/tui.hpp>
#include <morpheus/vis/visualisation.hpp>

#include <iostream>

using namespace morpheus;
using namespace morpheus::application::po;
using namespace morpheus::gfx::macos;

int main(int argc, char const* argv[])
{
    vis::VisualisationConfig visConfig;

    if (auto const result = parseProgramOptions(argc, argv, HelpDocumentation{}, visConfig.windowConfig))
    {
        return result.value();
    }

    auto const configured = vis::Tui::run(visConfig);
    if (!configured)
    {
        conf::print::print("Visualisation configuration cancelled by user.\n");
        return 0;
    }

    for (auto const& monitors : enumerateMonitors())
    {
        conf::print::print("Monitor: {}\n", monitors);
        std::cout.flush(); // Ensure it's not buffered
    }

    conf::print::print("Setting up Visualisation with {} render system...\n", configured->renderSystemName);
    conf::print::print("Configured Window: '{}' ({}x{}) @ ({}, {})\n",
                       configured->windowConfig.windowName,
                       configured->windowConfig.width,
                       configured->windowConfig.height,
                       configured->windowConfig.startX,
                       configured->windowConfig.startY);
    std::cout.flush();

    auto const visualisation = vis::Visualisation<gfx::metal::RenderSystem>::create(gfx::metal::RenderSystem{}, configured->windowConfig);

    if (!visualisation)
    {
        conf::print::print("Failed to initialize visualisation: {}\n", visualisation.error());
        return 1;
    }
}
