#pragma once

#import <Cocoa/Cocoa.h>

@interface ApplicationDelegate : NSResponder<NSApplicationDelegate>

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;

- (void)applicationWillFinishLaunching:(NSNotification *)notification;
@end
