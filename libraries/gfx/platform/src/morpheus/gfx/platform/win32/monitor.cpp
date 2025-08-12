
#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/win32/monitor.hpp>

#include <vector>

namespace morpheus::gfx::win32
{

BOOL CALLBACK MonitorEnumProc(HMONITOR hMon, HDC, LPRECT, LPARAM lParam)
{
    // LCOV_EXCL_START
    std::vector<Monitor>* monitors = reinterpret_cast<std::vector<Monitor>*>(lParam);
    MONITORINFOEX info{};
    info.cbSize = sizeof(info);
    if (GetMonitorInfo(hMon, &info))
    {
        monitors->emplace_back(Monitor{
            info.szDevice,
            static_cast<Monitor::PixelDiff>(info.rcMonitor.left),
            static_cast<Monitor::PixelDiff>(info.rcMonitor.top),
            static_cast<Monitor::Pixels>(info.rcMonitor.right - info.rcMonitor.left),
            static_cast<Monitor::Pixels>(info.rcMonitor.bottom - info.rcMonitor.top),
            (info.dwFlags & MONITORINFOF_PRIMARY) != 0
        });
    }
    return TRUE;
    // LCOV_EXCL_STOP
}

concurrency::Generator<Monitor> enumerateMonitors() noexcept
{
    // LCOV_EXCL_START
    std::vector<Monitor> result;
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, reinterpret_cast<LPARAM>(&result));
    for (auto const& monitor : result)
    {
        co_yield monitor;
    }
    // LCOV_EXCL_STOP
}

} // namespace morpheus::gfx::win32
