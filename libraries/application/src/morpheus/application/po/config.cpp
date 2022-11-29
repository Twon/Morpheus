#include "morpheus/application/po/adapters/std/filesystem.hpp"
#include "morpheus/application/po/config.hpp"

#include <boost/program_options/options_description.hpp>

namespace morpheus::application::po
{

void Config::addOptions(boost::program_options::options_description& options)
{
    namespace po = boost::program_options;
    // clang-format off
    options.add_options()
        ("logging-enabled", po::value(&loggingEnabled)->default_value(loggingEnabled), "Logging to file is enabled.")
        ("logfile-path", po::value(&logFilePath)->default_value(std::filesystem::current_path()), "The directory to store logfiles in.");
//        ("logfile-timezone", po::value(&logFileTimeZone)->required(), "Width in pixels of the window.");
//        ("height", po::value(&height)->required(), "Height in pixels of the window.")
//        ("colour-depth", po::value(&colourDepth)->required(), "Colour depth in bits per pixel.")
//        ("start-x", po::value(&startX)->default_value(startX), "Starting pixel in the x-dimension for the Window.")
//        ("start-y", po::value(&startY)->default_value(startY), "Starting pixel in the y-dimension for the Window.")
//        ("full-screen", po::value(&isFullScreen)->default_value(isFullScreen), "Is the window to be started in full screen modde");
    // clang-format on


//    std::filesystem::path logFilePath;
//    date_ns::time_zone logFileTimeZone;

}

} // namespace morpheus::application::po