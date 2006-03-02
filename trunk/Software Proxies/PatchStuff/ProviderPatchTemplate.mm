//
//
//  ProviderPatchTemplate.mm
//  QCiStuff
//
//  Created by Rene Reiners on 3/2/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

// This patch is a template.
// Fill the method stubs with custom funcitonality.

#import "ProviderPatchTemplate.h"


@implementation ProviderPatchTemplate

/*
Only change the UI class if there is a new UI file attached.
Otherwise a standard iStuffUI class will be taken.

@interface ProviderPatchTemplate (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation ProviderPatchTemplate(QCInspector)

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
	return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) waitForEvents
{
	 NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];	

	// definition of the type of event to receive.
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("EventTemplate that should be received");

	while (waitForEvents) {		
		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		
		// specify funtionality here, e.g. set output ports according to event information.
	}

	[localPool release];
}

@end
