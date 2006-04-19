//
//  InterfaceKitpatch.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "InterfaceKitPatch.h"

@implementation InterfaceKitPatch

- (id)initWithIdentifier:(id)fp8
{
	[self setEventType:[NSMutableString stringWithString:@"PhidgetInterfaceKit"]];
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
	const char* eventType = "PhidgetInterfaceKit";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	int analogPort;
	int portValue;

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
		if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]])
		{
			analogPort = resultEventPtr->getPostValueInt("Index");
			portValue = resultEventPtr->getPostValueInt("Value");
			// Here depending on Index, the corresponding AnalogPortValue must be set.
		
			switch (analogPort) {
			case 0:
				[outputAnalogReading0 setDoubleValue:portValue];
				break;
			case 1:
				[outputAnalogReading1 setDoubleValue:portValue];
				break;
			case 2:
				[outputAnalogReading2 setDoubleValue:portValue];
				break;
			case 3:
			 [outputAnalogReading3 setDoubleValue:portValue];
			 break;
			case 4:
			 [outputAnalogReading4 setDoubleValue:portValue];
			 break;
			case 5:
			 [outputAnalogReading5 setDoubleValue:portValue];
			 break;
			case 6:
			 [outputAnalogReading6 setDoubleValue:portValue];
			break;
			case 7:
			 [outputAnalogReading6 setDoubleValue:portValue];
			break;

			default:
				NSLog(@"Index Value not valid: probably out of bounds");
				break;
			}
		}
	}

	[localPool release];
	
}
*/

- (void) processEvent:(eh2_EventPtr) eventPtr {
	int analogPort = eventPtr->getPostValueInt("Index");
	int portValue = eventPtr->getPostValueInt("Value");
	// Here depending on Index, the corresponding AnalogPortValue must be set.
	switch (analogPort) {
		case 0:
			[outputAnalogReading0 setDoubleValue:portValue];
			break;
		case 1:
			[outputAnalogReading1 setDoubleValue:portValue];
			break;
		case 2:
			[outputAnalogReading2 setDoubleValue:portValue];
			break;
		case 3:
			[outputAnalogReading3 setDoubleValue:portValue];
			break;
		case 4:
			[outputAnalogReading4 setDoubleValue:portValue];
			break;
		case 5:
			[outputAnalogReading5 setDoubleValue:portValue];
			break;
		case 6:
			[outputAnalogReading6 setDoubleValue:portValue];
			break;
		case 7:
			[outputAnalogReading6 setDoubleValue:portValue];
			break;
		default:
			NSLog(@"Index Value not valid: probably out of bounds");
			break;
	}

}


@end
