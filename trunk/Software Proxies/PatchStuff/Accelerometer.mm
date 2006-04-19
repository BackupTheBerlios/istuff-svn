//
//  AccelerometerPatch.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "Accelerometer.h"

@implementation Accelerometer

- (id)initWithIdentifier:(id)fp8
{	
	[self setEventType:[NSMutableString stringWithString:@"PhidgetAccelerometer"]];
	return [super initWithIdentifier:fp8];
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}
/*
- (void) waitForEvents:(NSString *)eventID
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];

	// define the type of events you want to receive
	const char* eventType = "PhidgetAccelerometer"; // This should be a member variable
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	(*templatePtr)->setPostValueString([eventID cString]);		

	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");
	(*eventPtr)->setPostValueString([eventID cString]);		

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
		// Check if the event is for the current patch
		NSString *reveivedEventID = [NSString stringWithCString:resultEventPtr->getPostValueString("ProxyID")];
		NSString *receivedEventType = [NSString stringWithCString:resultEventPtr->getEventType()];
		NSLog (@"THE RECEIVED EVENT ID IS: %@", receivedEventID);
				
		if ( ([receivedEventID isEqualToString:eventID]) && ([receivedEventType isEqualToString:[NSString stringWithCString:eventType]]) ) {
		// Here call the custom method in the subclass
		// **** Method Call *********** // Maybe with the same name "Event Processing or something
		if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]]){
				char* acceleration = (char*) resultEventPtr->getPostValueString("Acceleration");
				[outputAcceleration setStringValue:[NSString stringWithCString:acceleration]];
		}
	}

	[localPool release];
	NSLog(@"WAITFOREVENTS REALLY QUIT IN ACCELEROMETER");
}
*/

- (void) processEvent:(eh2_EventPtr) eventPtr {
NSLog(@" ACCEL PROCESSES EVENT");
	char* acceleration = (char*) eventPtr->getPostValueString("Acceleration");
	[outputAcceleration setStringValue:[NSString stringWithCString:acceleration]];
}

@end
