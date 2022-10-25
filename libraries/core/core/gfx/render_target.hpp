#pragma once

#include <core/base/platform.hpp>

namespace morpheus::gfx
{

/*! \class render_target
        A render target defined a canvas onto which a render system can draw to.
 */
class MORPHEUSCORE_EXPORT RenderTarget {
public:

    /// \name Life cycle
    ///@{
    /*! Constructs a render target with the specified parameters.
        \param[in] width
             The width in pixels of the render target.
        \param[in] height
             The height in pixels of the render target.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    RenderTarget(
        std::uint16_t const width,
        std::uint16_t const height,
        std::uint16_t const colourDepth
    );
    ///@}



    //! The width in pixels of the render target.
    [[nodiscard]] std::uint16_t width() const noexcept { return mWidth; }

    //! The height in pixels of the render target.
    [[nodiscard]] std::uint16_t height() const noexcept { return mHeight; }

    //! The colour depth of the pixels of the render target.
    [[nodiscard]] std::uint16_t colourDepth() const noexcept { return mColourDepth; }

protected:
    /// \name Data Members
    ///@{
    //! The width in pixels of the render target.
    std::uint16_t mWidth = 0;
    //! The height in pixels of the render target.
    std::uint16_t mHeight = 0;
    //! The colour depth of the pixels of the render target.
    std::uint16_t mColourDepth = 0;
    ///@}
};

} // namespace morpheus::gfx
