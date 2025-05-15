
#include <morpheus/core/base/assert.hpp>
#include <morpheus/core/base/exceptions.hpp>
#include <morpheus/gfx/platform/macos/application_delegate.h>
#include <morpheus/gfx/platform/macos/render_window.hpp>
#include <morpheus/gfx/platform/macos/window_delegate.h>

#import "Cocoa/Cocoa.h"

#include <string>

namespace morpheus::gfx::macos
{

class RenderWindow::Impl{
public:
    Impl(Config const& config);
    Impl(Impl const&) = delete;
    Impl(Impl&&) = default;
    Impl& operator=(Impl const&) = delete;
    Impl& operator=(Impl&&) = default;

    ~Impl();

    auto pollEvents() -> void;
    auto setTitle(std::string const& title) -> void;

    [[nodiscard]] bool shouldClose() const noexcept { return mShouldClose; }

private:
    /// All window resoures on MacOS must be create on the main thread, this throw an exception if this is not the case.§
    auto throwExceptionIfNotMainThread() -> void;

    NSWindow* mHandle = nullptr;
    WindowDelegate* mWindowDelegate = nullptr;
    // ApplicationDelegate* mApplicationDelegate = nullptr;
    bool mShouldClose = false;
};

RenderWindow::Impl::Impl(Config const& config)
:   mHandle(nullptr)
,   mWindowDelegate([[WindowDelegate alloc] init])
{
    @autoreleasepool {
        throwExceptionIfNotMainThread();

        NSRect frame = NSMakeRect(config.startX, config.startY, config.width, config.height);
        NSUInteger styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
        mHandle = [[NSWindow alloc] initWithContentRect:frame
                                                styleMask:styleMask
                                                backing:NSBackingStoreBuffered
                                                defer:NO];
        setTitle(config.windowName);

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

        [mHandle setDelegate: mWindowDelegate];
        [[NSApplication sharedApplication] finishLaunching];
        // [NSApp run];
    }
}

RenderWindow::Impl::~Impl()
{
    [mHandle release];
    [mWindowDelegate release];
    // [ApplicationDelegate release];
}

void RenderWindow::Impl::pollEvents()
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

            mShouldClose = [mWindowDelegate shouldClose];
        }
    }
}

auto RenderWindow::Impl::setTitle(std::string const& title) -> void
{
    MORPHEUS_ASSERT(mHandle);

    @autoreleasepool {
        NSString* titleStr = [[NSString alloc] initWithUTF8String:title.c_str()];
        [mHandle setTitle:titleStr]; 
    }
}



auto RenderWindow::Impl::throwExceptionIfNotMainThread() -> void
{
    if ([NSThread currentThread] != [NSThread mainThread])
    {
        // See https://lists.apple.com/archives/cocoa-dev/2011/Feb/msg00460.html
        throwRuntimeException("Cannot create a window from a worker thread. (OS X limitation)");
    }
}

RenderWindow::RenderWindow(Config const& config)
:    gfx::RenderWindow(config)
,    mThis(std::make_unique<Impl>(config))
{
    // @autoreleasepool {

    //     if ([NSThread currentThread] != [NSThread mainThread])
    //     {
    //         // See https://lists.apple.com/archives/cocoa-dev/2011/Feb/msg00460.html
    //         throwRuntimeException("Cannot create a window from a worker thread. (OS X limitation)");
    //     }

    //     NSString* title = [[NSString alloc] initWithUTF8String:config.windowName.c_str()];

    //     NSRect frame = NSMakeRect(config.startX, config.startY, config.width, config.height);
    //     NSUInteger styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
    //     mHandle = [[NSWindow alloc] initWithContentRect:frame
    //                                             styleMask:styleMask
    //                                             backing:NSBackingStoreBuffered
    //                                             defer:NO];
    //     [(NSWindow *)mHandle setTitle:title];

    //     if (config.fullScreen)
    //     {
    //         [(NSWindow *)mHandle toggleFullScreen:nil];
    //     }

    //     if (config.visible)
    //     {
    //         [(NSWindow *)mHandle makeKeyAndOrderFront:nil];
    //     }

    //     [NSApp setDelegate: [ApplicationDelegate alloc]];
    //     [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    //     [NSApp activateIgnoringOtherApps:YES];


    //     [(NSWindow *)mHandle setBackgroundColor:[NSColor blackColor]];
    //     // [window setIsVisible:YES];
    //     // [window makeKeyAndOrderFront:window];

    //     // [(NSWindow *)mHandle setDelegate: [WindowDelegate alloc]];
    //     [[NSApplication sharedApplication] finishLaunching];
    //     // [NSApp run];
    // }
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


RenderWindow::RenderWindow(RenderWindow&&) noexcept = default;
RenderWindow& RenderWindow::operator=(RenderWindow&&) noexcept = default;

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

bool RenderWindow::shouldClose() const noexcept
{ 
    return mThis->shouldClose();
}

// bool RenderWindow::fullScreen() const noexcept
// { 
//     return gfx::RenderWindow::fullScreen();
// }

void RenderWindow::pollEvents()
{
    mThis->pollEvents();
}

} // namespace morpheus::gfx::macos
