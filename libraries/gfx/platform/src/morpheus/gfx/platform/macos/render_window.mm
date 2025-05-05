
#include <morpheus/core/base/exceptions.hpp>
#include <morpheus/gfx/platform/macos/application_delegate.h>
#include <morpheus/gfx/platform/macos/render_window.hpp>
#include <morpheus/gfx/platform/macos/window_delegate.h>

#import "Cocoa/Cocoa.h"

namespace morpheus::gfx::macos
{

RenderWindow::RenderWindow(Config const& config)
: gfx::RenderWindow(config)
{
    @autoreleasepool {

        if ([NSThread currentThread] != [NSThread mainThread])
        {
            // See https://lists.apple.com/archives/cocoa-dev/2011/Feb/msg00460.html
            throwRuntimeException("Cannot create a window from a worker thread. (OS X limitation)");
        }

        NSString* title = [[NSString alloc] initWithUTF8String:config.windowName.c_str()];

        NSRect frame = NSMakeRect(config.startX, config.startY, config.width, config.height);
        NSUInteger styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
        mHandle = [[NSWindow alloc] initWithContentRect:frame
                                                styleMask:styleMask
                                                backing:NSBackingStoreBuffered
                                                defer:NO];
        [(NSWindow *)mHandle setTitle:title];

        if (config.fullScreen)
        {
            [(NSWindow *)mHandle toggleFullScreen:nil];
        }

        if (config.visible)
        {
            [(NSWindow *)mHandle makeKeyAndOrderFront:nil];
        }

        [NSApp setDelegate: [ApplicationDelegate alloc]];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];


        [(NSWindow *)mHandle setBackgroundColor:[NSColor blackColor]];
        // [window setIsVisible:YES];
        // [window makeKeyAndOrderFront:window];

        // [(NSWindow *)mHandle setDelegate: [WindowDelegate alloc]];
        [[NSApplication sharedApplication] finishLaunching];
        // [NSApp run];
    }
}

RenderWindow::RenderWindow(WindowHandle const window)
:   mHandle(window)
{
    const id nsHandle = static_cast<id>(mHandle);
    if ([nsHandle isKindOfClass:[NSWindow class]])
    {
        [(NSWindow *)window setDelegate: [WindowDelegate alloc]];
        // We have a window.
        //m_delegate = [[SFWindowController alloc] initWithWindow:nsHandle];
    }
    else if ([nsHandle isKindOfClass:[NSView class]])
    {
        // We have a window.
        //m_delegate = [[SFWindowController alloc] initWithWindow:nsHandle];
    }
}

RenderWindow::~RenderWindow()
{
    @autoreleasepool {

        // WindowDelegate* delegate = (WindowDelegate*)[(NSWindow*)mHandle delegate];
        // [delegate release];
        
        if (mHandle)
        {
            [(NSWindow *)mHandle close];
            [(NSWindow *)mHandle release];
        }
    }
}

bool RenderWindow::hasFocus() const {
    @autoreleasepool {
        NSWindow* window = (NSWindow*)mHandle;
        if (!window) return false;

        return [window isKeyWindow] || [window isMainWindow];
    }
}

void RenderWindow::show() {
    [(NSWindow*)mHandle makeKeyAndOrderFront:nil];
}

void RenderWindow::pollEvents()
{
    @autoreleasepool {

        NSApplication* app = NSApplication.sharedApplication;
        NSEvent* event = [app nextEventMatchingMask:NSEventMaskAny
                                          untilDate:[NSDate distantPast]
                                             inMode:NSDefaultRunLoopMode
                                            dequeue:YES];
        if (event)
        {
            [app sendEvent:event];

            // WindowDelegate* delegate = (WindowDelegate*)[(NSWindow*)mHandle delegate];
            // mShouldClose = [delegate shouldClose];
        }
    }
}

} // namespace morpheus::gfx::macos
