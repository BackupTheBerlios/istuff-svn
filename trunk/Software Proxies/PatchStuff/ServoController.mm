//
//  ServoControllerPatch.mm
//  QCiStuff
//
//  Created by Ren� Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "ServoControllerPatch.h"
//#import "GFList.h"
//#import "GFNode.h"

@implementation ServoControllerPatch

- (id)initWithIdentifier:(id)fp8
{
	// Set the ProxyName the name of the patch
	proxyName = [NSMutableString stringWithString:@"ServoController_"];
	return [super initWithIdentifier:fp8];
}
	
- (void) executeCustomPatch {
	//	NSLog(@"VALUE: %@",[_inputPorts objectAtIndex:1]);
	/*	//[_inputPorts removeObjectAtIndex:3];
		NSLog (@"Maybe keys: %@", [_inputPorts objectForKey:@"inputProxyID"]);
			NSLog (@"Maybe keys: %@", [_inputPorts objectForKey:@"inputProxyID"]);
		// So the key parameter is an NSString
		// The first parameter in the add method is a QCPort.
		// The question is how to pass it...
	// getting closer. Does not work properly yet
	QCStringPort *testport;// = [QCStringPort init]; // it still has to be instantiated
		[_inputPorts addObject:[testport init] forKey:[_inputPorts keyAtIndex:1]];
*/

	//QCPort *test;
	//[test initWithNode:[self patch] arguments:nil];
	//NSLog (@"The key is: %@",[inputProxyID key]);
//	if ([self connected]) {
		// Only if one of the input ports changed, a new event has to be posted
		// and the other operations have to be performed
				int motor1Position = (int) [inputPosMot1 doubleValue];
				int motor2Position = (int) [inputPosMot2 doubleValue];
				int motor3Position = (int) [inputPosMot3 doubleValue];
				int motor4Position = (int) [inputPosMot4 doubleValue];

			if ((oldMotor1Position != [inputPosMot1 doubleValue]) ||
			    (oldMotor2Position != [inputPosMot2 doubleValue]) ||
				(oldMotor3Position != [inputPosMot3 doubleValue]) ||
				(oldMotor4Position != [inputPosMot4 doubleValue]))
				{
							
				//create a new event object
				eh2_EventPtr *eventPtr = new eh2_EventPtr;
				(*eventPtr) = eh2_Event::cs_create ("ServoController");

			// The controller is able to control 4 different motors
			// The acceleration and speed of each motor can be controlled
			// Therefore everytime an event is posted, two fields for each motor are posted 
			// inside the event. This results in 8  fields.
			
			// Conversion for the input values:
			// In order to protect the servos, position values
			//may only range from 30 to 215
							
				if ( motor1Position < 30) {motor1Position = 30;};
				if ( motor2Position < 30) {motor2Position = 30;};
				if ( motor3Position < 30) {motor3Position = 30;};
				if ( motor4Position < 30) {motor4Position = 30;};
				if ( motor1Position > 215) {motor1Position = 215;};
				if ( motor2Position > 215) {motor2Position = 215;};
				if ( motor3Position > 215) {motor3Position = 215;};
				if ( motor4Position > 215) {motor4Position = 215;};
				
				(*eventPtr)->setPostValueInt("PosMot1", motor1Position);
				(*eventPtr)->setPostValueInt("PosMot2", motor2Position);
				(*eventPtr)->setPostValueInt("PosMot3", motor3Position);
				(*eventPtr)->setPostValueInt("PosMot4", motor4Position);
			
			// the "event package" is ready -> post it to the Event Heap
				(*eventPtr)->setPostValueInt("TimeToLive", 50);
				(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
				(*eh)->putEvent (*eventPtr);
				delete eventPtr;

			// keep the old values and only post a new event if an input really changes! :)
			oldMotor1Position = [inputPosMot1 doubleValue];
			oldMotor2Position = [inputPosMot2 doubleValue];
			oldMotor3Position = [inputPosMot3 doubleValue];
			oldMotor4Position = [inputPosMot4 doubleValue];
			}
	}

@end