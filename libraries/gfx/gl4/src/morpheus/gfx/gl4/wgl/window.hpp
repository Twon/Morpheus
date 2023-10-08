#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace morpheus::gfx::gl4::wgl
{

/// \class Window
///
class Window
{
public:
    Window(HWND const window);

    Window(Window const&) = delete;
    Window& operator=(Window const&) = delete;
private:
    HDC mDeviceContext;
};


} // namespace morpheus::gfx::gl4::wgl
