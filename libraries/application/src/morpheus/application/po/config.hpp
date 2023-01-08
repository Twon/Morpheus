#pragma once

#include "morpheus/core/conformance/date.hpp"

#include <boost/log/trivial.hpp>
#include <filesystem>

namespace boost::program_options
{
    class options_description;
}

namespace morpheus::application::po
{

/// \struct Config
///     Standard appication program options
struct Config
{
    bool loggingEnabled = true;
    bool logAppend = true;
    boost::log::trivial::severity_level logLevel = boost::log::trivial::severity_level::info; /// The default level of log messages to allow into the log.
    std::filesystem::path logFilePath; // Name auto generated as "<processname>_<process_id>_<timestamp>".log if only a folder is given 
//    date_ns::time_zone loggingTimeZone;
//    std::uint32_t logFileRollOverSize; // Maximum size at which the log file roles over to a new logfile.


    // Logfile name
    // Logfile timezone
    void addOptions(boost::program_options::options_description& options);
};

} // namespace morpheus::application::po