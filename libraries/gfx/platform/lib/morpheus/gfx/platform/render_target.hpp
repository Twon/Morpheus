#pragma once

#include <cstdint>

namespace morpheus::gfx
{

/// \class RenderTarget
///     A render target defined a canvas onto which a render system can draw to.
///
class RenderTarget
{
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
    explicit RenderTarget(std::uint16_t const width, std::uint16_t const height, std::uint16_t const colourDepth);
    ///@}

    //! The width in pixels of the render target.
    [[nodiscard]] auto width() const noexcept -> std::uint16_t { return mWidth; }

    //! The height in pixels of the render target.
    [[nodiscard]] auto height() const noexcept -> std::uint16_t { return mHeight; }

    //! The colour depth of the pixels of the render target.
    [[nodiscard]] auto colourDepth() const noexcept -> std::uint16_t { return mColourDepth; }

protected:
    /// \name Data Members
    ///@{

    /// The width in pixels of the render target.
    std::uint16_t mWidth = 0;
    /// The height in pixels of the render target.
    std::uint16_t mHeight = 0;
    /// The colour depth of the pixels of the render target.
    std::uint16_t mColourDepth = 0;

    ///@}
};

} // namespace morpheus::gfx
