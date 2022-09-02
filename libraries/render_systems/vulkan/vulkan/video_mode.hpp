#pragma once

#include <core/base/platform.hpp>
#include <core/gfx/video_mode.hpp>

#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class VideoMode
        A video mode describes a mode of available settings for an graphics adapter.
 */
/*class VideoMode {
public:
    VideoMode() = default;
private:

};*/

using VideoMode = gfx::VideoMode;

using VideoModeList = std::vector<VideoMode>;

} // namespace morpheus::gfx::vulkan
