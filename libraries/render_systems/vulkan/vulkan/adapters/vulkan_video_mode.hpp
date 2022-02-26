#pragma once

#include <core/platform.hpp>

namespace morpheus::gfx::vulkan
{

/*! \class video_mode
        A video mode describes a mode of available settings for an graphics adapter.
 */
class video_mode {
public:
    /*! Constructs a render target with the specified parameters.
        \param[in] width
             The width in pixels of the render target.
        \param[in] height
             The height in pixels of the render target.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    video_mode() = default;
private:

};

} // namespace morpheus::gfx::vulkan
