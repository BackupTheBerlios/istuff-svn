//
//  iStuffProviderPatch.mm
//  QCiStuff
//
//  Created by René Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#include  "iStuffProviderPatch.h"

@implementation iStuffProviderPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
        return 2;
}

- (id)initWithIdentifier:(id)fp8
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(startReceivingEvents) name:@"EventHeapListChanged" object:nil];
	return [super initWithIdentifier:fp8];
	
}

// This method is needed for Provider patches
- (void) startReceivingEvents
{
	// set the flag to activate the thread
	waitForEvents = TRUE;
	// create the thread that waits for events
	[NSThread detachNewThreadSelector:@selector(waitForEvents) toTarget:self withObject:nil];
	// We need threads that can manuall be killed. That might be the soultion to the waitForEvent problem.
}



- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;	 
	if ((eh != nil)  && ([self connected])){
		//create a new event object
		eh2_EventPtr *eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("DUMMY");
		(*eventPtr)->setPostValueInt("TimeToLive", 150);
		(*eh)->putEvent(*eventPtr);
	}
	sleep(1);
}

// thread waiting for EH events, so we won't block the recognition system
// the function call (*eh)->waitForEvent is blocking !
// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
- (void) waitForEvents
{
// This method has to be implemented in a subclass.
}

- (void) nodeWillRemoveFromGraph{
	[self stopReceivingEvents];
	//sleep(1); // This is needed for the thread to exit. Otherwise dealloc won't be called.
	[super nodeWillRemoveFromGraph];
}

@end
