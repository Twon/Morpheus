
#include <morpheus/gfx/platform/macos/monitor.hpp>

#include <CoreGraphics/CoreGraphics.h>

#include <vector>

namespace morpheus::gfx::macos
{

concurrency::Generator<Monitor> enumerateMonitors() noexcept
{
    // LCOV_EXCL_START
    uint32_t displayCount = 0;
    CGGetActiveDisplayList(0, nullptr, &displayCount);
    std::vector<CGDirectDisplayID> displays(displayCount);
    CGGetActiveDisplayList(displayCount, displays.data(), &displayCount);

    for (auto const& id : displays)
    {
        CGRect bounds = CGDisplayBounds(id);
        bool const isPrimary = CGDisplayIsMain(id);

        co_yield Monitor{"Display " + std::to_string(id),
                         static_cast<Monitor::PixelDiff>(bounds.origin.x),
                         static_cast<Monitor::PixelDiff>(bounds.origin.y),
                         static_cast<Monitor::Pixels>(bounds.size.width),
                         static_cast<Monitor::Pixels>(bounds.size.height),
                         isPrimary};
    }
    // LCOV_EXCL_STOP
}

} // namespace morpheus::gfx::macos
