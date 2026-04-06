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
        .iLayerType = PFD_MAIN_PLANE};
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

Window::Window(gfx::win32::RenderWindow&& window, Context&& context) noexcept
    : gfx::win32::RenderWindow(std::move(window))
    , mGLContext(std::move(context))
{}

auto Window::create(Config const& config = Config{}) -> conf::exp::expected<Window, std::string>
{
    auto const createContext = [&](auto window) -> conf::exp::expected<std::tuple<RenderWindow, Context>, std::string>
    {
        auto context = Context::create(window.getHandle(), calculatePixedlFormatDescriptor(config));
        if (!context)
            return conf::exp::unexpected(std::move(context).error());
        return std::tuple{std::move(window), std::move(context).value()};
    };

    auto windowAndContext = gfx::win32::RenderWindow::create(config).and_then(createContext);
    if (!windowAndContext)
    {
        return conf::exp::unexpected(std::move(windowAndContext).error());
    }
    auto&& [window, context] = std::move(windowAndContext).value();
    Window thisWindow(std::move(window), std::move(context));
    return thisWindow;
}

} // namespace morpheus::gfx::gl4::wgl
