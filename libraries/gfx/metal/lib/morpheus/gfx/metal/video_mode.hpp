#pragma once

#include <compare>
#include <cstdint>

namespace morpheus::gfx
{

/*! \class VideoMode
        A video mode describes a mode of available settings for an graphics adapter.
 */
class VideoMode
{
public:
    /// \name Life cycle
    ///@{
    /*! Constructs a video mode with the specified parameters.
        \param[in] width
             The width in pixels of the video mode.
        \param[in] height
             The height in pixels of the video mode.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    VideoMode(std::uint32_t const width, std::uint32_t const height, std::uint32_t const colourDepth, std::uint32_t const refreshRate);
    ///@}

    //! The width in pixels of the render target.
    std::uint16_t width() const noexcept { return mWidth; }

    //! The height in pixels of the render target.
    std::uint16_t height() const noexcept { return mHeight; }

    //! The colour depth of the pixels of the render target.
    std::uint16_t colour_depth() const noexcept { return mColourDepth; }

    //! The colour depth of the pixels of the render target.
    std::uint16_t refresh_rate() const noexcept { return mRefreshRate; }

#if defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)
    /// The three-way operator provides strong ordering of types.
    [[nodiscard]] constexpr auto operator<=>(VideoMode const& rhs) const noexcept -> std::strong_ordering = default;
#else
    /// Compare two adapter objects.
    [[nodiscard]] auto operator<=>(VideoMode const& rhs) const noexcept
    {
        return std::tie(mWidth, mHeight, mColourDepth, mRefreshRate) <=> std::tie(rhs.mWidth, rhs.mHeight, rhs.mColourDepth, rhs.mRefreshRate);
    }

    [[nodiscard]] bool operator==(VideoMode const& rhs) const noexcept
    {
        return std::tie(mWidth, mHeight, mColourDepth, mRefreshRate) == std::tie(rhs.mWidth, rhs.mHeight, rhs.mColourDepth, rhs.mRefreshRate);
    }
#endif

private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the video mode.
    std::uint16_t const mWidth = 0;
    //! The height in pixels of the video mode.
    std::uint16_t const mHeight = 0;
    //! The colour depth of the pixels of the video mode.
    std::uint16_t const mColourDepth = 0;
    //! The refresh rate of the video mode.
    std::uint16_t const mRefreshRate = 0;
    ///@}
};

} // namespace morpheus::gfx
