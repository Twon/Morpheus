#include <morpheus/application/application.hpp>
#include <morpheus/application/try_catch.hpp>
#include <morpheus/gfx/gl4/render_system.hpp>
// #include <morpheus/gfx/platform/render_system_factory.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>

using namespace morpheus::application;
using namespace morpheus::gfx;

class RenderTriange : public Application
{
public:
    using Application::Application;

    void Run()
    {
        while (true)
        {
            //			#pragma FREEDOM_TODO( "Hide message pump behind Freedom operating system abstraction")

            ::MSG msg;
            ::ZeroMemory(&msg, sizeof(msg));

            // While there is messages in the queue pump them
            // till the message queue until it is empty
            while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
            {
                if (::GetMessage(&msg, NULL, 0, 0))
                {
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                }
            }
        }
    }

protected:
    win32::RenderWindow window;
};

int main(int argc, char* argv[])
{

    tryCatch(
        [&]
        {
            RenderTriange example(argc, argv);
            example.Run();
        });

    //    render_system_factory renderer_factory;
}
