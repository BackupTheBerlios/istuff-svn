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
	[super initWithIdentifier:fp8];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(startReceivingEvents) name:@"EventHeapListChanged" object:nil];
	templateEvents = [[NSMutableArray alloc] initWithCapacity:2];
	iStuffEvent *dummyEvent = [[iStuffEvent alloc] initWithType:@"DUMMY"];
	[dummyEvent addNewTemplateValueInt:@"ObjectID" intValue:[self hash]];
	[self addTemplateEvent:dummyEvent];
	return self;
}

// This method is needed for Provider patches
- (void) startReceivingEvents
{
	// set the flag to activate the thread
	waitForEvents = TRUE;
	readyToReconnect = FALSE;
	// create the thread that waits for events
	[NSThread detachNewThreadSelector:@selector(waitForEvents) toTarget:self withObject:nil];
}

//this method sends a specific dummy that is only picked up by the appropriate patch
// Otherwise crashes occur due to synchronisation errors caused by all patches reacting on the same event


- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;	 
	if ((eh != nil)  && ([self connected]) ){
		//create a new event object
		iStuffEvent *dummyToStop = [[iStuffEvent alloc]  initWithTypeAndID:@"DUMMY" eventID:@""];
		//[dummyToStop setTimeToLive:1000];
		[dummyToStop addNewIntegerField:@"ObjectID" intValue:[self hash]];
		[dummyToStop setTimeToLive:200];
		[dummyToStop postEvent:eh];
		//sleep(1);  // IF CRASHES OCCUR WHILE CHANGING THE EVENT HEAPS, MAKE USE OF SLEEP AGAIN.
	}
}

- (void) addTemplateEvent:(iStuffEvent *) event{
	[templateEvents addObject:event];
	[templateEvents retain];
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
	
	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();
	// loop to find all templates to wait for
    NSEnumerator *enumerator = [templateEvents objectEnumerator];
	iStuffEvent *currentEvent;

	while (currentEvent = [enumerator nextObject]) {
		eh2_EventPtr pointer = [currentEvent eventPointer];
		eventsToWaitFor->add(pointer);
	}
	//eh2_EventPtr dummyPtr = eh2_Event::cs_create();
	//dummyPtr->setEventType("DUMMY"); // yet another way to set event type
	//dummyPtr->setTemplateValueString("ObjectID", [[self description] cString]); 
	//eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
				
		//check wether one of the received event types is in the template list		
		NSString *receivedEventType = [NSString stringWithCString:resultEventPtr->getEventType()];
		NSEnumerator *enumerator = [templateEvents objectEnumerator];
		iStuffEvent *currentEvent;
		while (currentEvent = [enumerator nextObject]) {
			if ( (![receivedEventType isEqualToString:@"DUMMY"]) && ([[currentEvent eventType] isEqualToString:receivedEventType])) {
			// Check if the event is for the current patch
			iStuffEvent *receivedEvent = [[iStuffEvent alloc] initWithPointer:resultEventPtr];
				if([self listenToEverything] == NSOnState){
					[self processEvent:receivedEvent];
				}else{
				if ([[receivedEvent eventID] isEqualToString:[self eventID]]) {
					[self processEvent:receivedEvent];
					}
				}
			}
		} 
	}
	// This log message is still included to make check whether the threads that wait for events quit properly
	NSLog(@"WAITFOREVENTS REALLY QUIT IN %@", self);
	readyToReconnect = TRUE;
	[localPool release];
	
}

- (void) processEvent:(iStuffEvent *) event{
  // To be implemented in subclasses
}

- (void) setTemplateType:(NSMutableString *)typeName{
		*templatePtr = eh2_Event::cs_create ([typeName cString]);
		//eventType = [NSMutableString stringWithString:eventTypeName];
		[templateType retain]; 
}

- (void) nodeWillRemoveFromGraph{
	[self stopReceivingEvents];
	[templateType release];
	[templateEvents release];
	[super nodeWillRemoveFromGraph];
}

@end
