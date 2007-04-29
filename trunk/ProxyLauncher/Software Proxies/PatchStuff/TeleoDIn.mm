//
//  TeleoDInPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Refactored by Ren� Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "TeleoDIn.h"

@implementation TeleoDIn

- (id)initWithIdentifier:(id)fp8 
{
	[super initWithIdentifier:fp8];

	// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"TeleoDIn"];
	[self addTemplateEvent:templateEvent];
	return self;
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

// deactivate the thread that waits for Event Heap events
//
- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;
}

- (void) processEvent:(iStuffEvent *) event 
{
	[outputX setDoubleValue:[event intValueForField:@"X"]];
	[outputY setDoubleValue:[event intValueForField:@"Y"]];
	[outputZ setDoubleValue:[event intValueForField:@"Z"]];
}


@end
