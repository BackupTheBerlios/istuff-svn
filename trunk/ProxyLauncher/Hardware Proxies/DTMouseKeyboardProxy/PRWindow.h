/* PRWindow.h */

#import <Cocoa/Cocoa.h>

@class PRController;

@interface PRWindow : NSWindow
{
    PRController *controller;
    bool justStartedTracking;
    unsigned int currentModifiers;
}

- (id)initWithFrame:(NSRect)frame withController:(PRController*)theController;
- (void)startTracking;

@end
