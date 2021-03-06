//
//  iStuffConsumerPatch.h
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffPatch.h"
#import "iStuffConsumerPatchUI.h"	


@class iStuffConsumerPatchUI;

@interface iStuffConsumerPatch : iStuffPatch {

	// Global Event pointer
	
	eh2_EventPtr *eventPtr;
	//iStuffEvent *event;
}

+ (int)executionMode;

- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
- (void) executeCustomPatch;
//- (void) createNewEvent:(NSString *)eventType;


@end
