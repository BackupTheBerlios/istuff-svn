//
//  EventHeap.h
//  SpeechServer
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
	// myController is the connection to class MyController
	//IBOutlet id myController; //This deleagets to the event processor

	// pointer to the Event Heap client
	eh2_EventHeapPtr *eh;
	
	// signal whether or not to exit the thread waitforEvent
	BOOL waitForEvents;
}

// init the event heap client library
- (void) initialize;
- (void) finalize;

// create the event heap instance for the client
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port;

// activate/deactivate the thread that waits for EventHeap events
- (void) startReceivingEvents;
- (void) stopReceivingEvents;

// create / post an event
- (eh2_EventPtr *) createEvent:(NSString *)eventTypeName;
- (void) postEvent:(eh2_EventPtr *)eventPtr;

// put a key/value pair to the event
- (void) putStrKey:(char *)key andStrValue:(char * )value toEvent:(eh2_EventPtr *)eventPtr;
- (void) putStrKey:(char *)key andIntValue:(int)value toEvent:(eh2_EventPtr *)eventPtr;

@end
