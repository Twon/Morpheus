#include <morpheus/core/conformance/ranges.hpp>
#include <morpheus/gfx/metal/adapter.hpp>

#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CVDisplayLink.h>
#import <CoreVideo/CoreVideo.h>
#import <Metal/Metal.h>

#include <algorithm>

namespace morpheus::gfx::metal
{

Adapter::Adapter(std::string name, std::uint64_t const id, bool const isLowPower, bool const isRemovable, std::uint64_t const memory)
    : mName(std::move(name))
    , mId(id)
    , mIsLowPower(isLowPower)
    , mIsRemovable(isRemovable)
    , mMemory(memory)
{}

auto Adapter::getVideoModes() const -> std::vector<VideoMode>
{
    std::vector<VideoMode> modes;
    @autoreleasepool
    {
        uint32_t displayCount = 0;
        CGGetActiveDisplayList(0, nullptr, &displayCount);
        if (displayCount > 0)
        {
            std::vector<CGDirectDisplayID> displays(displayCount);
            CGGetActiveDisplayList(displayCount, displays.data(), &displayCount);

            for (auto const displayId : displays)
            {
                CFArrayRef const modeList = CGDisplayCopyAllDisplayModes(displayId, nullptr);
                if (!modeList)
                {
                    continue;
                }
                CFIndex const count = CFArrayGetCount(modeList);
                for (CFIndex i = 0; i < count; ++i)
                {
                    auto const getRefrestRate = [](CGDisplayModeRef mode)
                    {
                        auto const refreshRate = static_cast<std::uint16_t>(CGDisplayModeGetRefreshRate(mode));
                        if (refreshRate == 0)
                        {
                            // GLFW solved this like this: https://github.com/glfw/glfw/issues/137
                            //                            CVTime const time = CVDisplayLinkGetNominalOutputVideoRefreshPeriod(link);
                            //                            if (!(time.flags & kCVTimeIsIndefinite))
                            //                                return static_cast<std::uint16_t>(time.timeScale / (double)time.timeValue);
                            return static_cast<std::uint16_t>(60u);
                        }
                        return refreshRate;
                    };

                    auto mode = static_cast<CGDisplayModeRef>(const_cast<void*>(CFArrayGetValueAtIndex(modeList, i)));
                    auto const width = static_cast<std::uint16_t>(CGDisplayModeGetWidth(mode));
                    auto const height = static_cast<std::uint16_t>(CGDisplayModeGetHeight(mode));
                    auto refreshRate = getRefrestRate(mode);

                    VideoMode const vm{width, height, 32, refreshRate};
                    if (conf::ranges::find(modes, vm) == modes.end())
                    {
                        modes.push_back(vm);
                    }
                }
                CFRelease(modeList);
            }
        }
    }

    conf::ranges::sort(modes);

    return modes;
}

auto enumerateAdapters() -> std::vector<Adapter>
{
    std::vector<Adapter> adapters;
    @autoreleasepool
    {
        NSArray<id<MTLDevice>>* devices = MTLCopyAllDevices();
        if (devices == nil || devices.count == 0)
        {
            id<MTLDevice> defaultDev = MTLCreateSystemDefaultDevice();
            if (defaultDev != nil)
            {
                devices = @[ defaultDev ];
            }
        }

        if (devices != nil)
        {
            for (id<MTLDevice> dev in devices)
            {
                std::string const name = dev.name.length > 0 ? [dev.name UTF8String] : "Unknown Apple Metal Device";
                std::uint64_t const id = dev.registryID;
                bool const isLowPower = dev.isLowPower;
                bool const isRemovable = dev.isRemovable;
                std::uint64_t const mem = dev.recommendedMaxWorkingSetSize;

                adapters.emplace_back(name, id, isLowPower, isRemovable, mem);
            }
        }
    }

    return adapters;
}

} // namespace morpheus::gfx::metal
