//
//  SweepPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Refactored by RenŽ Reiners on 02/03/06
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "SweepPatch.h"
#import "string.h"

@implementation SweepPatch

- (id)initWithIdentifier:(id)fp8
{
	[self setEventType:[NSMutableString stringWithString:@"iPhone"]];
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
	
	int dX, dY;
	double drZ;
		
	// define the type of events you want to receive
	const char* eventType = "iPhone";
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
			NSLog(@"Received Event");
			char* type = (char*) resultEventPtr->getPostValueString("type");
	
			if(type != NULL){
				NSLog(@"type has data: %s", type);
				if( strcmp(type, "translation") == 0)
				{
					dX = resultEventPtr->getPostValueInt("dX");
					dY = resultEventPtr->getPostValueInt("dY");
					[outputdX setDoubleValue:dX];
					[outputdY setDoubleValue:dY];
				} 
				else if (strcmp(type, "rotation") == 0)
				{
					drZ = resultEventPtr->getPostValueDouble("angle");
					[outputdrZ setDoubleValue:drZ];
				} 
				else if (strcmp(type, "click") == 0)
				{
					char* state = (char*) resultEventPtr->getPostValueString("state");
					if( strcmp(state, "pressed") == 0){
						[outputClick setBooleanValue:TRUE];
				}
				else
					[outputClick setBooleanValue:FALSE];				
				}
			}
			/*else if (strcmp(type, "code")){
				[code initWithCString:resultEventPtr->getPostValueString("code") encoding:NSASCIIStringEncoding];
				targetX = resultEventPtr->getPostValueInt("targetX");
				targetY = resultEventPtr->getPostValueInt("targetY");
			}*/
/*		}
	}

	[localPool release];
}
*/

- (void) processEvent:(eh2_EventPtr) eventPtr {
	int dX, dY;
	double drZ;
	
	NSLog(@"Received Event");
	char* type = (char*) eventPtr->getPostValueString("type");
	if(type != NULL){
		NSLog(@"type has data: %s", type);
		if( strcmp(type, "translation") == 0) {
			dX = eventPtr->getPostValueInt("dX");
			dY = eventPtr->getPostValueInt("dY");
			[outputdX setDoubleValue:dX];
			[outputdY setDoubleValue:dY];
		} 
		else if (strcmp(type, "rotation") == 0) {
			drZ = eventPtr->getPostValueDouble("angle");
			[outputdrZ setDoubleValue:drZ];
		} 
		else if (strcmp(type, "click") == 0) {
			char* state = (char*) eventPtr->getPostValueString("state");
			if( strcmp(state, "pressed") == 0)
				[outputClick setBooleanValue:TRUE];
			else
				[outputClick setBooleanValue:FALSE];				
		}
	}
			/*else if (strcmp(type, "code")){
				[code initWithCString:eventPtr->getPostValueString("code") encoding:NSASCIIStringEncoding];
				targetX = eventPtr->getPostValueInt("targetX");
				targetY = eventPtr->getPostValueInt("targetY");
			}*/
}

@end
