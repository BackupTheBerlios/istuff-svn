//
//  SweepPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Refactored by RenŽ Reiners on 02/03/06
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "SweepController.h"
#import "string.h"

@implementation SweepController

- (id)initWithIdentifier:(id)fp8
{
	[super initWithIdentifier:fp8];
	
	setOutputPort = false;
	// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"iPhone"];
	[self addTemplateEvent:templateEvent];
	return self;
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
		// the values of relative movement should be reset to zero after each reading
		if (!setOutputPort) {
			[outputdX setDoubleValue:0];
			[outputdY setDoubleValue:0];
			[outputdrZ setDoubleValue:0];
		}
		else {
			setOutputPort = false;
		}
        return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) processEvent:(iStuffEvent *) event {
	int dX, dY;
	double drZ;
	
	//NSLog (@"In PROCESS OUTPUT from patch: %@",[self identifier] );
	// set the flag so that in the 'execute'-method the output port is set to the new value
	// after setting it, the flag is set to false again.
	// This allows posting one value per execution cycle
	setOutputPort = true;
				
	NSLog(@"Received Event");
	const char* type = [[event stringValueForField:@"type"] cString];
//	char* type = (char*) eventPtr->getPostValueString("type");
	if(type != NULL){
		NSLog(@"type has data: %s", type);
		if( strcmp(type, "translation") == 0) {
			dX = [event intValueForField:@"dX"];
			dY = [event intValueForField:@"dY"];
			[outputdX setDoubleValue:dX];
			[outputdY setDoubleValue:dY];
		} 
		else if (strcmp(type, "rotation") == 0) {
			drZ = [event doubleValueForField:@"angle"];;
			[outputdrZ setDoubleValue:drZ];
		} 
		else if (strcmp(type, "click") == 0) {
			const char* state = [[event stringValueForField:@"state"] cString];
			if( strcmp(state, "pressed") == 0)
				[outputClick setBooleanValue:TRUE];
			else
				[outputClick setBooleanValue:FALSE];				
		}
	}
			/*else if (strcmp(type, "code")){
				[code initWithCString:eventPtr->getPostValueString("code") encoding:NSASCIIStringEncoding];
				targetX = eventPtr->getPostValueInt("targetX");
				targetY = eventPtr->getPostValueInt("targetY");
			}*/
}

@end
