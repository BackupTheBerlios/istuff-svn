//
//  AccelerometerPatch.mm
//  QCiStuff
//
//  Created in by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "Accelerometer.h"

@implementation Accelerometer

- (id)initWithIdentifier:(id)fp8
{	
	[super initWithIdentifier:fp8];
	
	// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"PhidgetAccelerometer"];
	[self addTemplateEvent:templateEvent];
	return self;
}
	
- (void) processEvent:(iStuffEvent *) event {
	[outputX setStringValue:[event stringValueForField:@"X"]];
	[outputY setStringValue:[event stringValueForField:@"Y"]];
}

@end
