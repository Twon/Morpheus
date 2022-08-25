#pragma once

#include <core/base/platform.hpp>

namespace morpheus::gfx
{

/*! \class render_target
        A render target defined a canvas onto which a render system can draw to.
 */
class MORPHEUSCORE_EXPORT render_target {
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
    render_target(
        const std::uint32_t width,
        const std::uint32_t height,
        const std::uint32_t colourDepth
    );

    //! Destructor
    virtual ~render_target();
    ///@}



    //! The width in pixels of the render target.
    std::uint32_t width() const noexcept { return mWidth; }

    //! The height in pixels of the render target.
    std::uint32_t height() const noexcept { return mHeight; }

    //! The colour depth of the pixels of the render target.
    std::uint32_t colour_depth() const noexcept { return mColourDepth; }

private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the render target.
    const std::uint32_t mWidth = 0;
    //! The height in pixels of the render target.
    const std::uint32_t mHeight = 0;
    //! The colour depth of the pixels of the render target.
    const std::uint32_t mColourDepth = 0;
    ///@}
};

} // namespace morpheus::gfx
