#import "KnobWindow.h"

@implementation KnobWindow


- (id) initWithContentRect:(NSRect)contentRect styleMask:(unsigned int)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag
{
	
	//NSWindow *blinkWindow = [[NSWindow alloc] initWithContentRect:[self getScreenResolution] styleMask:NSBorderlessWindowMask backing:bufferingType defer:flag];
	self = [super initWithContentRect:[self getScreenResolution] styleMask:NSBorderlessWindowMask backing:bufferingType defer:flag];

	[self setLevel:NSPopUpMenuWindowLevel];
	//[resWindow setLevel:CGShieldingWindowLevel()];
	[self setAlphaValue: 0.1];
	[self setIgnoresMouseEvents:YES];
	//[self setIgnoresMouseEvents:NO];
	//[self setInitialFirstResponder:];
	// [self makeFirstResponder:self];
	//[[self contentView] addTrackingRect:[[resWindow contentView] bounds] owner:resWindow userData:nil assumeInside:NO];
	return self;
}



- (NSRect) getScreenResolution
{
   return [[[NSScreen screens] objectAtIndex: 0] frame];
}



/* This is the preferred way to determine events */
// if you want to get events sent to you, you must make yourself a first responder
- (BOOL)acceptsFirstResponder
{
    return YES;
}
- (BOOL)becomeFirstResponder
{
    return YES;
}

/*
// handle key down events
// if you don't handle this, the system beeps when you press a key (how annoying)
- (void)keyDown:(NSEvent *)theEvent
{
    NSLog( @"key down" );
}
// handle mouse up events (left mouse button)
- (void)mouseUp:(NSEvent *)theEvent
{
    NSPoint pt = [theEvent locationInWindow];
    NSLog(@"EVENT %f %f", pt.x, pt.y);
}
// handle mouse movement events (left mouse button)
- (void)mouseMoved:(NSEvent *)theEvent
{
    NSPoint pt = [theEvent locationInWindow];
    NSLog(@"EVENT %f %f", pt.x, pt.y);
}

- (void) scrollWheel:(NSEvent *) event
{
	NSLog(@"hallo");
	//[super scrollWheel:event];
}


- (void)keyUp:(NSEvent *) event
{
	NSLog(@"hallo4");
}*/
@end
