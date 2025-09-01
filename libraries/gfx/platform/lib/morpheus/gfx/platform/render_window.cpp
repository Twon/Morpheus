#include "morpheus/core/base/prerequisites.hpp"
#include "morpheus/gfx/platform/render_target.hpp"
#include "morpheus/gfx/platform/render_window.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>

namespace morpheus::gfx
{

void WindowConfig::addOptions(boost::program_options::options_description& options)
{
    namespace po = boost::program_options;
    // clang-format off
    options.add_options()
        ("window-name", po::value(&windowName)->required(), "The title of the Window.")
        ("width", po::value(&width)->required(), "Width in pixels of the window.")
        ("height", po::value(&height)->required(), "Height in pixels of the window.")
        ("colour-depth", po::value(&colourDepth)->required(), "Colour depth in bits per pixel.")
        ("start-x", po::value(&startX)->default_value(startX), "Starting pixel in the x-dimension for the Window.")
        ("start-y", po::value(&startY)->default_value(startY), "Starting pixel in the y-dimension for the Window.")
        ("full-screen", po::value(&fullScreen)->default_value(fullScreen), "Is the window to be started in full screen mode")
        ("visible", po::value(&visible)->default_value(visible), "Is the window initially visible");
    // clang-format on
}

//---------------------------------------------------------------------------------------------------------------------

RenderWindow::RenderWindow(Config const& config)
    : RenderTarget(config.width, config.height, config.colourDepth)
    , mStartX(config.startX)
    , mStartY(config.startY)
    , mWindowName(config.windowName)
    , mFullScreen(config.fullScreen)
{}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
