#include <gl4/wgl/window.hpp>
#include <stdexcept>

namespace morpheus::gfx::gl4::wgl
{

Window::Window(HWND const window)
:   mDeviceContext([&]()
        {
            auto const hDC = GetDC(window);
            if (!hDC)
                throw std::runtime_error("Unable to get device context from window");
            return hDC;
        }()
    )
{
}

} // namespace morpheus::gfx::gl4::wgl
