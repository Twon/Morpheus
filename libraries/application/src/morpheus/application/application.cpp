#include "morpheus/application/application.hpp"
#include <morpheus/core/conformance/date.hpp>
#include <morpheus/core/conformance/format.hpp>

#include <boost/process/environment.hpp>
#include <boost/dll.hpp>
#include <chrono>

namespace morpheus::application
{

std::string getDefaultApplicationLogName()
{
    using namespace std::chrono;
    auto const programName = boost::dll::program_location().stem().string();
    auto const processId = boost::this_process::get_id();
    auto const now = time_point{ system_clock::now() };
    auto const ymd = year_month_day{ floor<days>(now) };
//    auto const result = fmt_ns::format("{}{}{}-{}-{}", ymd.year(), ymd.month(), ymd.day(), programName, processId);
    auto const year = fmt_ns::format("{:%Y}", ymd.year());
    auto const month = fmt_ns::format("{:%m}", ymd.month());
    auto const day = fmt_ns::format("{:%d}", ymd.day());
    auto const monthDay = fmt_ns::format("{:%m}{:%d}", ymd.month(), ymd.day());
    auto const yeahMonth = fmt_ns::format("{:%Y}{:%m}", ymd.year(), ymd.month());
    auto const yeahMonthDay = fmt_ns::format("{:%Y}{:%m}{:%d}", ymd.year(), ymd.month(), ymd.day());
    auto const result = fmt_ns::format("{:%Y}{:%m}{:%d}", ymd.year(), ymd.month(), ymd.day());
    auto const date = fmt_ns::format("{:%m%d}", ymd);
//    return result;
//    auto const localTime = date_ns::zoned_time{ date_ns::current_zone(), system_clock::now() };
//    return fmt_ns::format("{}_{}_{}", programName, processId, localTime);
//    auto const logfileName = fmt_ns::format("{}.{}.{:%Y}{:%m}{:%d}.log", programName, processId, ymd.year(), ymd.month(), ymd.day());
    auto const logfileName = fmt_ns::format("{}.{}.{}.log", programName, processId, yeahMonthDay);

    return logfileName;
}

} // namespace morpheus::application