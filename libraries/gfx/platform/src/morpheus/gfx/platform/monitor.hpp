#pragma once

#include <compare>
#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::gfx
{

/// \class Monitor
///     Describes an available monitor on the system.
///
class Monitor {
public:
    using Pixels = std::uint32_t;
    using PixelDiff = std::int32_t;

    /// \name Life cycle
    ///@{
    /// Default construction an empty adapter.
    explicit Monitor() noexcept = default;

    /// Constructs an adapter from name and id.
    explicit Monitor(
        std::string_view const name,
        Pixels const width,
        Pixels const height,
        PixelDiff const x,
        PixelDiff const y,
        bool const primary = false
    )   noexcept
    :   mName(name)
    ,   mWidth(width)
    ,   mHeight(height)
    ,   mX(x)
    ,   mY(y)
    ,   mPrimary(primary)
    {
    }
    ///@}

    /// Access the adapter name.
    [[nodiscard]] auto const& name() const noexcept { return mName; }

    /// The width in pixels of the render target.
    [[nodiscard]] Pixels width() const noexcept { return mWidth; }

    /// The height in pixels of the render target.
    [[nodiscard]] Pixels height() const noexcept { return mHeight; }

    /// Left origin of the monitor in pixels, relative to the global virtual screen coordinate space.
    [[nodiscard]] PixelDiff x() const noexcept { return mX; }

    /// Top origin of the monitor in pixels, relative to the global virtual screen coordinate space.
    [[nodiscard]] PixelDiff y() const noexcept { return mY; }

    /// Is this the primary monitor?
    [[nodiscard]] bool primary() const noexcept { return mPrimary; }

    /// Compare two adapter objects.
    [[nodiscard]] auto operator<=>(Monitor const& rhs) const noexcept = default;
private:
    /// \name Data Members
    ///@{
    std::string mName; //!< The name of the monitor
    Pixels mWidth = 0; //!< The width in pixels of the screen
    Pixels mHeight = 0; //!< The height in pixels of the screen
    PixelDiff mX = 0; //!< Left origin of the monitor in pixels, relative to the global virtual screen coordinate space.
    PixelDiff mY = 0; //!< Top origin of the monitor in pixels, relative to the global virtual screen coordinate space.
    bool mPrimary = false; //!< Is this the primary monitor?
    ///@}
};

} // namespace morpheus::gfx
