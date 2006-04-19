//
//  MobilePhoneKeyListenerPatch.m
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhoneKeyListenerPatch.h"
#include <eh2.h> // include eh2 package
#include <idk_io.h> // include idk_io package

@implementation MobilePhoneKeyListenerPatch

- (id)initWithIdentifier:(id)fp8
{	
	[self setEventType:[NSMutableString stringWithString:@"iStuffMobile"]];
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

- (void) processEvent:(eh2_EventPtr) eventPtr{

// set the flag so that in the 'execute'-method the output port is set to the new value
			// after setting it, the flag is set to false again.
			// This allows posting one value per execution cycle
			// This line causes others to crash
			const char* activity = eventPtr->getPostValueString("Activity");
			if ([@"KeyDown" isEqualToString:[NSString stringWithUTF8String:activity]]) {
				[outputKeyPressed setBooleanValue:true];
			}
		
			if ([@"KeyPress" isEqualToString:[NSString stringWithUTF8String:activity]]) {
				//read the character ASCII value from the event field
				NSLog(@"In keyPress");
				setOutputPort = true;
				keyCode = eventPtr->getPostValueInt("KeyCode");
				[outputKeyStroke setDoubleValue:(double) keyCode];
			}
		
			if ([@"KeyUp" isEqualToString:[NSString stringWithUTF8String:activity]]) {
				NSLog(@"In keyUp");
				[outputKeyPressed setBooleanValue:false];
			}
}
	
@end
