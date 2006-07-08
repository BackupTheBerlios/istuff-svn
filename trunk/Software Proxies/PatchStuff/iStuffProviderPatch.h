//
//  iStuffProviderPatch.h
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffPatch.h"
#import <Foundation/Foundation.h>
#import <eh2.h>
#import <idk_io.h>
#import "QCPatch.h"
#include <unistd.h>


@interface iStuffProviderPatch : iStuffPatch {
	
	eh2_EventPtr *templatePtr;
	NSMutableString *templateType;
	NSMutableArray *templateEvents;
	BOOL waitForEvents;
}
 
 + (int)executionMode;
 
- (id)initWithIdentifier:(id)fp8;
- (void) startReceivingEvents;
- (void) stopReceivingEvents;
- (void) waitForEvents;  // In this method, a Template Event Pointer is defined. The outputs of a patch are set in this thread.
- (void) nodeWillRemoveFromGraph;

- (void) addTemplateEvent:(iStuffEvent *) event;

// Method in which the received Event is processed
- (void) setTemplateType:(NSMutableString *)typeName;
- (void) processEvent:(iStuffEvent *) event;

@end
