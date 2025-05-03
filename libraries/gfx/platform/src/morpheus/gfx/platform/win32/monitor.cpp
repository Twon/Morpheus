
#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/win32/monitor.hpp>

#include <vector>

namespace morpheus::gfx::win32
{

BOOL CALLBACK MonitorEnumProc(HMONITOR hMon, HDC, LPRECT, LPARAM lParam) {
    std::vector<Monitor>* monitors = reinterpret_cast<std::vector<Monitor>*>(lParam);
    MONITORINFOEX info{};
    info.cbSize = sizeof(info);
    if (GetMonitorInfo(hMon, &info)) {
        monitors->emplace_back(Monitor{
            .name = info.szDevice,
            .x = info.rcMonitor.left,
            .y = info.rcMonitor.top,
            .width = info.rcMonitor.right - info.rcMonitor.left,
            .height = info.rcMonitor.bottom - info.rcMonitor.top,
            .isPrimary = (info.dwFlags & MONITORINFOF_PRIMARY) != 0
        });
    }
    return TRUE;
}

concurrency::Generator<Monitor> enumerateMonitors() noexcept
{
    std::vector<Monitor> result;
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, reinterpret_cast<LPARAM>(&result));
    for (const auto& monitor : result) {
        co_yield monitor;
    }
}

} // namespace morpheus::gfx::win32
