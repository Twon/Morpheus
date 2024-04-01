#pragma once

#include <morpheus/gfx/platform/render_target.hpp>
#include <string>

namespace morpheus::gfx
{

/*! \enum pixel_format

 */
enum class pixel_format : std::int32_t
{
    UNKNOWN,
//    VK_FORMAT_R8_UNORM

    //! Specifies a one-component, 8-bit signed integer format that has a 8-byte red channel.
    R8_SINT,

    //! Specifies a one-component, 8-bit unsigned integer format that has a 8-byte red channel.
    R8_UINT,

    //! Specifies a one-component, 8-bit signed normalised format that has a 8-byte red channel.
    R8_SNORM,

    //! Specifies a one-component, 8-bit unsigned normalised format that has a 8-byte red channel.
    R8_UNORM,

 //     DXGI_FORMAT_R8_TYPELESS,
 // DXGI_FORMAT_R8_UNORM,
 // DXGI_FORMAT_R8_UINT,
 // DXGI_FORMAT_R8_SNORM,
 // DXGI_FORMAT_R8_SINT,

    /// 8-bit luminance only.
    L8,

    /// 16-bit luminance only.
    L16,

    /// 8-bit alpha only.
    A8,

    /// 8-bit using 4 bits each for alpha and luminance.
    A4L4,

    /// 16-bit using 8 bits each for alpha and luminance.
    A8L8,

    /// 8-bit pixel using 2 bits red, 3 bits green, 3 bits blue
    R3G3B2,

    /// 16-bit pixel using 5 bits red, 6 bits green, 5 bits blue
    R5G6B5,

    /// 16-bit pixel using 5 bits blue, 6 bits green, 5 bits red
    B5G6R5,

    /// 16-bit pixel using 5 bits for blue, green, red and 1 for alpha.
    A1R5G5B5,

    /// 16-bit pixel using 4 bits for alpha, red, green and blue.
    A4R4G4B4,

    /// 24-bit pixel using 8 bits for red, green and blue.
    R8G8B8,

    /// 24-bit pixel using 8 bits for blue, green and red.
    B8G8R8,

    /// 32-bit pixel using 8 bits for alpha, red, green and blue.
    A8R8G8B8,

    /// 32-bit pixel using 8 bits for blue, green, red and alpha.
    A8B8G8R8,

    /// 32-bit pixel using 8 bits for red, green, blue and alpha.
    R8G8B8A8,

    /// 32-bit pixel using 8 bits for blue, green, red and alpha.
    B8G8R8A8,

    /// 32-bit pixel using 8 bits for red, 8 bits for green, 8 bits for blue
    /// like PF_A8R8G8B8, but alpha will get discarded
    X8R8G8B8,

    /// 32-bit pixel using 8 bits for blue, 8 bits for green, 8 bits for red
    /// like PF_A8B8G8R8, but alpha will get discarded
    X8B8G8R8,

    /// 32-bit pixel using 2 bits for alpha, 10 bits for red, green and blue.
    A2R10G10B10,

    /// 32-bit pixel using 2 bits for alpha, 10 bits for blue, green and red.
    A2B10G10R10,
};

} // namespace morpheus::gfx
