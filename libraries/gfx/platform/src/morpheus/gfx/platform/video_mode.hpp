#pragma once

#include <morpheus/core/base/platform.hpp>

#include <compare>
#include <cstdint>

namespace morpheus::gfx
{

/// \class VideoMode
///     A video mode describes a mode of available settings for an graphics adapter.
///
class VideoMode {
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
        \param[in] refreshRate
             The refresh rate of the video mode.
     */
    constexpr VideoMode(
        std::uint16_t const width,
        std::uint16_t const height,
        std::uint16_t const colourDepth,
        std::uint16_t const refreshRate
    ) noexcept
    :   mWidth(width),
        mHeight(height),
        mColourDepth(colourDepth),
        mRefreshRate(refreshRate)
    {
    }
    ///@}


    /// The width in pixels of the render target.
    [[nodiscard]] constexpr auto width() const noexcept { return mWidth; }

    /// The height in pixels of the render target.
    [[nodiscard]] constexpr auto height() const noexcept { return mHeight; }

    /// The colour depth of the pixels of the render target.
    [[nodiscard]] constexpr auto colourDepth() const noexcept { return mColourDepth; }

    /// The colour depth of the pixels of the render target.
    [[nodiscard]] constexpr auto refreshRate() const noexcept { return mRefreshRate; }

    /// The three-way operator provides strong ordering of types.
    [[nodiscard]] constexpr auto operator<=>(VideoMode const& rhs) const noexcept = default;
private:
    /// \name Data Members
    ///@{
    /// The width in pixels of the video mode.
    std::uint16_t mWidth = 0;
    /// The height in pixels of the video mode.
    std::uint16_t mHeight = 0;
    /// The colour depth of the pixels of the video mode.
    std::uint16_t mColourDepth = 0;
    /// The refresh rate of the video mode.
    std::uint16_t mRefreshRate = 0;
    ///@}
};

} // namespace morpheus::gfx
