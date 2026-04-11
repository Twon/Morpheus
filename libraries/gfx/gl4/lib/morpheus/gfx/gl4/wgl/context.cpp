#include <morpheus/core/base/assert.hpp>
#include <morpheus/core/conformance/bit_cast.hpp>
#include <morpheus/core/conformance/format.hpp>
#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/gl4/wgl/verify.hpp>

namespace morpheus::gfx::gl4::wgl
{

namespace
{

template <typename T>
using WGLExpected = conf::exp::expected<T, std::string>;

auto createDC(HWND const window) -> WGLExpected<HDC>
{
    MORPHEUS_ASSERT(window);
    auto const hDC = GetDC(window);
    if (!hDC)
        return conf::exp::unexpected(getLastErrorMessage());
    return hDC;
}

auto choosePixelFormat(HDC const hdc, PIXELFORMATDESCRIPTOR const& pfd) -> WGLExpected<int>
{
    if (auto const format = ChoosePixelFormat(hdc, &pfd); format == 0)
        return conf::exp::unexpected(conf::fmt::format("Failed to choose pixel format: {}", getLastErrorMessage()));
    else
        return format;
}

auto setPixelFormat(HDC hdc, int format) -> WGLExpected<void>
{
    PIXELFORMATDESCRIPTOR pfd;
    if (!DescribePixelFormat(hdc, format, sizeof(pfd), &pfd))
        return conf::exp::unexpected(conf::fmt::format("Failed to describe pixel format: {}", getLastErrorMessage()));

    if (!SetPixelFormat(hdc, format, &pfd))
        return conf::exp::unexpected(conf::fmt::format("Failed to set pixel format: {}", getLastErrorMessage()));
    return {};
}

auto createGLContext(HDC hdc) -> WGLExpected<HGLRC>
{
    if (auto const hglrc = wglCreateContext(hdc); !hglrc)
        return conf::exp::unexpected(conf::fmt::format("Failed to create OpenGL context: {}", getLastErrorMessage()));
    else
        return hglrc;
}

} // namespace

auto Context::create(HWND const window, PIXELFORMATDESCRIPTOR const& pfd) -> Expected
{
    auto const setupPixelFormat = [&pfd](HDC const hdc)
    { return choosePixelFormat(hdc, pfd).and_then([hdc, &pfd](int format) { return setPixelFormat(hdc, format).transform([hdc]() { return hdc; }); }); };

    auto const createContext = [&](HDC const hdc)
    {
        return createGLContext(hdc).transform(
            [window, hdc](HGLRC const hglrc)
            {
                glbinding::initialize(
                    [](char const* name) -> glbinding::ProcAddress { return conf::bit::bit_cast<glbinding::ProcAddress>(wglGetProcAddress(name)); }, true);
                return Context(window, hdc, hglrc);
            });
    };

    return createDC(window).and_then(setupPixelFormat).and_then(createContext);
}

Context::Context(HWND const window, HDC const hdc, HGLRC const hglrc)
    : mOwningWindow(window)
    , mDeviceContext(hdc, {[this]() { MORPHEUS_WGL_VERIFY(ReleaseDC(*mOwningWindow, mDeviceContext.get())); }})
    , mGLContext(hglrc, {[this]() { MORPHEUS_WGL_VERIFY(wglDeleteContext(mGLContext.get())); }})
{}

Context::Context()
    : mDeviceContext(wglGetCurrentDC(), {[]() {}})
    , mGLContext(wglGetCurrentContext(), {[]() {}})
{}

Context::Expected Context::enable()
{
    Context currenContext{};
    if (!wglMakeCurrent(mDeviceContext.get(), mGLContext.get()))
    {
        return conf::exp::unexpected(conf::fmt::format("Failed to make OpenGL context current: {}", getLastErrorMessage()));
    }
    return currenContext;
}

void Context::disable()
{
    MORPHEUS_WGL_VERIFY(wglMakeCurrent(nullptr, nullptr));
}

} // namespace morpheus::gfx::gl4::wgl
