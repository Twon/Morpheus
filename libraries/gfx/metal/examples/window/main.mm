#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

int main(int argc, const char * argv[])
{
 
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    NSLog (@"hello world");

    [NSApplication sharedApplication];
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

    // More window configuration...
    [window setOpaque:YES];
    [window setHidesOnDeactivate:YES];
    [window setAutodisplay:YES];
    [window setReleasedWhenClosed:NO]; // We own the class, not AppKit

    [window setAcceptsMouseMovedEvents:YES];
    [window setIgnoresMouseEvents:NO];


    //[window.contentView setValue: NSColor.blackColor forKey: @"backgroundColor"];
    // Create a master view containing our OpenGL view
    //NSView* masterView = [[[SFBlackView alloc] initWithFrame:windowRect] autorelease];

    [[NSApplication sharedApplication] finishLaunching]; 

    [window setBackgroundColor:[NSColor blackColor]];
    [window makeKeyAndOrderFront:NSApp];
    [NSApp run];

    [pool drain];
}