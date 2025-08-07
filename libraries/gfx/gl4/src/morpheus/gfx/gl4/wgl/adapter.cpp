#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/gl4/wgl/adapter.hpp>
#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/gl4/wgl/verify.hpp>

#include <regex>
#include <sstream>

// https://stackoverflow.com/questions/16823372/forcing-machine-to-use-dedicated-graphics-card
#ifdef _WIN32
#include <windows.h>
//extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
#endif

namespace morpheus::gfx::gl4::wgl
{

static constexpr std::string_view vendorAMD = "PCI\\VEN_1002&";
static constexpr std::string_view vendorNvidia = "PCI\\VEN_10DE&";
static constexpr std::string_view vendorIntel = "PCI\\VEN_8086&";

namespace
{

auto getModuleHandle()
{
    HINSTANCE hinst = nullptr;
    static const TCHAR findAddressFrom = TCHAR();
    auto const result = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, &findAddressFrom, &hinst);
    MORPHEUS_WGL_VERIFY(result);
    return hinst;
}

auto pciIdFromDeviceId(std::string_view const deviceId)
{
    auto const pciIdStr = deviceId.substr(deviceId.find_first_not_of("PCI\\VEN_"), 4);
    std::uint32_t pciId = 0;
    std::stringstream ss;
    ss << std::hex << pciIdStr;
    ss >> pciId;
    return pciId;
}

auto vendorFromDeviceId(std::string_view const deviceId)
{
    auto const pciId = pciIdFromDeviceId(deviceId);
    auto const vendor = vendorFromPciId(pciId);
    MORPHEUS_VERIFY(vendor);
    return *vendor;
}

std::string_view glGetStringView(GLenum name)
{
    const GLubyte* str = glGetString(name);
    return str ? std::string_view(reinterpret_cast<const char*>(str)) : std::string_view{};
}

} // namespace

LRESULT CALLBACK dummyWndProc(HWND hwnd, UINT umsg, WPARAM wp, LPARAM lp)
{
    return DefWindowProc(hwnd, umsg, wp, lp);
}

concurrency::Generator<Adapter> enumerateAdapters()
{
    auto displayDevice = DISPLAY_DEVICE{.cb = sizeof(DISPLAY_DEVICE)};

    HINSTANCE const hinst = getModuleHandle();

    LPCSTR const dummyText = "WglDummyWindow";
    WNDCLASS dummyClass = {.style = CS_OWNDC, .lpfnWndProc = dummyWndProc, .hInstance = hinst, .lpszClassName = dummyText};
    RegisterClass(&dummyClass);

    HWND hwnd = CreateWindow(dummyText, dummyText, WS_POPUP | WS_CLIPCHILDREN, 0, 0, 32, 32, 0, 0, hinst, 0);

    //	auto const hDC = GetDC(hwnd);
    //	auto const hResults = GetLastError();

    for (DWORD dwCurrentDevice = 0;; ++dwCurrentDevice)
    {
        if (!EnumDisplayDevices(NULL, dwCurrentDevice, &displayDevice, 0))
            break;

		PIXELFORMATDESCRIPTOR pfd =
		{
			.nSize = sizeof(PIXELFORMATDESCRIPTOR),
			.nVersion = 1,
			.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			.iPixelType = PFD_TYPE_RGBA, // The kind of framebuffer. RGBA or palette.
			.cColorBits = 32, // Colour depth of the framebuffer.
			.cDepthBits = 24, // Number of bits for the depthbuffer
			.cStencilBits = 8, // Number of bits for the stencilbuffer
			.cAuxBuffers = 0, // Number of Aux buffers in the framebuffer.
			.iLayerType = PFD_MAIN_PLANE,
		};

        //		auto const glContext = wglCreateContext(hDC);
        //		auto const hResult2 = GetLastError();
        //		auto const successful = wglMakeCurrent(hDC, glContext);

        auto context = Context::create(hwnd, pfd);
        if (!context)
            continue;

        auto oldContext = context.value().enable();
        std::string_view vendor = glGetStringView(GL_VENDOR);
        std::string_view renderer = glGetStringView(GL_RENDERER);
        std::string_view version = glGetStringView(GL_VERSION);

        // If the device is attached to the desktop, i.e. a graphics card
        if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
        {
            co_yield Adapter(displayDevice.DeviceName, displayDevice.DeviceString, vendorFromDeviceId(displayDevice.DeviceID));

            // Set the current display device to the the primary device
            if (displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
            {
                // m_uCurrentAdapter = static_cast<u32>( m_GraphicsAdapters.size() - 1 );
            }
        }
        oldContext.enable();
    }
}

} // namespace morpheus::gfx::gl4::wgl
