#include <gl4/wgl/adapter.hpp>
#include <GL/glew.h>
#include <GL/wglew.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string_view>

namespace morpheus::gfx::gl4::wgl
{

static constexpr std::string_view vendorAMD = "PCI\\VEN_1002&";
static constexpr std::string_view vendorNvidia = "PCI\\VEN_10DE&";
static constexpr std::string_view vendorIntel = "PCI\\VEN_8086&";


concurrency::Generator<Adapter> enumerateAdapters()
{
    auto displayDevice = DISPLAY_DEVICE{ .cb = sizeof(DISPLAY_DEVICE) };

	for (DWORD dwCurrentDevice = 0; ; ++dwCurrentDevice)
	{
		if (!EnumDisplayDevices(NULL, dwCurrentDevice, &displayDevice, 0))
			break;

		// If the device is attached to the desktop, i.e. a graphics card
		if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
		{
			co_yield Adapter(displayDevice.DeviceName, displayDevice.DeviceString);

			// Set the current display device to the the primary device
			if (displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
			{
				//m_uCurrentAdapter = static_cast<u32>( m_GraphicsAdapters.size() - 1 );
			}
		}
	}
}

} // namespace morpheus::gfx::gl4::wgl
