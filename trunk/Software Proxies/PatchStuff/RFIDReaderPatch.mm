//
//  RFIDReader.m
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "RFIDReaderPatch.h"

@interface RFIDReaderPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation RFIDReaderPatch
	
- (id)initWithIdentifier:(id)fp8
{
	[outputTag setStringValue:nil];
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
	templatePtr->setEventType ("PhidgetRFID");
	while (waitForEvents) {
	// specify your event template here:
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		NSLog(@"Event Received");
		char* taggie = (char*) resultEventPtr->getPostValueString("TagNumber");

		[outputTag setStringValue:[NSString stringWithCString:taggie]];
		NSLog([NSString stringWithCString:taggie]);
	}
	
	[localPool release];
	NSLog(@"The thread actually ended");
}

@end
