//
//  PowerbookTiltSensorPatch.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Modified and refactored by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "PowerbookTiltSensorPatch.h"

@implementation PowerbookTiltSensorPatch
	
- (id)initWithIdentifier:(id)fp8
{
	proxyName = [NSMutableString stringWithString:@"PowerbookTiltSensor"];
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
	
	int x, y, z;
	// define the type of events you want to receive
	const char* eventType = "Powerbook_Tilt";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

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
		}
	}
	
	[localPool release];
}
	
@end
