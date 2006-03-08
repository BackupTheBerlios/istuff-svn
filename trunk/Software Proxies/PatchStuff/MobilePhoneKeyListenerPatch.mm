//
//  MobilePhoneKeyListenerPatch.m
//  QCiStuff
//
//  Created by RenŽ Reiners in winter 2005/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhoneKeyListenerPatch.h"

@implementation MobilePhoneKeyListenerPatch

- (id)initWithIdentifier:(id)fp8
{	
	setOutputPort = false;
	[outputKeyStroke setDoubleValue:-1];
	
	return [super initWithIdentifier:fp8];
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

- (void) waitForEvents
{
	 NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];	

	// specify your event template here:
	eh2_EventPtr templatePtr = eh2_Event::cs_create();
	templatePtr->setEventType ("iStuffMobile");
	
	eh2_Field* field;
	field = templatePtr->allocateField("Activity", eh2_FieldType::cs_string());
	field->setTemplateValueType(eh2_EventConsts::FVT_FORMAL);
	
	while (waitForEvents) {
	eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);

	// set the flag so that in the 'execute'-method the output port is set to the new value
	// after setting it, the flag is set to false again.
	// This allows posting one value per execution cycle
		const char* activity = resultEventPtr->getPostValueString("Activity");
		NSLog(@"The String was read and is checked now: %s", activity);
		if ([@"KeyDown" isEqualToString:[NSString stringWithUTF8String:activity]]) {
			[outputKeyPressed setBooleanValue:true];
		}
		
		if ([@"KeyPress" isEqualToString:[NSString stringWithUTF8String:activity]]) {
			//read the character ASCII value from the event field
			NSLog(@"In keyPress");
			setOutputPort = true;
			keyCode = resultEventPtr->getPostValueInt("KeyCode");
			[outputKeyStroke setDoubleValue:(double) keyCode];
		}
		
		if ([@"KeyUp" isEqualToString:[NSString stringWithUTF8String:activity]]) {
		 NSLog(@"In keyUp");
			[outputKeyPressed setBooleanValue:false];
		}
	}
	
	[localPool release];
}
	
@end
