#include "morpheus/application/po/adapters/boost/log.hpp"      // IWYU pragma: keep
#include "morpheus/application/po/adapters/std/filesystem.hpp" // IWYU pragma: keep
#include "morpheus/application/po/config.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>

namespace morpheus::application::po
{

void Config::addOptions(boost::program_options::options_description& options)
{
    namespace po = boost::program_options;
    // clang-format off
    options.add_options()
        ("logging-enabled", po::value(&loggingEnabled)->default_value(loggingEnabled), "Logging to file is enabled.")
        ("log-append", po::value(&logAppend)->default_value(logAppend), "Logging is appended to an existing log file.")
        ("log-level", po::value(&logLevel)->default_value(logLevel), "The most permissive level of logging to allow into the log file.")
        ("logfile-path", po::value(&logFilePath)->default_value(std::filesystem::current_path()), "The directory to store logfiles in.");
//        ("logfile-timezone", po::value(&logFileTimeZone)->required(), "Width in pixels of the window.");
    // clang-format on

    //    std::filesystem::path logFilePath;
    //    conf::date::time_zone logFileTimeZone;
}

} // namespace morpheus::application::po
