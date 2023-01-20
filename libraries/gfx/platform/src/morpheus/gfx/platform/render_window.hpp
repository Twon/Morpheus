#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/render_target.hpp>

#include <boost/program_options/options_description.hpp>
#include <string>

namespace morpheus::gfx
{

/// \struct WindowConfig
///     Configuration structure for windows, will allow for automatic registration of parameter necessary for construction.
struct WindowConfig
{
    std::string windowName = "MorpheusWindow"; /// The name of the window.
    std::uint16_t width = 800; /// The width in pixels of the render target.
    std::uint16_t height = 600; /// The height in pixels of the render target.
    std::uint16_t colourDepth = 32; /// The colour depth of the pixels of the render target.
    std::uint16_t startX = 0; /// The starting X position in pixels of the render window.
    std::uint16_t startY = 0; /// The starting Y position in pixels of the render window.
    bool isFullScreen = false; /// Start the window in full screen mode.

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("window-name", po::value(&windowName)->required(), "The title of the Window.")
            ("width", po::value(&width)->required(), "Width in pixels of the window.")
            ("height", po::value(&height)->required(), "Height in pixels of the window.")
            ("colour-depth", po::value(&colourDepth)->required(), "Colour depth in bits per pixel.")
            ("start-x", po::value(&startX)->default_value(startX), "Starting pixel in the x-dimension for the Window.")
            ("start-y", po::value(&startY)->default_value(startY), "Starting pixel in the y-dimension for the Window.")
            ("full-screen", po::value(&isFullScreen)->default_value(isFullScreen), "Is the window to be started in full screen modde");
        // clang-format on
    }
};

/// \class RenderWindow
///     A render window is a specialisation of a render target within the native windowing system
///     of the target platform.
///
class RenderWindow : protected RenderTarget  {
public:
    using Config = WindowConfig;


    /// \name Life cycle
    ///@{
    /// Constructs a render window with the specified parameters.
    /// \param[in] width
    ///     The configuration the Window.
    RenderWindow(Config const& config = Config{});

    //! Destructor
    ~RenderWindow();
    ///@}

//    bool isHidden() const noexcept
//    bool isFocus() const noexcept

    /// Query if the window full screen.
    bool isFullScreen() const noexcept { return mIsFullScreen; }


    //    bool isVisible() const noexcept

//    void isHidden(bool const hidden) const noexcept
//    void isFocus(bool const focus) const noexcept
//    void isVisible(bool const visible) const noexcept

protected:

    std::uint16_t mStartX = 0; ///< The starting X position in pixels of the render window.
    std::uint16_t mStartY = 0; ///< The starting Y position in pixels of the render window.
    std::string mWindowName; ///< The name of the window.
    bool mIsFullScreen; ///< Start the window in full screen mode.
};

} // namespace morpheus::gfx
