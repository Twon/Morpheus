#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/gl4/wgl/verify.hpp>
#include <morpheus/core/base/assert.hpp>

namespace morpheus::gfx::gl4::wgl
{

Context::Context(HWND const window, PIXELFORMATDESCRIPTOR const& pfd)
:   mOwningWindow(window)
,   mDeviceContext([&]()
        {
            MORPHEUS_ASSERT(window);
            auto const hDC = GetDC(window);
            MORPHEUS_WGL_VERIFY(hDC);
            return hDC;
        }()
    ,   { [this]() { MORPHEUS_WGL_VERIFY(ReleaseDC(*mOwningWindow, mDeviceContext.get())); } }
    )
,   mGLContext([&]()
        {
		    if (int format = ChoosePixelFormat(mDeviceContext.get(), &pfd); format != 0)
		    {
			    // ChoosePixelFormat calls out to graphics adapter drivers.  During this nvodl64v.dll set this even during success
			    // and its not cleared at the end of the function call.
			    SetLastError(0);
			    SetPixelFormat(mDeviceContext.get(), format, &pfd);
		    }
            auto const hGLContext = wglCreateContext(mDeviceContext.get());
            MORPHEUS_WGL_VERIFY(hGLContext);
            return hGLContext;
        }()
    ,   { [this]() { MORPHEUS_WGL_VERIFY(wglDeleteContext(mGLContext.get())); } }
    )
{
}

Context::Context()
:   mDeviceContext(wglGetCurrentDC(), {[](){}})
,   mGLContext(wglGetCurrentContext(), {[](){}})
{}

Context Context::enable()
{
    Context currentContext;
    MORPHEUS_WGL_VERIFY(wglMakeCurrent(mDeviceContext.get(), mGLContext.get()));
    return currentContext;
}

void Context::disable()
{   
    MORPHEUS_WGL_VERIFY(wglMakeCurrent(nullptr, nullptr));
}

} // namespace morpheus::gfx::gl4::wgl
