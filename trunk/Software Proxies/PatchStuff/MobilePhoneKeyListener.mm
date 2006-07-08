//
//  MobilePhoneKeyListener.mm
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhoneKeyListener.h"
#include <eh2.h> // include eh2 package
#include <idk_io.h> // include idk_io package

@implementation MobilePhoneKeyListener

- (id)initWithIdentifier:(id)fp8
{	
	[super initWithIdentifier:fp8];
	setOutputPort = false;
	[outputKeyStroke setDoubleValue:-1];
	
	// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"iStuffMobile"];
	[templateEvent addNewStringTemplateField:@"Activity"];
	[self addTemplateEvent:templateEvent];
	return self;
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	if (!setOutputPort) {
		[outputKeyStroke setDoubleValue:0];
	}
	else {
		[outputKeyStroke setDoubleValue:(double)keyCode];
		setOutputPort = false;
	}
	
	return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) processEvent:(iStuffEvent *) event{

// set the flag so that in the 'execute'-method the output port is set to the new value
			// after setting it, the flag is set to false again.
			// This allows posting one value per execution cycle
			
			// first check to see that the Activity field exists
//			const eh2_Field* field = eventPtr->getField("Activity");
			NSString *activity = [event stringValueForField:@"Activity"];
			if (activity != nil) {
				//const char* activity = eventPtr->getPostValueString("Activity");
				if ([@"KeyDown" isEqualToString: activity]) {
					[outputKeyPressed setBooleanValue:true];
				}
		
				if ([@"KeyPress" isEqualToString: activity]) {
					//read the character ASCII value from the event field
					NSLog(@"In keyPress");
					setOutputPort = true;
					//make sure that the KeyCode field exists
//					const eh2_Field* field = eventPtr->getField("KeyCode");
//					if (field != NULL) {
					
						keyCode = [event intValueForField:@"KeyCode"];
						[outputKeyStroke setDoubleValue:(double) keyCode];
					}
				}
			
				if ([@"KeyUp" isEqualToString:activity]) {
					NSLog(@"In keyUp");
					[outputKeyPressed setBooleanValue:false];
				}
			// else ignore the event, not intended for us (possibly an output of the MobilePhone.mm)
}
	
@end
