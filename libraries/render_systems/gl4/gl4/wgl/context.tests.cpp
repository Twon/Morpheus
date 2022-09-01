#include <gl4/wgl/context.hpp>
#include <catch2/catch_all.hpp>


namespace morpheus::gfx::gl4::wgl
{

TEST_CASE("Create a WGL Context", "[morpheus.core.gfx.gl.wgl.context]")
{
/*
    HINSTANCE const hinst = getModuleHandle();

    LPCSTR const dummyText = "WglDummyWindow";
    WNDCLASS dummyClass = { .style = CS_OWNDC,.lpfnWndProc = dummyWndProc, .hInstance = hinst, .lpszClassName = dummyText };
    RegisterClass(&dummyClass);

    HWND hwnd = CreateWindow(dummyText, dummyText, WS_POPUP | WS_CLIPCHILDREN, 0, 0, 32, 32, 0, 0, hinst, 0);
*/
}

/*  
TEST_CASE("Iterates over the adapters in the list", "[morpheus.core.gfx.gl.wgl.adapter_list]")
{
    GIVEN("An adapter list")
    {
        //adapter_list adapters;
        THEN("Loop over all adapters using native for loop syntax")
        {
            for (auto& adapter : enumerateAdapters())
            {
                INFO("The adapter id is: " << adapter.getId());
            }
        }
    }
}
*/

} // namespace morpheus::gfx::gl4::wgl
