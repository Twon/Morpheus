#include <morpheus/gfx/platform/macos/application_delegate.h>
#include <morpheus/gfx/platform/macos/window_delegate.h>

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{
    @autoreleasepool {

        NSLog (@"hello world");

        [NSApplication sharedApplication];
        [NSApp setDelegate: [ApplicationDelegate alloc]];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];

        if ([NSThread currentThread] != [NSThread mainThread])
        {
            // See https://lists.apple.com/archives/cocoa-dev/2011/Feb/msg00460.html
            NSLog (@"Cannot create a window from a worker thread. (OS X limitation)");
            return 1;
        }

        NSRect windowRect = NSMakeRect(0, 0, 800, 600);
        NSWindow* window = [NSWindow alloc];
        [window initWithContentRect:windowRect
            styleMask:NSWindowStyleMaskBorderless
            backing:NSBackingStoreBuffered
            defer:NO];
        [window setDelegate: [WindowDelegate alloc]];

        // More window configuration...
        [window setOpaque:YES];
        [window setHidesOnDeactivate:YES];
        //[window setAutodisplay:YES];
        [window setReleasedWhenClosed:NO]; // We own the class, not AppKit

        [window setAcceptsMouseMovedEvents:YES];
        [window setIgnoresMouseEvents:NO];



        [[NSApplication sharedApplication] finishLaunching]; 

        [window setBackgroundColor:[NSColor blackColor]];
        [window setIsVisible:YES];
        [window makeKeyAndOrderFront:window];
        [NSApp run];
    }
}