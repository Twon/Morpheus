#include <morpheus/core/base/assert.hpp>
#include <morpheus/core/base/debugging.hpp>
#include <morpheus/core/base/verify.hpp>
#include <morpheus/core/conformance/format.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>

#include <boost/numeric/conversion/cast.hpp>
#include <algorithm>

namespace morpheus::gfx::win32
{

namespace {

auto getModuleHandle()
{
	HINSTANCE hinst = nullptr;
	static const TCHAR findAddressFrom = TCHAR();
	auto const result = GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, &findAddressFrom, &hinst);
	MORPHEUS_VERIFY(result);
	return hinst;
}

bool HandlePowerBroadCast(WPARAM wParam, LPARAM /*lParam*/)
{
	switch (wParam) {

		//	At this point the application should save any data for open network
		//	connections, file, etc and prepare to go into suspended mode.
	case PBT_APMQUERYSUSPEND:
	{

	}
	break;

	case PBT_APMRESUMESUSPEND:
	{

	}
	break;

	// Looks like the computers battery is getting low, should probably save any essential data
	// and auto save the application state so that the user can resume the game from the current
	// position.
	case PBT_APMBATTERYLOW:
	{

	}
	break;
	default:
		break;
	}

	return true;
}

inline std::string getLastErrorMessage()
{
	DWORD const error = ::GetLastError();
	return std::system_category().message(error);
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RenderWindow* thisWindow = nullptr;

	if (message != WM_CREATE)
	{
		// Get the pointer to the active window specified by hWnd
		thisWindow = reinterpret_cast<RenderWindow*>( GetWindowLongPtr( hWnd, 0 ) ) ;
	}

	// Handle possible windows messages
	switch(message) {
	/// Handle the initial case of creating the window
	case WM_CREATE:
		{
			LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>( lParam );
			thisWindow = reinterpret_cast<RenderWindow*>( pCreateStruct->lpCreateParams );

			MORPHEUS_ASSERT_MSG(thisWindow, "Window32::WndProc() - Failed to create window");

			// Store pointer in window user data area
			::SetWindowLongPtr( hWnd, 0, reinterpret_cast<LONG_PTR>(thisWindow) );
//			thisWindow->SetActive( true );
		}
		break;

	///	Handle activation or deactivation of the window
	case WM_ACTIVATE:
		{
			MORPHEUS_ASSERT_MSG(thisWindow, "Window32::WndProc() - Failed to get active window - WM_ACTIVATE");

			// Check if the window is active
//			thisWindow->SetActive( WA_ACTIVE == LOWORD(wParam) );
		}
		break;

	case WM_PAINT:
		{
			MORPHEUS_ASSERT_MSG(thisWindow, "Window32::WndProc() - Failed to get active window - WM_PAINT");
//			if ( pThisWindow->IsActive() )
			{
//					thisWindow->PresentBackBuffer();
			}
		}
		break;

	case WM_SIZE:
		{
			MORPHEUS_VERIFY_MSG(thisWindow, "morpheus::gfx::win32::WndProc() - Failed to get active window - WM_SIZE");
			thisWindow->resize();
		}
		break;

	case WM_MOVE:
		{
		}
		break;

	case WM_KEYDOWN:
		{
			switch (wParam) {
				case 'T':
				case 't':
//					thisWindow->ToggleFullScreen();
				break;
			}
		}
		break;

	case WM_COMMAND:
		{
		}
		break;

	case WM_ENTERSIZEMOVE:
		{
			MORPHEUS_ASSERT_MSG(thisWindow, "Window32::WndProc() - Failed to get active window - WM_ENTERSIZEMOVE");
//			thisWindow->SetActive( false );
		}
		break;

	case WM_EXITSIZEMOVE:
		{
			MORPHEUS_ASSERT_MSG(thisWindow, "Window32::WndProc() - Failed to get active window - WM_EXITSIZEMOVE");
//			pThisWindow->SetActive( true );

			//! @todo	Temp measure, find a better solution
//			pThisWindow->ResizeWindow();
		}
		break;

	case WM_CLOSE:
		{
			MORPHEUS_ASSERT_MSG(thisWindow, "Window32::WndProc() - Failed to get active window - WM_CLOSE");
			// Shut down the relevant window
//			pThisWindow->Destroy();
		}
		break;

	case WM_POWERBROADCAST:
		{
			HandlePowerBroadCast(wParam, lParam);
		}
		break;

	case WM_DISPLAYCHANGE:
		{

		}
		break;

	case WM_DEVICECHANGE:
		{

		}
		break;

	case WM_SYSCOMMAND:
		{
			// Prevent moving/sizing and power loss in full screen mode
			switch( wParam )
			{
			case SC_MOVE:
			case SC_SIZE:
			case SC_MAXIMIZE:
			case SC_KEYMENU:
			case SC_MONITORPOWER:
				if(thisWindow->isFullScreen())
					return 1;
				break;
			}
		}
		break;

	case WM_DESTROY:
		{

		}
		break;

	default:
		break;
	}


	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

auto adjustWindowConfig(RenderWindow::Config& config)
{
	// The style of the window depends select setting of our window.
	DWORD dwWindowStyle = 0;

	// Select the appropriate setting for full screen or windowed mode
	if (config.isFullScreen)
	{
		dwWindowStyle |= WS_POPUP;

		// We are in full screen mode so the window must start in the top most corner
		// There is no border to take into consideration, nice and easy
		config.startX = 0;
		config.startY = 0;
	}
	else
	{
		// Set up windowed information
		dwWindowStyle |= WS_OVERLAPPEDWINDOW;

		// Get the size of the desktop
		std::int16_t const screenWidth = boost::numeric_cast<std::uint16_t>(::GetSystemMetrics(SM_CXSCREEN));
		std::int16_t const screenHeight = boost::numeric_cast<std::uint16_t>(::GetSystemMetrics(SM_CYSCREEN));

		// We need to adjust the window rectangle to ensure the client is the
		// requested size and takes the size of the window border into account.
        RECT WndRect = {0, 0, config.width, config.height};
        MORPHEUS_VERIFY(::AdjustWindowRect(&WndRect, dwWindowStyle, false));
        config.width = std::min<std::int16_t>(static_cast<std::int16_t>(WndRect.right - WndRect.left), screenWidth);
        config.height = std::min<std::int16_t>(static_cast<std::int16_t>(WndRect.bottom - WndRect.top), screenHeight);

        // If the window is going to go off the right and bottom of the
        // screen then position it back so that in fits on the screen
        config.startX = std::min<std::int16_t>(config.startX, static_cast<std::int16_t>(screenWidth - config.width));
        config.startY = std::min<std::int16_t>(config.startY, static_cast<std::int16_t>(screenHeight - config.height));
    }
	return dwWindowStyle;
}

auto createWindow(RenderWindow* thisWindow, RenderWindow::Config& config)
{
	auto const windowStyle = adjustWindowConfig(config);
	auto const hInstance = getModuleHandle();

	// Next default values for new objects
	::WNDCLASS const wcex{
		.style = CS_OWNDC, .lpfnWndProc = WndProc, .cbClsExtra = 0, .cbWndExtra = sizeof(RenderWindow*), // Reserve space for the Window pointer returned by GetWindowLong
		.hInstance = hInstance, .hIcon = ::LoadIcon(nullptr, IDI_APPLICATION), .hCursor = ::LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1), .lpszMenuName = nullptr, .lpszClassName = config.windowName.c_str()
	};

	// Register class  with the game application details
	::RegisterClass(&wcex);

	// Create the window using the WS_OVERLAPPEDWINDOW style
	auto const window = ::CreateWindow(config.windowName.c_str(), config.windowName.c_str(), windowStyle,
							config.startX, config.startY, config.width, config.height,
							nullptr, nullptr, hInstance, thisWindow);
	MORPHEUS_VERIFY(window);
	return window;
}

}

RenderWindow::RenderWindow(Config config)
:   gfx::RenderWindow(config)
,   mWindow(createWindow(this, config))
{
	//  Display the window and force an initial paint
	::ShowWindow(mWindow.get(), SW_SHOWNORMAL);
	::UpdateWindow(mWindow.get());

	// Get the true window dimensions
/*	{
		RECT WinRect, ClientRect;
		::GetWindowRect(mWindow, &WinRect);
		::GetClientRect(mWindow, &ClientRect);
		SetWidth(ClientRect.right);
		SetHeight(ClientRect.bottom);
		m_uStartX = WinRect.left;
		m_uStartY = WinRect.top;
	}*/
}

RenderWindow::RenderWindow(HWND const window)
{

}

RenderWindow::~RenderWindow()
{
	::UnregisterClass(mWindowName.c_str(), getModuleHandle());
}

void RenderWindow::resize()
{
	RECT windowRect{};
	// Get the current starting X and Y positions of the window
	::GetWindowRect(mWindow.get(), &windowRect);
	mStartX = boost::numeric_cast<std::uint16_t>(windowRect.left);
	mStartY = boost::numeric_cast<std::uint16_t>(windowRect.top);

	// Get the width and height of the drawable area
	::GetClientRect(mWindow.get(), &windowRect);

	// If the width and height have not changed then we have nothing to do
	if ((width() == windowRect.right) && (height() == windowRect.bottom))
		return;

	// We need to save the new width and height
	mWidth = boost::numeric_cast<std::uint16_t>(windowRect.right);
	mHeight = boost::numeric_cast<std::uint16_t>(windowRect.bottom);

	debugPrint(fmt_ns::format("Window <{}> is at start <{}, {}> with dimensions <{}, {}>\n", mWindowName, mStartX, mStartY, mWidth, mHeight));
}

} // namespace morpheus::gfx::win32
