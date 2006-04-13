//
//  iStuffProviderPatch.mm
//  QCiStuff
//
//  Created by René Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#include  "iStuffProviderPatch.h"

@implementation iStuffProviderPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
        return 2;
}

- (id)initWithIdentifier:(id)fp8
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(startReceivingEvents) name:@"EventHeapListChanged" object:nil];
	return [super initWithIdentifier:fp8];
}

// This method is needed for Provider patches
- (void) startReceivingEvents
{
	// set the flag to activate the thread
	waitForEvents = TRUE;
	// create the thread that waits for events
	[NSThread detachNewThreadSelector:@selector(waitForEvents) toTarget:self withObject:nil];
	// We need threads that can manuall be killed. That might be the soultion to the waitForEvent problem.
}



- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;	 
	if ((eh != nil)  && ([self connected]) ){
	NSLog(@"TRYING TO PUT SOMETHING");
		//create a new event object
		eh2_EventPtr *eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("DUMMY");
		(*eventPtr)->setPostValueInt("TimeToLive", 10000);
		(*eh)->putEvent(*eventPtr);
		//sleep(1);  // IF CRASHES OCCUR WHILE CHANGING THE EVENT HEAPS, MAKE USE OF SLEEP AGAIN.
			NSLog(@"ACTUALLY PUT SOMETHING");
	}
}

// thread waiting for EH events, so we won't block the recognition system
// the function call (*eh)->waitForEvent is blocking !
// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];
	// define the type of events you want to receive
	eh2_EventPtr templatePtr = eh2_Event::cs_create ([eventType cString]);

	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");
	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
		
		// Check if the event is for the current patch
		NSString *receivedEventType = [NSString stringWithCString:resultEventPtr->getEventType()];
		if ([receivedEventType isEqualToString:eventType]) {
			NSString *receivedEventID = [NSString stringWithCString:resultEventPtr->getPostValueString("ProxyID")];				
			if ( ([receivedEventID isEqualToString:eventID]) || ([self listenToEverything] == NSOnState) ) 
				[self processEvent:resultEventPtr];
		}
	}

//	NSLog(@"WAITFOREVENTS REALLY QUIT IN %@", self);
	[localPool release];
}

- (void) processEvent:(eh2_EventPtr) eventPtr{

}

- (void) setEventType:(NSMutableString *)eventTypeName{
		eventType = [NSMutableString stringWithString:eventTypeName];
		[eventType retain];
}

- (void) nodeWillRemoveFromGraph{
	NSLog(@"IN SUBCLASS Will remove from graph");
	[self stopReceivingEvents];
	//if ([self connected]) 
		//sleep(1); // This is needed for a clean quit of QC. Otherwise there will be a crash...
	//NSLog(@"Patch was not connected");
//	[eventType release];

	[super nodeWillRemoveFromGraph];
}

- (void) dealloc {
	//[eventType release];
	NSLog(@"In dealloc");
	[super dealloc];
}

@end
