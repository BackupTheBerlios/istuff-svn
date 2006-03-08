//
//  AccelerometerPatch.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "AccelerometerPatch.h"

@implementation AccelerometerPatch

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
	templatePtr->setEventType ("PhidgetAccelerometer");

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		char* acceleration = (char*) resultEventPtr->getPostValueString("Acceleration");;
		[outputAcceleration setStringValue:[NSString stringWithCString:acceleration]];
	}

	[localPool release];
	NSLog(@"WAITFOREVENTS REALLY QUIT");
}

@end
