//  ProcessorPatchTemplate.h
//  QCiStuff
//
//  Created by Rene Reiners on 3/2/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

// This patch is a template.
// Fill the method stubs with custom funcitonality.

#import <Cocoa/Cocoa.h>
#import "iStuffProcessorPatch.h"

// name for your custom class has to replace the template name
@interface ProcessorPatchTemplate : iStuffProcessorPatch {

// Define member variables and input / output ports here

}

- (id)initWithIdentifier:(id)fp8; // Initialization when patch instance is created.
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20; // code executed with every patch execution cycle

@end

