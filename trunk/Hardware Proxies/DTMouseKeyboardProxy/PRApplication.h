/* PRApplication */

#import <Cocoa/Cocoa.h>

@class PRController;

@interface PRApplication : NSApplication
{
    PRController* controller;
}
@end
