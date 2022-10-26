#pragma once

#include <morpheus/gfx/platform/render_window.hpp>
#include <morpheus/core/base/prerequisites.hpp>

#include <wil/resource.h>
#include <string>

namespace morpheus::gfx::win32
{

/*! \class render_window
        A specialisation of the render window for the Windows platform based on the Win32 API.
 */
class MORPHEUSCORE_EXPORT RenderWindow : protected gfx::RenderWindow {
public:
    using Config = gfx::RenderWindow::Config;

    RenderWindow(Config const config = Config{});
    ~RenderWindow();

    //    bool isHidden() const noexcept
    //    bool isFocus() const noexcept
    bool isFullScreen() const noexcept { return gfx::RenderWindow::isFullScreen(); }
    //    bool isVisible() const noexcept

    //    void isHidden(bool const hidden) const noexcept
    //    void isFocus(bool const focus) const noexcept
    //    void isVisible(bool const visible) const noexcept

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    void resize();

    wil::unique_hwnd mWindow;/// OS window handle
    std::string mWindowName;
};

} // namespace morpheus::gfx::win32
