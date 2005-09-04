#import "PRApplication.h"

#import "PRController.h"

@implementation PRApplication

- (void)sendEvent:(NSEvent*)theEvent
{
    //NSLog([theEvent description]);
	if ([theEvent type] == NSKeyDown){
		NSLog(@"key down");
	}

    switch ([theEvent type]) {
        
        case NSLeftMouseDown:
        case NSRightMouseDown:
        case NSOtherMouseDown:	[[controller window] mouseDown:theEvent];	break;

        case NSLeftMouseUp:
        case NSRightMouseUp:
        case NSOtherMouseUp:	[[controller window] mouseUp:theEvent];		break;
            
        case NSMouseMoved:
        case NSLeftMouseDragged:
        case NSRightMouseDragged:
        case NSOtherMouseDragged:[[controller window] mouseMoved:theEvent];	break;

        //case NSMouseEntered:	[[controller window] mouseEntered:theEvent];	break;

        //case NSMouseExited:	break;
            
        case NSKeyDown:		[[controller window] keyDown:theEvent];		break;
        case NSKeyUp:		[[controller window] keyUp:theEvent];		break;
        case NSFlagsChanged:	[[controller window] flagsChanged:theEvent];	break;
            
        default:		[super sendEvent:theEvent];			break;
    }
    
    /*
    if ([theEvent type] == NSAppKitDefined || [theEvent type] == NSSystemDefined || [theEvent type] == NSApplicationDefined) [super sendEvent:theEvent];
    else if ([theEvent type] == NSKeyDown) [[controller window] keyDown:theEvent];
    else if ([theEvent type] == NSRightMouseDown) [[controller window] rightMouseDown:theEvent];
    else if ([theEvent type] == NSRightMouseUp) [[controller window] rightMouseUp:theEvent];
    else if ([theEvent type] == NSRightMouseDragged) [[controller window] rightMouseDragged:theEvent];
    else [[controller window] sendEvent:theEvent];
     */
}

- (void)applicationDidBecomeActive:(NSNotification *)notification
{
    NSLog(@"PRSender did become active");
}

- (void)applicationDidResignActive:(NSNotification *)notification
{
    NSLog(@"PRSender did resign active");
    if ([controller isSending]) [controller stopCapture];
}

@end
