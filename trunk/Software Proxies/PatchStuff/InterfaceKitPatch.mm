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

	// definition of the type of event to receive.
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("PhidgetInterfaceKit");

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		int analogPort;
		analogPort = resultEventPtr->getPostValueInt("Index");
		int portValue;
		portValue = resultEventPtr->getPostValueInt("Value");
		// Here depending on Index, the corresponding AnalogPortValue must be set.
		
		switch (analogPort) {
		case 0:
			 [outputAnalogReading0 setDoubleValue:portValue];
			 NSLog(@"Index 0");
			 break;
		case 1:
			 [outputAnalogReading1 setDoubleValue:portValue];
			 NSLog(@"Index 1");
			 break;
		case 2:
			 [outputAnalogReading2 setDoubleValue:portValue];
			 break;
		case	 3:
			 [outputAnalogReading3 setDoubleValue:portValue];
			 break;
		case	 4:
			 [outputAnalogReading4 setDoubleValue:portValue];
			 break;
		case	 5:
			 [outputAnalogReading5 setDoubleValue:portValue];
			 break;
		case	 6:
			 [outputAnalogReading6 setDoubleValue:portValue];
			break;
		case	 7:
			 [outputAnalogReading6 setDoubleValue:portValue];
			break;

		default:NSLog(@"Index Value not valid: probably out of bounds");
			break;
		}
	}

	[localPool release];
}

@end
