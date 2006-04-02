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
	proxyName = [NSMutableString stringWithString:@"MobilePhoneController_"];
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
	const char* eventType = "iStuffMobile";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	templatePtr->allocateField("Activity", eh2_FieldType::cs_string());
	//FVT_FORMAL means wildcard value, as long as the Activity field exists, the template is matched
	templatePtr->setTemplateValueType("Activity", eh2_Consts::FVT_FORMAL);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);
		
		if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]])
		{
			// set the flag so that in the 'execute'-method the output port is set to the new value
			// after setting it, the flag is set to false again.
			// This allows posting one value per execution cycle
			// This line causes others to crash
			const char* activity = resultEventPtr->getPostValueString("Activity");
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
	}
	
	[localPool release];
}
	
@end
