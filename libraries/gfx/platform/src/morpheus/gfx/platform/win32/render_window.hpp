#pragma once

#include <morpheus/gfx/platform/render_window.hpp>
#include <morpheus/core/base/prerequisites.hpp>

#include <wil/resource.h>
#include <string>

namespace morpheus::gfx::win32
{

/*! \class RenderWindow
        A specialisation of the render window for the Windows platform based on the Win32 API.
 */
class RenderWindow : protected gfx::RenderWindow {
public:
    using Config = gfx::RenderWindow::Config;

    explicit RenderWindow(Config const config = Config{});
    explicit RenderWindow(HWND const window);

    explicit RenderWindow(RenderWindow const&) = delete;
    RenderWindow& operator=(RenderWindow const&) = delete;

    explicit RenderWindow(RenderWindow&&) noexcept;
    RenderWindow& operator=(RenderWindow&&) noexcept;

    ~RenderWindow();

    /// \copydoc gfx::RenderTarget::width()
    [[nodiscard]] std::uint16_t width() const noexcept { return gfx::RenderWindow::width(); }

    /// \copydoc gfx::RenderTarget::height()
    [[nodiscard]] std::uint16_t height() const noexcept { return gfx::RenderWindow::height(); }

    /// \copydoc gfx::RenderTarget::colourDepth()
    [[nodiscard]] std::uint16_t colourDepth() const noexcept { return gfx::RenderWindow::colourDepth(); }

    /// \copydoc gfx::RenderTarget::refreshRate()
    [[nodiscard]] std::uint16_t refreshRate() const noexcept { return gfx::RenderWindow::refreshRate(); }

    //    bool isHidden() const noexcept
    //    bool isFocus() const noexcept

    /// \copydoc gfx::RenderWindow::fullScreen()
    [[nodiscard]] bool fullScreen() const noexcept { return gfx::RenderWindow::fullScreen(); }

    [[nodiscard]] bool visible() const noexcept;

    //    void isHidden(bool const hidden) const noexcept
    //    void isFocus(bool const focus) const noexcept
    //    void isVisible(bool const visible) const noexcept

    void resize();

    /// Access the underlying OS Window handle.
    auto getHandle() const noexcept { return mWindow.get(); }

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    wil::unique_hwnd mWindow; /// OS window handle
};

} // namespace morpheus::gfx::win32
