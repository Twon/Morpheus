#include <gl4/wgl/context.hpp>
#include <gl4/wgl/verify.hpp>
#include <core/base/assert.hpp>

namespace morpheus::gfx::gl4::wgl
{

Context::Context(HWND const window, PIXELFORMATDESCRIPTOR const& pfd)
:   mOwningWindow(window),
    mDeviceContext([&]()
        {
            MORPHEUS_ASSERT(window);
            auto const hDC = GetDC(window);
            MORPHEUS_WGL_VERIFY(hDC);
            return hDC;
        }()
    )
,   mGLContext([&]()
        {
		    if (int format = ChoosePixelFormat(mDeviceContext, &pfd); format != 0)
		    {
			    // ChoosePixelFormat calls out to graphics adapter drivers.  During this nvodl64v.dll set this even during success
			    // and its not cleared at the end of the function call.
			    SetLastError(0);
			    SetPixelFormat(mDeviceContext, format, &pfd);
		    }
            auto const hGLContext = wglCreateContext(mDeviceContext);
            MORPHEUS_WGL_VERIFY(hGLContext);
            return hGLContext;
        }()
    )
,   mOwningContext(true)
{
}

Context::Context()
:   mDeviceContext(wglGetCurrentDC())
,   mGLContext(wglGetCurrentContext())
,   mOwningContext(false)
{}

Context::~Context()
{
    if (mOwningWindow)
    {
        wglDeleteContext(mGLContext);
        MORPHEUS_WGL_VERIFY(ReleaseDC(*mOwningWindow, mDeviceContext));
    }
}

Context Context::enable()
{
    Context currentContext;
    wglMakeCurrent(mDeviceContext, mGLContext);
    return currentContext;
}

void Context::disable()
{   
    MORPHEUS_WGL_VERIFY(wglMakeCurrent(nullptr, nullptr));
}

} // namespace morpheus::gfx::gl4::wgl
