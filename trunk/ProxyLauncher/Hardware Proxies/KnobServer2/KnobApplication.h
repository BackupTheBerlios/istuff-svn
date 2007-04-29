/* KnobApplication */

#import <Cocoa/Cocoa.h>
#import "KnobWindow.h"
#import "eh2.h"
@interface KnobApplication : NSApplication
{
    IBOutlet KnobWindow *mWindow;
	
	eh2_EventHeapPtr eventHeapPtr;
}
@end
