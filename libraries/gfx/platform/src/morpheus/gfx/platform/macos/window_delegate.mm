#include <morpheus/gfx/platform/macos/window_delegate.h>

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@implementation WindowDelegate
- (instancetype)init {
    self = [super init];
    _shouldClose = NO;
    return self;
}
- (void)windowWillClose:(NSNotification *)notification {
    _shouldClose = YES;
}

- (void) windowDidMiniaturize: (NSNotification *)notification
{

}
- (void) windowDidDeminiaturize: (NSNotification *)notification
{

}
@end
