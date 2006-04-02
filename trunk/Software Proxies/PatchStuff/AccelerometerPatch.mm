//
//  AccelerometerPatch.mm
//  QCiStuff
//
//  Created in by Ren� Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "AccelerometerPatch.h"

@implementation AccelerometerPatch

- (id)initWithIdentifier:(id)fp8
{	
	proxyName = [NSMutableString stringWithString:@"Accelerometer_"];
	return [super initWithIdentifier:fp8];
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];

	// define the type of events you want to receive
	const char* eventType = "PhidgetAccelerometer";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
		
	if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]]){
			char* acceleration = (char*) resultEventPtr->getPostValueString("Acceleration");
			[outputAcceleration setStringValue:[NSString stringWithCString:acceleration]];
		}
	}

	[localPool release];
	NSLog(@"WAITFOREVENTS REALLY QUIT IN ACCELEROMETER");
}

@end
