#pragma once

#include <core/gfx/pixel.hpp>
#include <dxgi1_6.h>

namespace morpheus::gfx::d3d12
{

/*! \class types
        Provides helper methods for mapping from native types to the underlying rendering API.
 */
class types {
public:
    /*! Maps between the native pixel format type to the underlying 
        <a href="https://docs.microsoft.com/en-us/windows/desktop/api/dxgiformat/ne-dxgiformat-dxgi_format">Direct X format type</a>.
        \param[in] format
            The native API repesentation of pixel format to map to the underlying hardware API.
        \return
            The underlying hardware pixel format which represents the user requested type in the hardware API.        
     */
    static DXGI_FORMAT map(
        const pixel_format format
    );

    static pixel_format map(
        const DXGI_FORMAT format 
    );

private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the video mode.
//    const std::uint16_t mWidth = 0;
    //! The height in pixels of the video mode.
//    const std::uint16_t mHeight = 0;
    //! The colour depth of the pixels of the video mode.
//    const std::uint16_t mColourDepth = 0;
    //! The refresh rate of the video mode.
//    const std::uint16_t mRefreshRate = 0;
    ///@}
};

} // namespace morpheus::gfx::d3d12
