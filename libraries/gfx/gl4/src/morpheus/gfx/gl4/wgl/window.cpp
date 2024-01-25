#include <morpheus/gfx/gl4/wgl/window.hpp>
#include <stdexcept>

namespace morpheus::gfx::gl4::wgl
{

Window::Window(Config const& config)
:   gfx::win32::RenderWindow(config)
,   mDeviceContext(
      [&]()
      {
          auto const hDC = GetDC(getHandle());
          if (!hDC)
              throw std::runtime_error("Unable to get device context from window");
          return hDC;
      }())
{}

Window::Window(HWND const window)
:   gfx::win32::RenderWindow()
,   mDeviceContext([&]()
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
