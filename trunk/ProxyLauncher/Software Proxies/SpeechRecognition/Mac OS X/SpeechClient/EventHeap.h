//
//  EventHeap.h
//  SpeechClient
//
//  Created by Daniel Spelmezan on Fri Jun 04 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <eh2.h>
#import <idk_io.h>

// EventHeap is my Cocoa class that wraps the Event Heap API
//
@interface EventHeap : NSObject
{
	// myController connects to class MyController
	IBOutlet id myController;
	
	// pointer to the event heap client
	eh2_EventHeapPtr *eh;
	
	// signal whether or not to exit the waitforEvent thread
	BOOL waitForEvents;
}

// initialize the event heap
- (void) initialize;
// finalize the event heap client library
- (void) finalize;

// create the event heap instance for the client
- (void) createEventHeap;

// activate the thread that waits for EventHeap events
- (void) startReceivingEvents;
// deactivate the thread that waits for EventHeap events
- (void) stopReceivingEvents;

// create a new event
- (eh2_EventPtr *) createEvent;
// post the event to the heap
- (void) postEvent:(eh2_EventPtr *)eventPtr;
// put a key/value pair to the event
- (void) putStrKey:(char *)key andStrValue:(char * )value toEvent:(eh2_EventPtr *)eventPtr;
- (void) putStrKey:(char *)key andIntValue:(int)value toEvent:(eh2_EventPtr *)eventPtr;

@end
