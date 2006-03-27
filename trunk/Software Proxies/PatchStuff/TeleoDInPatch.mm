//
//  TeleoDInPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Refactored by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "TeleoDInPatch.h"

@implementation TeleoDInPatch

- (id)initWithIdentifier:(id)fp8
{
	return [super initWithIdentifier:fp8];
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

// deactivate the thread that waits for Event Heap events
//
- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;
}

- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];

	// define the type of events you want to receive

	const char* eventType = "TeleoDIn";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	int x, y, z;

	while (waitForEvents) 
	{
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);

		if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]])
		{
		
			x = resultEventPtr->getPostValueInt("X");
			y = resultEventPtr->getPostValueInt("Y");
			z = resultEventPtr->getPostValueInt("Z");
			
			[outputX setDoubleValue:x];
			[outputY setDoubleValue:y];
			[outputZ setDoubleValue:z];

		// print debug info
		//const char* field1, *field2;
		//field1 = resultEventPtr->getPostValueString ("SequenceNum");
		//field2 = resultEventPtr->getPostValueString ("SessionID");
		//NSLog (@"event received, seqNum %s, sessID %s", field1, field2);

		// report the received event to MyController
		//[myController processEvent:resultEventPtr];
		}
	}

	[localPool release];
}

@end
