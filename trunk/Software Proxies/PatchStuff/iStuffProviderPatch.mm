//
//  iStuffProviderPatch.mm
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import "iStuffProviderPatch.h"

@implementation iStuffProviderPatch

+ (int)executionMode
{
        // I have found the following execution modes:
        //  1 - Renderer, Environment - pink title bar
        //  2 - Source, Tool, Controller - blue title bar
        //  3 - Numeric, Modifier, Generator - green title bar
        return 2;
}

- (id)initWithIdentifier:(id)fp8
{	
	[self startReceivingEvents];
	return [super initWithIdentifier:fp8];
}

// This method is needed for Provider patches
- (void) startReceivingEvents
{
	// set the flag to activate the thread
	waitForEvents = TRUE;
	// create the thread that waits for events
	[NSThread detachNewThreadSelector:@selector(waitForEvents) toTarget:self withObject:nil];
	NSLog (@"thread waitForEvents activated");
}

- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;	
	NSLog (@"thread waitForEvents deactivated");
}

// thread waiting for EH events, so we won't block the recognition system
// the function call (*eh)->waitForEvent is blocking !
// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
- (void) waitForEvents
{
// This method has to be implemented in a subclass.
}


@end
