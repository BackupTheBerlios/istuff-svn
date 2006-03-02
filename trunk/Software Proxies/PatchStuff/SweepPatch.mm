//
//  SweepPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Refactored by RenŽ Reiners on 02/03/06
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "SweepPatch.h"
#import "string.h"

@implementation SweepPatch

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

	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];
	
	// define the type of events you want to receive
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("iPhone");
	
	int dX, dY;
	double drZ;
	
	while (waitForEvents) {
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		
		NSLog(@"Received Event");
		char* type = (char*) resultEventPtr->getPostValueString("type");
	
		if(type != NULL){
			NSLog(@"type has data: %s", type);
			if( strcmp(type, "translation") == 0){
				dX = resultEventPtr->getPostValueInt("dX");
				dY = resultEventPtr->getPostValueInt("dY");
				[outputdX setDoubleValue:dX];
				[outputdY setDoubleValue:dY];
			} else if (strcmp(type, "rotation") == 0){
				drZ = resultEventPtr->getPostValueDouble("angle");
				[outputdrZ setDoubleValue:drZ];
			} else if (strcmp(type, "click") == 0){
				char* state = (char*) resultEventPtr->getPostValueString("state");
				if( strcmp(state, "pressed") == 0){
					[outputClick setBooleanValue:TRUE];
				}else{
					[outputClick setBooleanValue:FALSE];				
				}
				
			} 
			/*else if (strcmp(type, "code")){
				[code initWithCString:resultEventPtr->getPostValueString("code") encoding:NSASCIIStringEncoding];
				targetX = resultEventPtr->getPostValueInt("targetX");
				targetY = resultEventPtr->getPostValueInt("targetY");
			}*/
		}
		
	}

	[localPool release];
}

@end
