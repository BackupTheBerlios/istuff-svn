//
//  iStuffConsumerPatch.m
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import "iStuffConsumerPatch.h"

@implementation iStuffConsumerPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
        return 1;
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// Specify the functionality of the patch.
	// The code is executed in each cycle.
	
        // Read/Write any ports in here too.
		
        return TRUE;
}
@end
