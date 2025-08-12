#pragma once

#include <dxgi1_6.h>
#include <vector>

namespace morpheus::gfx::d3d12
{
class adapter;

/*! \class video_mode_list
        Defines all of the available video modes for an graphics adapter selected for a graphics API.
 */
class video_mode_list
{
public:
    /// \name Life cycle
    ///@{
    /*! Constructs a render target with the specified parameters.
        \param[in] displayModes
             The enumerated display modes for this parent adapter.
     */
    video_mode_list(std::vector<DXGI_MODE_DESC> const& displayModes);
    ///@}

    //! The width in pixels of the render target.
    //    std::uint32_t width() const noexcept { return mWidth; }

    //! The height in pixels of the render target.
    //    std::uint32_t height() const noexcept { return mHeight; }

    //! The colour depth of the pixels of the render target.
    //    std::uint32_t colout_depth() const noexcept { return mColourDepth; }

private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the render target.
    //    const std::uint32_t mWidth = 0;
    //! The height in pixels of the render target.
    //    const std::uint32_t mHeight = 0;
    //! The colour depth of the pixels of the render target.
    //    const std::uint32_t mColourDepth = 0;
    ///@}
};

} // namespace morpheus::gfx::d3d12
