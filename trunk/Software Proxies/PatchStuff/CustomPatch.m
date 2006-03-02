//
//  CustomPatch.m
//  QCiStuff
//
//  Created by Rene Reiners on 3/2/06.
//  Copyright 2006 Media Computing Group RWTH Aachen, Germany. All rights reserved.
//

#import "CustomPatch.h"

@interface CustomPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation CustomPatch(QCInspector)

+ (Class)inspectorClassWithIdentifier:(id)fp8
{	
	return [CustomPatchUI class];
}
@end


@implementation CustomPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
		return nil;
}
	
+ (BOOL)allowsSubpatches
{
        // If your patch is a parent patch, like 3D Transformation,
        // you will allow subpatches, otherwise FALSE.
	return FALSE;
}

- (id) initWithIdentifier:(id)fp8{
	// Initialization of variables takes place here
	return [super initWithIdentifier:fp8];
}

- (id)setup:(id)fp8
{
  // fp8 is the QCOpenGLContext
	// setup vars here
        return fp8;
}
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// This is where the execution of your patch happens.
        // Everything in this method gets executed once
        // per 'clock cycle', which is available in fp12 (time).
	
        // fp8 is the QCOpenGLContext*.  Don't forget to set
        // it before you start drawing.  
	
        // Read/Write any ports in here too.
		
        return TRUE;
}

- (void) dealloc{
	[super dealloc];
}

@end
