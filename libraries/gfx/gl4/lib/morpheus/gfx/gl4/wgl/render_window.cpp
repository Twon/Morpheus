#include <morpheus/gfx/gl4/wgl/render_window.hpp>

namespace morpheus::gfx::gl4::wgl
{

auto RenderWindow::create(Config const& config) -> conf::exp::expected<RenderWindow, std::string>
{
    RenderWindow thisWindow;

    // auto const moveInWindow = [&thisWindow](auto&& window){ thisWindow.mWindow = std::move(window); };
    auto const createOpenGLContext = [](auto&& window)
    {
        ::PIXELFORMATDESCRIPTOR pxlFmtDescriptor{.nSize = sizeof(PIXELFORMATDESCRIPTOR),
                                                 .nVersion = 1,
                                                 .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED,
                                                 .iPixelType = PFD_TYPE_RGBA,
                                                 .cColorBits = 24,
                                                 .cAlphaBits = 8,
                                                 .cDepthBits = 24,
                                                 .cStencilBits = 8,
                                                 .iLayerType = PFD_MAIN_PLANE};
        return Context::create(window.getHandle(), pxlFmtDescriptor);
    };
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
