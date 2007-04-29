/* KnobWindow */

#import <Cocoa/Cocoa.h>

@interface KnobWindow : NSWindow
{
	NSWindow *resWindow;
}
- (NSRect) getScreenResolution;
@end
