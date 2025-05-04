
#include <morpheus/gfx/platform/macos/monitor.h>

#include <CoreGraphics/CoreGraphics.h>
#include <vector>

namespace morpheus::gfx::macos
{

concurrency::Generator<Monitor> enumerateMonitors() noexcept
{
    uint32_t displayCount = 0;
    CGGetActiveDisplayList(0, nullptr, &displayCount);
    std::vector<CGDirectDisplayID> displays(displayCount);
    CGGetActiveDisplayList(displayCount, displays.data(), &displayCount);

    for (const auto& id : displays) {
        CGRect bounds = CGDisplayBounds(id);
        const bool isPrimary = CGDisplayIsMain(id);

        co_yield Monitor{
            "Display " + std::to_string(id),
            static_cast<Monitor::PixelDiff>(bounds.origin.x),
            static_cast<Monitor::PixelDiff>(bounds.origin.y),
            static_cast<Monitor::Pixels>(bounds.size.width),
            static_cast<Monitor::Pixels>(bounds.size.height),
            isPrimary
        };
    }
}

} // namespace morpheus::gfx::macos
