//
//  CharacterGeneratorPatch.mm
//  QCiStuff
//
//  Created in by Ren� Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
// This patch waits for "Text Event" from the event heap and directs them
// to the output ports as integers with the ACII code number. As only events are processed, no input ports are needed.

#import "CharacterGenerator.h"

@implementation CharacterGenerator
	
- (id) initWithIdentifier:(id)fp8
{
	[self setEventType:[NSMutableString stringWithString:@"TextEvent"]];
	proxyName = [NSMutableString stringWithString:@"TextEventGenerator_"];
	setOutputPort = false;
	[outputKeyStroke setDoubleValue:-1];
	[outputPermanentASCIICode setDoubleValue:-1];
	return [super initWithIdentifier:fp8];
}
	
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
		// if a new Character Event was received, the code value has to be posted once
		// After posting, the port is set back to the "illegal" value -1
	if (!setOutputPort) {
		[outputKeyStroke setDoubleValue:0];
	}
	else {
		[outputKeyStroke setDoubleValue:[outputKeyStroke doubleValue]];
		setOutputPort = false;
	}
		return [super execute:fp8 time:fp12 arguments:fp20];
}

/*- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];
	
	// define the type of events you want to receive
	const char* eventType = "TextEvent";
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
				// invoke the waitForEvent operation, keep the returned event in a smart pointer
		
				// set the flag so that in the 'execute'-method the output port is set to the new value
				// after setting it, the flag is set to false again.
				// This allows posting one value per execution cycle
				setOutputPort = true;
		
				//read the character ASCII value from the event field
				int keyCode;
				keyCode = resultEventPtr->getPostValueInt("Character");
				[outputKeyStroke setDoubleValue:(double) keyCode];
				[outputPermanentASCIICode setDoubleValue:keyCode];				
			}
		}
			
	[localPool release];
}*/

- (void) processEvent:(eh2_EventPtr) eventPtr{
				//NSLog (@"In PROCESS OUTPUT from patch: %@",[self identifier] );
				// set the flag so that in the 'execute'-method the output port is set to the new value
				// after setting it, the flag is set to false again.
				// This allows posting one value per execution cycle
				NSLog(@"In process Event : %@", [self description]);
				setOutputPort = true;
		
				//read the character ASCII value from the event field
				int keyCode;
				keyCode = eventPtr->getPostValueInt("Character");
				[outputKeyStroke setDoubleValue:(double) keyCode];
				[outputPermanentASCIICode setDoubleValue:keyCode];		
}

@end
