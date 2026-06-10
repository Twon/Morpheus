#pragma once

#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>

#include <wil/resource.h>

#include <optional>
#include <string>

namespace morpheus::gfx::gl4::wgl
{

/// \class RenderWindow
///     A specialisation of the render window for the Windows platform based on the Win32 API.
class RenderWindow
{
public:
    using WindowHandle = HWND;
    using Config = gfx::win32::RenderWindow::Config;

    explicit RenderWindow(RenderWindow const&) = delete;
    RenderWindow& operator=(RenderWindow const&) = delete;

    explicit RenderWindow(RenderWindow&&) noexcept;
    RenderWindow& operator=(RenderWindow&&) noexcept;

    ~RenderWindow() = default;

    /// Creates a render window or returns an error if creation failed.
    /// \param[in] config
    ///     The setting to configure the window with.
    /// \return
    ///     An expected of the newly created window, or an error if creation failed.
    static auto create(Config const& config = Config{}) -> conf::exp::expected<RenderWindow, std::string>;

    // static auto create(WindowHandle handle) -> conf::exp::expected<RenderWindow, std::string>;

    /// \copydoc gfx::RenderTarget::width()
    [[nodiscard]] auto width() const noexcept -> std::uint16_t { return mWindow.width(); }

    /// \copydoc gfx::RenderTarget::height()
    [[nodiscard]] auto height() const noexcept -> std::uint16_t { return mWindow.height(); }

    /// \copydoc gfx::RenderTarget::colourDepth()
    [[nodiscard]] auto colourDepth() const noexcept -> std::uint16_t { return mWindow.colourDepth(); }

    /// \copydoc gfx::RenderWindow::refreshRate()
    [[nodiscard]] auto refreshRate() const noexcept -> std::uint16_t { return mWindow.refreshRate(); }

private:
    RenderWindow() = default;

    gfx::win32::RenderWindow mWindow;
    Context mContext;
};

} // namespace morpheus::gfx::gl4::wgl
