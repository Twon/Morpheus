
#include <morpheus/gfx/platform/macos/render_window.hpp>
#include <morpheus/gfx/platform/macos/window_delegate.h>

#import "Cocoa/Cocoa.h"

namespace morpheus::gfx::macos
{

RenderWindow::RenderWindow(Config const& config)
{

}

RenderWindow::RenderWindow(WindowHandle const window)
:   mHandle(window)
{
    const id nsHandle = static_cast<id>(mHandle);
    if ([nsHandle isKindOfClass:[NSWindow class]])
    {
        [window setDelegate: [WindowDelegate alloc]];
        // We have a window.
        //m_delegate = [[SFWindowController alloc] initWithWindow:nsHandle];
    }
    else if ([nsHandle isKindOfClass:[NSView class]])
    {
        // We have a window.
        //m_delegate = [[SFWindowController alloc] initWithWindow:nsHandle];
    }
}

} // namespace morpheus::gfx::macos
