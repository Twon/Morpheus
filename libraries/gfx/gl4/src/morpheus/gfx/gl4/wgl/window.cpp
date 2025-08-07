#include <morpheus/gfx/gl4/wgl/window.hpp>
#include <stdexcept>

namespace morpheus::gfx::gl4::wgl
{

namespace
{

auto calculatePixedlFormatDescriptor(Window::Config const& config)
{
    ::PIXELFORMATDESCRIPTOR pxlFmtDescriptor{
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = static_cast<BYTE>((config.colourDepth > 16) ? 24 : config.colourDepth), // Allow the user to select colour depth
        .cAlphaBits = static_cast<BYTE>((config.colourDepth > 16) ? 8 : 0),
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE
    };
    return pxlFmtDescriptor;
}

} // namespace

Window::Window(Config const& config)
    : gfx::win32::RenderWindow(config)
    , mGLContext(getHandle(), calculatePixedlFormatDescriptor(config))
{}

Window::Window(HWND const window)
    : gfx::win32::RenderWindow(window)
    , mGLContext(getHandle(), []() { return ::PIXELFORMATDESCRIPTOR{}; }())
{}

} // namespace morpheus::gfx::gl4::wgl
