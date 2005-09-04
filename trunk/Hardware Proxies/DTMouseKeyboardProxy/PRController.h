/* PRController */

#import <Cocoa/Cocoa.h>

@class PRWindow;

#include "PRWorld.h"
using namespace prlogic;

@interface PRController : NSObject
{
    NSRect screenFrame, topFrame;
    PRWindow *window;
    PRWorld *world;
    CFStringRef prefKey;
}

- (void)setBooleanPref:(NSString*)key to:(BOOL)value;
- (NSString*)getStringPref:(NSString*)key;
- (NSWindow*)window;
- (bool)isSending;
- (void)attemptStart:(NSPoint)mouseLocation;
- (void)startCapture;
- (void)stopCapture;
- (void)mouseMoved;
- (void)mouseButton:(int)button isDown:(bool)isDown;
- (void)scrollWheel:(int)value;
- (void)charCode:(int)charCode keyCode:(int)keyCode isDown:(bool)isDown;

@end
