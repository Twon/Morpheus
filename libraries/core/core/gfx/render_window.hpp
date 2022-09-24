#pragma once

#include <core/base/platform.hpp>
#include <core/base/prerequisites.hpp>
#include <core/gfx/render_target.hpp>
#include <string>

namespace morpheus::gfx
{

struct Config
{
    std::string windowName; /// The name of the window.
    std::uint16_t width = 800; /// The width in pixels of the render target.
    std::uint16_t height = 600; /// The height in pixels of the render target.
    std::uint16_t colourDepth = 32; /// The colour depth of the pixels of the render target.
    std::uint16_t startX = 0; /// The starting X position in pixels of the render window.
    std::uint16_t startY = 0; /// The starting Y position in pixels of the render window.
    bool isFullScreen = false; /// Start the window in full screen mode.
};

/*! \class render_window
        A render window is a specialisation of a render target within the native windowing system
        of the target platform.
 */
class MORPHEUSCORE_EXPORT RenderWindow : public RenderTarget  {
public:



   /// \name Life cycle
    ///@{
    /// Constructs a render target with the specified parameters.
    /// \param[in] width
    ///     The configuration the Window.
    RenderWindow(Config const& config = Config{});

    //! Destructor
    virtual ~RenderWindow() override;
    ///@}

//    bool isHidden() const noexcept
//    bool isFocus() const noexcept
//    bool isFullScreen() const noexcept
//    bool isVisible() const noexcept

//    void isHidden(bool const hidden) const noexcept
//    void isFocus(bool const focus) const noexcept
//    void isVisible(bool const visible) const noexcept

private:
    const std::uint32_t mStartX = 0;
    const std::uint32_t mStartY = 0;
    const std::string mWindowName;
};

} // namespace morpheus::gfx
