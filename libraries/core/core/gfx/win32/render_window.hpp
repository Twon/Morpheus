#pragma once

#include <core/base/prerequisites.hpp>
#include <core/gfx/render_window.hpp>

namespace morpheus::gfx::win32
{

/*! \class render_window
        A specialisation of the render window for the Windows platform based on the Win32 API.
 */
class MORPHEUSCORE_EXPORT RenderWindow : private gfx::RenderWindow {
public:
    using Config = gfx::Config;

    RenderWindow(Config const config = Config{});
    ~RenderWindow();

private:
    HWND mWindow; /// OS window handle
};

} // namespace morpheus::gfx::win32
