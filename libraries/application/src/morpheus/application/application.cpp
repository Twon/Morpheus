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

}

Application::Application()
{
    std::set_terminate(terminationHandler);
}

std::string getDefaultApplicationLogName()
{
    using namespace date_ns;
    auto const programName = boost::dll::program_location().stem().string();
    auto const processId = boost::this_process::get_id();
    auto const now = std::chrono::time_point{ std::chrono::system_clock::now() };
    auto const ymd = year_month_day{ floor<days>(now) };
//    auto const result = fmt_ns::format("{}{}{}-{}-{}", ymd.year(), ymd.month(), ymd.day(), programName, processId);
 //   auto const year = fmt_ns::format("{}", ymd.year());
//    auto const year = fmt_ns::format("{:%Y}", ymd.year());
    /*    auto const month = fmt_ns::format("{:%m}", ymd.month());
        auto const day = fmt_ns::format("{:%d}", ymd.day());
        auto const monthDay = fmt_ns::format("{:%m}{:%d}", ymd.month(), ymd.day());
        auto const yeahMonth = fmt_ns::format("{:%Y}{:%m}", ymd.year(), ymd.month());
        auto const yeahMonthDay = fmt_ns::format("{:%Y}{:%m}{:%d}", ymd.year(), ymd.month(), ymd.day());
        auto const result = fmt_ns::format("{:%Y}{:%m}{:%d}", ymd.year(), ymd.month(), ymd.day());
        auto const date = fmt_ns::format("{:%m%d}", ymd);
    //    return result;
    //    auto const localTime = date_ns::zoned_time{ date_ns::current_zone(), system_clock::now() };
    //    return fmt_ns::format("{}_{}_{}", programName, processId, localTime);*/
    auto const logfileName = fmt_ns::format("{}.{}.{}.log", programName, processId, ymd);
    return logfileName;
    // return fmt_ns::format("{}.{}.{:%Y}{:%m}{:%d}.log", programName, processId, ymd.year(), ymd.month(), ymd.day());
    //  return {};
}

// auto format = getDefaultApplicationLogName();

} // namespace morpheus::application
