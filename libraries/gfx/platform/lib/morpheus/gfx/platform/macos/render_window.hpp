
#pragma once

#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/render_window.hpp>

#include <string>

namespace morpheus::gfx::macos
{

/*! \class RenderWindow
        A specialisation of the render window for the MacOS platform based on the Cocoa API.
 */
class RenderWindow : protected gfx::RenderWindow
{
public:
    using WindowHandle = void*;
    using Config = gfx::RenderWindow::Config;

    explicit RenderWindow(Config const& config = Config{});
    explicit RenderWindow(WindowHandle const window);

    explicit RenderWindow(RenderWindow const&) = delete;
    RenderWindow& operator=(RenderWindow const&) = delete;

    explicit RenderWindow(RenderWindow&&) noexcept;
    RenderWindow& operator=(RenderWindow&&) noexcept;

    ~RenderWindow();

    //! The width in pixels of the render target.
    [[nodiscard]] std::uint16_t width() const noexcept { return gfx::RenderTarget::width(); }

    //! The height in pixels of the render target.
    [[nodiscard]] std::uint16_t height() const noexcept { return gfx::RenderTarget::height(); }

    //! The colour depth of the pixels of the render target.
    [[nodiscard]] std::uint16_t colourDepth() const noexcept { return gfx::RenderTarget::colourDepth(); }

    //    bool isHidden() const noexcept
    //    bool isFocus() const noexcept

    /// \copydoc gfx::RenderWindow::fullScreen()
    [[nodiscard]] bool fullScreen() const noexcept { return gfx::RenderWindow::fullScreen(); }

    [[nodiscard]] bool visible() const noexcept;

    /// Does the window have focus?
    [[nodiscard]] bool hasFocus() const;

    //    void isHidden(bool const hidden) const noexcept
    //    void isFocus(bool const focus) const noexcept
    //    void isVisible(bool const visible) const noexcept

    void show();

    void resize();

    /// Access the underlying OS Window handle.
    auto getHandle() const noexcept { return mHandle; }

private:
    WindowHandle mHandle;

    // Should we use a Windows controller subclass to enable unit testing?
    // https://eschatologist.net/blog/?p=10
};

} // namespace morpheus::gfx::macos
