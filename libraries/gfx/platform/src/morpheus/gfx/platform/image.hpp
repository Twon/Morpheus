#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace morpheus::gfx
{

/// \class Image
///     The image abstracts the loading and saving of image files in CPU space.
class Image
{
public:
    /// \name Life cycle
    ///@{

    /// Constructs a render target with the specified parameters.
    /// \param[in] width
    ///      The width in pixels of the render target.
    /// \param[in] height
    ///      The height in pixels of the render target.
    /// \param[in] colourDepth
    ///      The colour depth of the pixels of the render target.
    explicit Image(
        std::uint32_t const width,
        std::uint32_t const height,
        std::uint32_t const colourDepth
    );
    ///@}

    /// The width in pixels of the render target.
    constexpr std::uint32_t width() const noexcept { return mWidth; }

    /// The height in pixels of the render target.
    constexpr std::uint32_t height() const noexcept { return mHeight; }

    /// The colour depth of the pixels of the render target.
    constexpr std::uint32_t colourDepth() const noexcept { return mColourDepth; }

private:
    /// Container for raw image data.
    using ImageData = std::vector<std::byte>;

    /// \name Data Members
    ///@{
    std::uint32_t mWidth = 0;       ///< The width in pixels of the render target.
    std::uint32_t mHeight = 0;      ///< The height in pixels of the render target.
    std::uint32_t mColourDepth = 0; ///< The colour depth of the pixels of the render target.
    ImageData mData;                /// Buffer of raw image data.
    ///@}
};

} // namespace morpheus::gfx
