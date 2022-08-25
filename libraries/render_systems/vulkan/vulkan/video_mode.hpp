#pragma once

#include <core/base/platform.hpp>

#include <vector>

namespace morpheus::gfx::vulkan
{

/*! \class VideoMode
        A video mode describes a mode of available settings for an graphics adapter.
 */
class VideoMode {
public:
    /*! Constructs a render target with the specified parameters.
        \param[in] width
             The width in pixels of the render target.
        \param[in] height
             The height in pixels of the render target.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    VideoMode() = default;
private:

};

using VideoModeList = std::vector<VideoMode>;

} // namespace morpheus::gfx::vulkan
