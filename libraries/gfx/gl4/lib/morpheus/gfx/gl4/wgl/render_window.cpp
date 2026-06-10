#include <morpheus/gfx/gl4/wgl/render_window.hpp>

namespace morpheus::gfx::gl4::wgl
{

namespace
{

auto calculatePixedlFormatDescriptor(RenderWindow::Config const& config)
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
        .iLayerType = PFD_MAIN_PLANE};
    return pxlFmtDescriptor;
}

} // namespace

auto RenderWindow::create(Config const& config) -> conf::exp::expected<RenderWindow, std::string>
{
    RenderWindow thisWindow;

    auto const createOpenGLContext = [&config](auto&& window) { return Context::create(window.getHandle(), calculatePixedlFormatDescriptor(config)); };
    auto parent = gfx::win32::RenderWindow::create(config).and_then(createOpenGLContext);

    // if (!parent)
    //     return conf::exp::unexpected(parent.error());
    // else

    // auto context = Context::create(thisWindow.mWindow.getHandle(), pxlFmtDescriptor);
    // if (!context)
    //     return conf::exp::unexpected(context.error());

    return conf::exp::expected<RenderWindow, std::string>{std::move(thisWindow)};
}

} // namespace morpheus::gfx::gl4::wgl
