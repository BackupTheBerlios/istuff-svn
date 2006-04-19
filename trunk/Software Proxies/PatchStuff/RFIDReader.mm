//
//  RFIDReader.m
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "RFIDReader.h"

@interface RFIDReader (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation RFIDReader
	
- (id)initWithIdentifier:(id)fp8
{
	[self setEventType:[NSMutableString stringWithString:@"PhidgetRFID"]];
	[outputTag setStringValue:nil];
	return [super initWithIdentifier:fp8];
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

/*
- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];

	// define the type of events you want to receive
	const char* eventType = "PhidgetsRFID";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
		if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]])
		{
			char* taggie = (char*) resultEventPtr->getPostValueString("TagNumber");
			[outputTag setStringValue:[NSString stringWithCString:taggie]];
		}
	}	
	
	[localPool release];
	NSLog(@"The thread actually ended");
}
*/

- (void) processEvent:(eh2_EventPtr) eventPtr {
NSLog(@"In process Event Tag Reader");
	char* taggie = (char*) eventPtr->getPostValueString("TagNumber");
	[outputTag setStringValue:[NSString stringWithCString:taggie]];
}


@end
