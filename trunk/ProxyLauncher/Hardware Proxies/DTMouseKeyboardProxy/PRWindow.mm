#import "PRWindow.h"

#import "PRController.h"

@implementation PRWindow

- (id)initWithFrame:(NSRect)frame withController:(PRController*)theController
{
    self = [super initWithContentRect:frame styleMask:NSBorderlessWindowMask backing:NSBackingStoreBuffered defer:NO];
    if (self)
    {
        controller = theController;

        [self setLevel:CGShieldingWindowLevel()];
        [self setBackgroundColor:[NSColor blackColor]];
        [self setAlphaValue:0.3];
        currentModifiers = 0;
    }
    return self;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (void)startTracking
{
    justStartedTracking = YES;
    [[self contentView] addTrackingRect:[[self contentView] bounds] owner:self userData:nil assumeInside:NO];
}

- (void)mouseEntered:(NSEvent*)theEvent
{
    if (![controller isSending]) [controller attemptStart:[NSEvent mouseLocation]];
}

- (void)mouseMoved:(NSEvent*)theEvent
{
    if ([controller isSending])
    {
        if (justStartedTracking) { justStartedTracking = NO; return; }
        [controller mouseMoved];
    }
}
/*
- (void)mouseDragged:(NSEvent*)theEvent { [self mouseMoved:theEvent]; }
- (void)rightMouseMoved:(NSEvent*)theEvent { [self mouseMoved:theEvent]; }
- (void)otherMouseMoved:(NSEvent*)theEvent { [self mouseMoved:theEvent]; }
- (void)rightMouseDragged:(NSEvent*)theEvent { [self mouseMoved:theEvent]; }
- (void)otherMouseDragged:(NSEvent*)theEvent { [self mouseMoved:theEvent]; }
*/
- (void)mouseDown:(NSEvent*)theEvent
{
    if ([controller isSending]) [controller mouseButton:[theEvent buttonNumber] isDown:YES];
}

//- (void)rightMouseDown:(NSEvent*)theEvent { [self mouseDown:theEvent]; }
//- (void)otherMouseDown:(NSEvent*)theEvent { [self mouseDown:theEvent]; }

- (void)mouseUp:(NSEvent*)theEvent
{
    if ([controller isSending]) [controller mouseButton:[theEvent buttonNumber] isDown:NO];
}

//- (void)rightMouseUp:(NSEvent*)theEvent { [self mouseUp:theEvent]; }
//- (void)otherMouseUp:(NSEvent*)theEvent { [self mouseUp:theEvent]; }

- (void)scrollWheel:(NSEvent*)theEvent
{
    if ([controller isSending]) [controller scrollWheel:(int)[theEvent deltaY]];
}

- (void)keyDown:(NSEvent*)theEvent
{
	/*
	NSString *chars = [theEvent charactersIgnoringModifiers];
    [controller charCode:[chars characterAtIndex:0] keyCode:[theEvent keyCode] isDown:YES];

    // Special trap for Cmd-Ctl-Q, the special SAVE ME escape sequence
    if (([theEvent modifierFlags] & PRKEY_COMMAND) && ([theEvent modifierFlags] & PRKEY_CONTROL)) {
         int ch = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
		 
        
		 if ([controller isSending] && (ch == 'q' || ch == 'Q')){	
			cout << [[theEvent charactersIgnoringModifiers] characterAtIndex:0];   
               // Then get me off this tube of death!
              [controller stopCapture];
              return;
		 }
		 else if (![controller isSending] && (ch == 's' || ch == 'S')){	   
			   [controller startCapture];
			   return;
		}
	}*/

    if ([controller isSending])
    {
        NSString *chars = [theEvent charactersIgnoringModifiers];
        [controller charCode:[chars characterAtIndex:0] keyCode:[theEvent keyCode] isDown:YES];

        // Special trap for Cmd-Ctl-Q, the special SAVE ME escape sequence
        if (([theEvent modifierFlags] & PRKEY_COMMAND) && ([theEvent modifierFlags] & PRKEY_CONTROL)) {
            int ch = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
            
            if (ch == 'q' || ch == 'Q') {
                // Then get me off this tube of death!
                
                [controller stopCapture];
                return;
            }
        }
    }
}

- (void)keyUp:(NSEvent*)theEvent
{
    if ([controller isSending])
    {
        NSString *chars = [theEvent charactersIgnoringModifiers];
        [controller charCode:[chars characterAtIndex:0] keyCode:[theEvent keyCode] isDown:NO];
    }
}

- (void)flagsChanged:(NSEvent*)theEvent
{
    if ([controller isSending])
    {
        unsigned int modifiers = [theEvent modifierFlags];

		cout << "here";
        //cout.setf(ios::hex, ios::basefield);
        //cout << modifiers << endl;
        //cout.setf(ios::dec, ios::basefield);

        if ((currentModifiers & PRKEY_CAPSLOCK) != (modifiers & PRKEY_CAPSLOCK))
            [controller charCode:PRKEY_CAPSLOCK keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_CAPSLOCK)];
        
        if ((currentModifiers & PRKEY_SHIFT) != (modifiers & PRKEY_SHIFT))
            [controller charCode:PRKEY_SHIFT keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_SHIFT)];
        
        if ((currentModifiers & PRKEY_CONTROL) != (modifiers & PRKEY_CONTROL))
            [controller charCode:PRKEY_CONTROL keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_CONTROL)];
        
        if ((currentModifiers & PRKEY_OPTION) != (modifiers & PRKEY_OPTION))
            [controller charCode:PRKEY_OPTION keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_OPTION)];
        
        if ((currentModifiers & PRKEY_COMMAND) != (modifiers & PRKEY_COMMAND))
            [controller charCode:PRKEY_COMMAND keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_COMMAND)];

        if ((currentModifiers & PRKEY_NUMERIC) != (modifiers & PRKEY_NUMERIC))
            [controller charCode:PRKEY_NUMERIC keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_NUMERIC)];
        
        if ((currentModifiers & PRKEY_HELP) != (modifiers & PRKEY_HELP))
            [controller charCode:PRKEY_HELP keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_HELP)];

        if ((currentModifiers & PRKEY_FUNCTION) != (modifiers & PRKEY_FUNCTION))
            [controller charCode:PRKEY_FUNCTION keyCode:[theEvent keyCode] isDown:(modifiers & PRKEY_FUNCTION)];
        
        currentModifiers = modifiers;
    }
}

@end
