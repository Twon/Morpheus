#include <morpheus/core/base/assert.hpp>
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

WGLExpected<int> choosePixelFormat(HDC const hdc, PIXELFORMATDESCRIPTOR const& pfd)
{
    auto const format = ChoosePixelFormat(hdc, &pfd);
    if (format == 0)
        return conf::exp::unexpected(conf::fmt::format("Failed to choose pixel format: {}", getLastErrorMessage()));
    return format;
}

WGLExpected<void> setPixelFormat(HDC hdc, int format)
{
    PIXELFORMATDESCRIPTOR pfd;
    if (!DescribePixelFormat(hdc, format, sizeof(pfd), &pfd))
        return conf::exp::unexpected(conf::fmt::format("Failed to describe pixel format: {}", getLastErrorMessage()));

    if (!SetPixelFormat(hdc, format, &pfd))
        return conf::exp::unexpected(conf::fmt::format("Failed to set pixel format: {}", getLastErrorMessage()));
    return {};
}

WGLExpected<HGLRC> createGLContext(HDC hdc)
{
    if (auto hglrc = wglCreateContext(hdc); hglrc)
        return hglrc;
    else
        return conf::exp::unexpected(conf::fmt::format("Failed to create OpenGL context: {}", getLastErrorMessage()));
}

} // namespace

Context::Expected Context::create(HWND const window, PIXELFORMATDESCRIPTOR const& pfd)
{
    // clang-format off
    return createDC(window)
        .and_then([&](HDC const hdc)
            { return choosePixelFormat(hdc, pfd)
                .and_then([hdc, &pfd](int format)
                    { return setPixelFormat(hdc, format)
                        .transform([hdc]() { return hdc; });
                    });
            })
        .and_then([&](HDC const hdc){
            return createGLContext(hdc)
                .transform([window, hdc](HGLRC const hglrc) {
                    glbinding::initialize(
                        [](const char * name) -> glbinding::ProcAddress {
                            return reinterpret_cast<glbinding::ProcAddress>(wglGetProcAddress(name));
                        },
                        true
                    );
                    return Context(window, hdc, hglrc);
                });
        });
    // clang-format on
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
