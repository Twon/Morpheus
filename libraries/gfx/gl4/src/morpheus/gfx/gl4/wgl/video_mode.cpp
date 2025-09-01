#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/gl4/wgl/video_mode.hpp>

namespace morpheus::gfx::gl4::wgl
{

concurrency::Generator<VideoMode> enumerateVideoModes(Adapter const& adapter)
{
    auto devMode = DEVMODE{.dmSize = sizeof(DEVMODE)};

    // This is a loop with an early loop exit point, hence no condition for the loop
    for (DWORD dwCurrentSetting = 0; /* NO CONDITION */; ++dwCurrentSetting)
    {
        // Break out of the loop it there is no more video modes to enumerate
        if (!EnumDisplaySettings(adapter.id().c_str(), dwCurrentSetting, &devMode))
        {
            break;
        }

        // Only add the video mode if it is 16 or 32 bit colour
        if ((16 != devMode.dmBitsPerPel) && (32 != devMode.dmBitsPerPel))
        {
            continue;
        }

        co_yield VideoMode(static_cast<std::uint16_t>(devMode.dmPelsWidth),
                           static_cast<std::uint16_t>(devMode.dmPelsHeight),
                           static_cast<std::uint16_t>(devMode.dmBitsPerPel),
                           static_cast<std::uint16_t>(devMode.dmDisplayFrequency) /*,
                            ((32 == DevMode.dmBitsPerPel) ? PF_X8R8G8B8 : PF_R5G6B5)*/
        );
    }
}

} // namespace morpheus::gfx::gl4::wgl
