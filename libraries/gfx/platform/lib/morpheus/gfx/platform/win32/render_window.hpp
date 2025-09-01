#pragma once

#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/gfx/platform/render_window.hpp>

#include <wil/resource.h>

#include <optional>
#include <string>
#include <wil/resource.h>

namespace morpheus::gfx::win32
{

/// \class RenderWindow
///     A specialisation of the render window for the Windows platform based on the Win32 API.
class RenderWindow : protected gfx::RenderWindow
{
public:
    using WindowHandle = HWND;
    using Config = gfx::RenderWindow::Config;

    explicit RenderWindow(RenderWindow const&) = delete;
    RenderWindow& operator=(RenderWindow const&) = delete;

    explicit RenderWindow(RenderWindow&&) noexcept;
    RenderWindow& operator=(RenderWindow&&) noexcept;

    ~RenderWindow();

    /// Creates a render window or returns an error if creation failed.
    /// \param[in] config
    ///     The setting to configure the window with.
    /// \return
    ///     An expected of the newly created window, or an error if creation failed.
    static conf::exp::expected<RenderWindow, std::string> create(Config const& config = Config{});

    /// \copydoc gfx::RenderTarget::width()
    [[nodiscard]] std::uint16_t width() const noexcept { return gfx::RenderWindow::width(); }

    /// \copydoc gfx::RenderTarget::height()
    [[nodiscard]] std::uint16_t height() const noexcept { return gfx::RenderWindow::height(); }

    /// \copydoc gfx::RenderTarget::colourDepth()
    [[nodiscard]] std::uint16_t colourDepth() const noexcept { return gfx::RenderWindow::colourDepth(); }

    /// \copydoc gfx::RenderWindow::refreshRate()
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
    RenderWindow() = default;

    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    std::optional<HINSTANCE> mHInstance; /// HInstance of initiating module.
    wil::unique_hwnd mWindow;            /// OS window handle.
};

} // namespace morpheus::gfx::win32
