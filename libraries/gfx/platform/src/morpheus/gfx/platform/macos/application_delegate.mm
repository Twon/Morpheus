#include <morpheus/gfx/platform/macos/application_delegate.h>

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@implementation ApplicationDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
    return YES;
}

- (void)applicationWillFinishLaunching:(NSNotification*)notification
{
    // TODO - Create the menu here.
    // Set the main menu bar
    NSMenu* mainMenu = [NSApp mainMenu];
    if (mainMenu != nil)
        return;
    mainMenu = [[[NSMenu alloc] initWithTitle:@""] autorelease];
    [NSApp setMainMenu:mainMenu];

    // Application Menu (aka Apple Menu)
    NSMenuItem* appleItem = [mainMenu addItemWithTitle:@""
                                                action:nil
                                         keyEquivalent:@""];
    NSMenu* appleMenu = [[NSMenu alloc] initWithTitle:@""];
    [appleItem setSubmenu:appleMenu];

    // NSMenu*     appleMenu = [NSApplication newAppleMenu];
    // [appleItem setSubmenu:appleMenu];

    // NSMenu* appleMenu = [[NSMenu alloc] initWithTitle:@""];
    //[appleMenu addItemWithTitle:[@"About " stringByAppendingString:@"Test
    // App"]
    //                      action:@selector(orderFrontStandardAboutPanel:)
    //               keyEquivalent:@""];
    //[appleItem setSubmenu:appleMenu];

    //[window.contentView setValue: NSColor.blackColor forKey:
    //@"backgroundColor"];
    // Create a master view containing our OpenGL view
    // NSView* masterView = [[[SFBlackView alloc] initWithFrame:windowRect]
    // autorelease];
}
@end
