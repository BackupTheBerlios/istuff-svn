//
//  PowerbookTiltSensorPatch.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Modified and refactored by Ren� Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "PowerbookTiltSensorPatch.h"

@implementation PowerbookTiltSensorPatch
	
- (id)initWithIdentifier:(id)fp8
{
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
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("Powerbook_Tilt");
	
	int x, y, z;
	while (waitForEvents) {
		
		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);

		x = resultEventPtr->getPostValueInt("X");
		y = resultEventPtr->getPostValueInt("Y");
		z = resultEventPtr->getPostValueInt("Z");
		
		[outputX setDoubleValue:x];
		[outputY setDoubleValue:y];
		[outputZ setDoubleValue:z];
	}
	
	[localPool release];
}
	
@end
