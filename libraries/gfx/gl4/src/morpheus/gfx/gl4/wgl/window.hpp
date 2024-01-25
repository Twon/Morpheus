#pragma once

#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>

namespace morpheus::gfx::gl4::wgl
{

/// \class Window
///
class Window : protected gfx::win32::RenderWindow
{
public:
    using Config = WindowConfig;

    explicit Window(Config const& config = {});
    explicit Window(HWND const window);

    Window(Window const&) = delete;
    Window& operator=(Window const&) = delete;
private:
    HDC mDeviceContext;
};


} // namespace morpheus::gfx::gl4::wgl
