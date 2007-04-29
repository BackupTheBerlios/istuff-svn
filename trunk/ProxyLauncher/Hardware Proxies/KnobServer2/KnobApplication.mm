#import "KnobApplication.h"

@implementation KnobApplication

- (void)awakeFromNib
{
	eh2_EventHeapFactory* factory;
	eh2_init(NULL,NULL);
	factory = eh2_EventHeapFactory::cs_getInstance();
	eventHeapPtr = factory->createEventHeap(
											NULL,
											"localhost",
											-1
											);
	

	[[NSApplication sharedApplication] setDelegate:[NSApplication sharedApplication]];
	//mWindow = [[KnobWindow alloc] initWithContentRect:nil withController:self];
    [mWindow makeKeyAndOrderFront:self];
    [mWindow makeFirstResponder: mWindow];
}

- (void)sendEvent:(NSEvent*)theEvent
{
	float deltaY;
	eh2_EventPtr eventPtr;
    //NSLog([theEvent description]);
	switch ([theEvent type]) {
		case NSScrollWheel:
			deltaY = [theEvent deltaY];
			NSLog(@"The place to send %d\n" , (int)deltaY);
			eventPtr = eh2_Event::cs_create("ScrollEvent");
			
			eventPtr->setPostValueInt("delta",(int)deltaY);
			//EY: Memory error if I set the template value to formal, why?
			//eventPtr->setTemplateValueString("delta", "FORMAL");	
			eventPtr->setPostValueInt("TimeToLive",2000);	
			eventHeapPtr->putEvent(eventPtr);
        /*case NSLeftMouseDown:
        case NSRightMouseDown:
        case NSOtherMouseDown:	//[[controller window] mouseDown:theEvent];	break;

        case NSLeftMouseUp:
        case NSRightMouseUp:
        case NSOtherMouseUp:	//[[controller window] mouseUp:theEvent];		break;
            
        case NSMouseMoved:
        case NSLeftMouseDragged:
        case NSRightMouseDragged:
        case NSOtherMouseDragged://[[controller window] mouseMoved:theEvent];	break;

        //case NSMouseEntered:	[[controller window] mouseEntered:theEvent];	break;

        //case NSMouseExited:	break;
            
        case NSKeyDown:		//[[controller window] keyDown:theEvent];		break;
        case NSKeyUp:		//[[controller window] keyUp:theEvent];		break;
        case NSFlagsChanged:	//[[controller window] flagsChanged:theEvent];	break;
          */  
        default:		[super sendEvent:theEvent];			break;
    }
	[self activateIgnoringOtherApps: YES];
}
@end
