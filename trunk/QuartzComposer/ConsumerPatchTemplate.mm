//
//
//  ConsumerPatchTemplate.mm
//  QCiStuff
//
//  Created by Rene Reiners on 3/2/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

// This patch is a template.
// Fill the method stubs with custom funcitonality.

#import "ConsumerPatchTemplate.h"


@implementation ConsumerPatchTemplate

/*
Only change the UI class if there is a new UI file attached.
Otherwise a standard iStuffUI class will be taken.

@interface ConsumerPatchTemplate (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation ConsumerPatchTemplate (QCInspector)

+ (Class)inspectorClassWithIdentifier:(id)fp8
{	
	return [CustomUI class];
}

@end
*/

- (id)initWithIdentifier:(id)fp8
{	
	return [super initWithIdentifier:fp8];
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// Before blind creation of an Event Pointer, the patch has to be connected.
	
	// To ensure this, the code should be surrounded with 
	
	if ([self connected]){
	
	}
	return [super execute:fp8 time:fp12 arguments:fp20];
}

@end
