#pragma once

#include "morpheus/core/base/prerequisites.hpp"
#include "morpheus/gfx/platform/render_target.hpp"

#include <cstdint>
#include <string>

namespace boost::program_options
{
class options_description;
}

namespace morpheus::gfx
{

/// \struct WindowConfig
///     Configuration structure for windows, will allow for automatic registration of parameter necessary for construction.
struct WindowConfig
{
    std::string windowName = "MorpheusWindow"; /// The name of the window.
    std::uint16_t width = 800;                 /// The width in pixels of the render target.
    std::uint16_t height = 600;                /// The height in pixels of the render target.
    std::uint16_t colourDepth = 32;            /// The colour depth of the pixels of the render target.
    std::uint16_t startX = 0;                  /// The starting X position in pixels of the render window.
    std::uint16_t startY = 0;                  /// The starting Y position in pixels of the render window.
    bool fullScreen = false;                   /// Start the window in full screen mode.
    bool visible = true;                       /// Should the window initially be visible.

    void addOptions(boost::program_options::options_description& options);
};

/// \class RenderWindow
///     A render window is a specialisation of a render target within the native windowing system
///     of the target platform.
///
class RenderWindow : protected RenderTarget
{
public:
    using Config = WindowConfig;

    /// \name Life cycle
    ///@{
    /// Constructs a render window with the specified parameters.
    /// \param[in] config
    ///     The configuration the Window.
    explicit RenderWindow(Config const& config = Config{});
    ///@}

    [[nodiscard]] auto const& name() const noexcept { return mWindowName; }

    //! The width in pixels of the render window.
    [[nodiscard]] std::uint16_t width() const noexcept { return RenderTarget::width(); }

    //! The height in pixels of the render window.
    [[nodiscard]] std::uint16_t height() const noexcept { return RenderTarget::height(); }

    //! The colour depth of the pixels of the render window.
    [[nodiscard]] std::uint16_t colourDepth() const noexcept { return RenderTarget::colourDepth(); }

    //! The location of the start pixel in the X-coordinate screen space of the render window.
    [[nodiscard]] std::uint16_t startX() const noexcept { return mStartX; }

    //! The location of the start pixel in the Y-coordinate screen space of the render window.
    [[nodiscard]] std::uint16_t startY() const noexcept { return mStartY; }

    //    bool isHidden() const noexcept
    //    bool isFocus() const noexcept

    /// Query if the window full screen.
    [[nodiscard]] bool fullScreen() const noexcept { return mFullScreen; }

    /// Query if the window refresh rate in Htz.
    [[nodiscard]] std::uint16_t refreshRate() const noexcept { return mRefreshRate; }

    /// Queries if the window is visible;
    //    bool isVisible() const noexcept

    //    void isHidden(bool const hidden) const noexcept
    //    void isFocus(bool const focus) const noexcept
    //    void isVisible(bool const visible) const noexcept

protected:
    std::uint16_t mStartX = 0;      ///< The starting X position in pixels of the render window.
    std::uint16_t mStartY = 0;      ///< The starting Y position in pixels of the render window.
    std::uint16_t mRefreshRate = 0; ///< The refresh rate of the render window.
    std::string mWindowName;        ///< The name of the window.
    bool mFullScreen;               ///< Start the window in full screen mode.
};

} // namespace morpheus::gfx
