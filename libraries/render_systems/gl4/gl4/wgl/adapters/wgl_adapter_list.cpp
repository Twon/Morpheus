#include <gl4/wgl/adapters/wgl_adapter_list.hpp>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace morpheus::gfx::gl4::wgl
{

namespace
{
    void enumerate_adapters()
    {
		// Initialise the display device structure
		DISPLAY_DEVICE DisplayDevice = {0};
		DisplayDevice.cb = sizeof(DISPLAY_DEVICE);

		// This is a loop with an early loop exit point, hence no condition for the loop
		for ( DWORD dwCurrentDevice = 0; EnumDisplayDevices(NULL, dwCurrentDevice, &DisplayDevice, 0); ++dwCurrentDevice ) 
		{
			// If the device is attached to the desktop, i.e. a graphics card
			if (DisplayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) 
			{
				//Create a new adapter an push it onto the list
				//GraphicsAdapterWGL	newAdapter(DisplayDevice);
				//m_GraphicsAdapters.push_back(newAdapter);
				//m_GraphicsAdapters.back().Enumerate();

				// Set the current display device to the the primary device
				if (DisplayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) 
				{
					//m_uCurrentAdapter = static_cast<u32>( m_GraphicsAdapters.size() - 1 );
				}
			}
		}
    }
}

//---------------------------------------------------------------------------------------------------------------------

adapter_list::adapter_list()
:    gfx::adapter_list(gfx::adapter_list::adapter_container())
{

}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::gl4::wgl
