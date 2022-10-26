#pragma once

#include <morpheus/gfx/platform/render_window.hpp>
#include <morpheus/core/base/prerequisites.hpp>

namespace morpheus::gfx::win32
{

/*! \class render_window
        A specialisation of the render window for the Windows platform based on the Win32 API.
 */
class RenderWindow : private gfx::RenderWindow {
public:
    using Config = gfx::Config;

    RenderWindow(Config const config = Config{});
    ~RenderWindow();

private:
    HWND mWindow; /// OS window handle
};

} // namespace morpheus::gfx::win32
