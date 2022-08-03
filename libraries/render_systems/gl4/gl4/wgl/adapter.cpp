#include <gl4/wgl/adapter.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace morpheus::gfx::gl4::wgl
{

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
			co_yield Adapter(displayDevice.DeviceName);

			//Create a new adapter an push it onto the list
			//GraphicsAdapterWGL	newAdapter(DisplayDevice);
			//m_GraphicsAdapters.push_back(newAdapter);
			//m_GraphicsAdapters.back().Enumerate();

			// Set the current display device to the the primary device
			if (displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
			{
				//m_uCurrentAdapter = static_cast<u32>( m_GraphicsAdapters.size() - 1 );
			}
		}
	}
}




/*
AdapterList enumerateAdapters()
{
    auto displayDevice = DISPLAY_DEVICE{ .cb = sizeof(DISPLAY_DEVICE) };

    AdapterList adapters;
//    ranges::move(instance.enumeratePhysicalDevices(), ranges::back_inserter(adapters));
    return adapters;
}
*/

} // namespace morpheus::gfx::gl4::wgl
