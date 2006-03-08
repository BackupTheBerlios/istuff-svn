//
//  CharacterGeneratorPatch.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
// This patch waits for "Text Event" from the event heap and directs them
// to the output ports as integers with the ACII code number. As only events are processed, no input ports are needed.

#import "CharacterGeneratorPatch.h"

@implementation CharacterGeneratorPatch
	
- (id) initWithIdentifier:(id)fp8
{
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

- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];
	
	// define the type of events you want to receive
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("TextEvent");

	// the thread exits if waitForEvents becomes FALSE
	while (waitForEvents) {

		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		
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
	
	[localPool release];
}

@end
