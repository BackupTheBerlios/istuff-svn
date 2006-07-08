//
//  InterfaceKitpatch.mm
//  QCiStuff
//
//  Created in by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "InterfaceKit.h"

@implementation InterfaceKit

- (id)initWithIdentifier:(id)fp8
{
	[super initWithIdentifier:fp8];
	
	// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"PhidgetInterfaceKit"];
	[self addTemplateEvent:templateEvent];
	return self;
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) processEvent:(iStuffEvent *) event {
	int analogPort = [event intValueForField:@"Index"];
	int portValue = [event intValueForField:@"Value"];
	// Here depending on Index, the corresponding AnalogPortValue must be set.
	switch (analogPort) {
		case 0:
			[outputAnalogReading0 setDoubleValue:portValue];
			break;
		case 1:
			[outputAnalogReading1 setDoubleValue:portValue];
			break;
		case 2:
			[outputAnalogReading2 setDoubleValue:portValue];
			break;
		case 3:
			[outputAnalogReading3 setDoubleValue:portValue];
			break;
		case 4:
			[outputAnalogReading4 setDoubleValue:portValue];
			break;
		case 5:
			[outputAnalogReading5 setDoubleValue:portValue];
			break;
		case 6:
			[outputAnalogReading6 setDoubleValue:portValue];
			break;
		case 7:
			[outputAnalogReading6 setDoubleValue:portValue];
			break;
		default:
			NSLog(@"Index Value not valid: probably out of bounds");
			break;
	}

}


@end
