//
//  iStuffConsumerPatch.m
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import "iStuffConsumerPatch.h"

@interface iStuffConsumerPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation iStuffConsumerPatch(QCInspector)

+ (Class)inspectorClassWithIdentifier:(id)fp8
{	
	return [iStuffConsumerPatchUI class];
}
@end

@implementation iStuffConsumerPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
        return 1;
}

- (id)initWithIdentifier:(id)fp8 {
	[self setListenToEverything:false]; // This is needed to display the eventID textfield
	return 	[super initWithIdentifier:fp8];
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// Specify the functionality of the patch.
	// The code is executed in each cycle.
	
        // Read/Write any ports in here too.
		if ([self connected]) 
			[self executeCustomPatch];

        return TRUE;
}

- (void) executeCustomPatch {
  // to be implemented
}

//- (void) createNewEventType:(NSString *)eventType {
//	event = [[iStuffEvent alloc] init];
//	[event setEventType:eventType];
//	[event retain];
	//eventPtr = new eh2_EventPtr;
	//(*eventPtr) = eh2_Event::cs_create ([eventType cString]);
//}

@end
