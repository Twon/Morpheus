#include "morpheus/application/application.hpp"
#include "morpheus/core/base/debugging.hpp"
#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"
#include "morpheus/core/conversion/adapters/std/chrono.hpp"
#include "morpheus/core/conversion/adapters/std/stacktrace.hpp"

#include <boost/process/environment.hpp>
#include <boost/dll.hpp>
#include <chrono>

namespace morpheus::application
{

namespace
{

/// \brief Override the default termination handler to print the call stack before exiting the program to aid debugging.
void terminationHandler()
{
    try{
        debugPrint(fmt_ns::format("{}", MORPHEUS_CURRENT_STACKTRACE));
    }
    catch(...){

    }
    std::abort();
}

/// Standardises all application logs to common log name format of <progam name>-<process id>-<yeah-month-day>.log
/*std::string getDefaultApplicationLogName()
{
    using namespace date_ns;
    auto const programName = boost::dll::program_location().stem().string();
    auto const processId = boost::this_process::get_id();
    auto const now = std::chrono::time_point{ std::chrono::system_clock::now() };
    auto const ymd = year_month_day{floor<days>(now)};
    //    auto const localTime = date_ns::zoned_time{ date_ns::current_zone(), system_clock::now() };
    //    return fmt_ns::format("{}_{}_{}", programName, processId, localTime);
    return fmt_ns::format("{}.{}.{}.log", programName, processId, ymd);
}*/

} // namespace

Application::Application(int argc, char* argv[])
//`: mLogName(getDefaultApplicationLogName())
{
    if (auto invalid = parseProgramOptions(argc, argv, po::HelpDocumentation{}, mConfig)) {
    }

    std::set_terminate(terminationHandler);
}

// auto format = getDefaultApplicationLogName();

} // namespace morpheus::application
