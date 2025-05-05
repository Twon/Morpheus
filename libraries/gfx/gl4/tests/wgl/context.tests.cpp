#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>

#include <catch2/catch_all.hpp>


namespace morpheus::gfx::gl4::wgl
{

TEST_CASE("Create a WGL Context", "[morpheus.gfx.gl4.wgl.context]")
{
    GIVEN("A new constructed wgl context")
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
        win32::RenderWindow window;
        Context context(window.getHandle(), pxlFmtDescriptor);

        wglMakeCurrent(nullptr, nullptr);
        auto const globalDC = wglGetCurrentDC();
        auto const globalGL = wglGetCurrentContext();

        WHEN("enabling the context")
        {
            auto globalContext = context.enable();

            THEN("expect the context to be set as active and the global context for the thread to be returned")
            {
                REQUIRE(context.getDC() == wglGetCurrentDC());
                REQUIRE(context.getGL() == wglGetCurrentContext());
                REQUIRE(globalContext.getDC() == globalDC);
                REQUIRE(globalContext.getGL() == globalGL);

                AND_WHEN("disabling the context")
                {
                    context.disable();

                    THEN("expect the global context to be restored")
                    {
                        REQUIRE(wglGetCurrentDC() == globalDC);
                        REQUIRE(wglGetCurrentContext() == globalGL);
                    }
                }
            }
        }
    }
}

} // namespace morpheus::gfx::gl4::wgl
