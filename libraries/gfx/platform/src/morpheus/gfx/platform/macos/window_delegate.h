#pragma once

#import <Cocoa/Cocoa.h>

@interface WindowDelegate : NSResponder<NSWindowDelegate>
- (void) windowDidMiniaturize:(NSNotification *)notification;
- (void) windowDidDeminiaturize:(NSNotification *)notification;
@end
