#pragma once

#include <core/platform.hpp>

#include <compare>

namespace morpheus::gfx
{

/*! \class video_mode
        A video mode describes a mode of available settings for an graphics adapter.
 */
class MORPHEUSCORE_EXPORT VideoMode {
public:
    /// \name Life cycle
    ///@{
    constexpr VideoMode() noexcept = default;

    /*! Constructs a video mode with the specified parameters.
        \param[in] width
             The width in pixels of the video mode.
        \param[in] height
             The height in pixels of the video mode.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    constexpr VideoMode(
        const std::uint16_t width,
        const std::uint16_t height,
        const std::uint16_t colourDepth,
        const std::uint16_t refreshRate
    );
    ///@}


    //! The width in pixels of the render target.
    [[nodiscard]] constexpr auto width() const noexcept { return mWidth; }

    //! The height in pixels of the render target.
    [[nodiscard]] constexpr auto height() const noexcept { return mHeight; }

    //! The colour depth of the pixels of the render target.
    [[nodiscard]] constexpr auto colour_depth() const noexcept { return mColourDepth; }

    //! The colour depth of the pixels of the render target.
    [[nodiscard]] constexpr auto refresh_rate() const noexcept { return mRefreshRate; }

    [[nodiscard]] constexpr auto operator<=>(VideoMode const& rhs) const noexcept = default;
private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the video mode.
    std::uint16_t mWidth = 0;
    //! The height in pixels of the video mode.
    std::uint16_t mHeight = 0;
    //! The colour depth of the pixels of the video mode.
    std::uint16_t mColourDepth = 0;
    //! The refresh rate of the video mode.
    std::uint16_t mRefreshRate = 0;
    ///@}
};

} // namespace morpheus::gfx
