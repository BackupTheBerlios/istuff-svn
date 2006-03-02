//
//  iStuffProviderPatch.h
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffPatch.h"


@interface iStuffProviderPatch : iStuffPatch {

	BOOL waitForEvents;
}
 
 + (int)executionMode;
 
 - (id)initWithIdentifier:(id)fp8;
- (void) startReceivingEvents;
- (void) stopReceivingEvents;
- (void) waitForEvents;  // In this method, a Template Event Pointer is defined. The outputs of a patch are set in this thread.
- (void) dealloc;

@end
