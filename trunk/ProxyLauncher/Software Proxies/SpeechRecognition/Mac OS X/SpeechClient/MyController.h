/* MyController */

#import <Cocoa/Cocoa.h>
#import "EventHeap.h"

@interface MyController : NSObject
{
	// connection to the Event Heap
	IBOutlet EventHeap *eventHeap;
}

- (IBAction) postEventsButton:(id)sender;

// post events to the EH
- (void) postEvents;

// process the received Event Heap event
- (void) processReceivedEvent:(eh2_EventPtr)event;

@end
