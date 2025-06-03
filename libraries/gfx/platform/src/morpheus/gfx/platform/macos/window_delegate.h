#pragma once

#import <Cocoa/Cocoa.h>

@interface WindowDelegate : NSResponder<NSWindowDelegate>
@property (nonatomic) BOOL shouldClose;

- (void) windowWillClose:(NSNotification *)notification;
- (void) windowDidMiniaturize:(NSNotification *)notification;
- (void) windowDidDeminiaturize:(NSNotification *)notification;
@end
