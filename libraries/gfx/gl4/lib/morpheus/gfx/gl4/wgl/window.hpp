#pragma once

#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>

namespace morpheus::gfx::gl4::wgl
{

/// \class Window
///
class Window : public gfx::win32::RenderWindow
{
public:
    using Config = WindowConfig;

    explicit Window(Config const& config = {});
    explicit Window(HWND const window);

    Window(Window const&) = delete;
    Window& operator=(Window const&) = delete;

    /// Creates a render window or returns an error if creation failed.
    /// \param[in] config
    ///     The setting to configure the window with.
    /// \return
    ///     An expected of the newly created window, or an error if creation failed.
    static conf::exp::expected<Window, std::string> create(Config const& config = Config{});

private:
    Window() = default;
    Window(gfx::win32::RenderWindow&& window, Context&& config) noexcept;

    Context mGLContext;
};

} // namespace morpheus::gfx::gl4::wgl
