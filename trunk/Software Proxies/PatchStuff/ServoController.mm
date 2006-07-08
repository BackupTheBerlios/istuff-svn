//
//  ServoControllerPatch.mm
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "ServoController.h"

@implementation ServoController
	
- (void) executeCustomPatch {

	int motor1Position = (int) [inputPosMot1 doubleValue];
	int motor2Position = (int) [inputPosMot2 doubleValue];
	int motor3Position = (int) [inputPosMot3 doubleValue];
	int motor4Position = (int) [inputPosMot4 doubleValue];

	if ((oldMotor1Position != [inputPosMot1 doubleValue]) ||
		(oldMotor2Position != [inputPosMot2 doubleValue]) ||
		(oldMotor3Position != [inputPosMot3 doubleValue]) ||
		(oldMotor4Position != [inputPosMot4 doubleValue])) {
								
			iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"ServoController" eventID:[self eventID]];
			[event setTimeToLive:50];
									
			// The controller is able to control 4 different motors
			// The acceleration and speed of each motor can be controlled
			// Therefore everytime an event is posted, two fields for each motor are posted 
			// inside the event. This results in 8  fields.
			
			// Conversion for the input values:
			// In order to protect the servos, position values
			//may only range from 30 to 215
							
			if ( motor1Position < 30) {motor1Position = 35;};
			if ( motor2Position < 30) {motor2Position = 35;};
			if ( motor3Position < 30) {motor3Position = 35;};
			if ( motor4Position < 30) {motor4Position = 35;};
			if ( motor1Position > 215) {motor1Position = 215;};
			if ( motor2Position > 215) {motor2Position = 215;};
			if ( motor3Position > 215) {motor3Position = 215;};
			if ( motor4Position > 215) {motor4Position = 215;};
				
			[event addNewIntegerField:@"PosMot1" intValue:motor1Position];
			[event addNewIntegerField:@"PosMot2" intValue:motor2Position];
			[event addNewIntegerField:@"PosMot3" intValue:motor3Position];
			[event addNewIntegerField:@"PosMot4" intValue:motor4Position];
			[event postEvent:eh];
			[event release];
			
			// keep the old values and only post a new event if an input really changes! :)
			oldMotor1Position = [inputPosMot1 doubleValue];
			oldMotor2Position = [inputPosMot2 doubleValue];
			oldMotor3Position = [inputPosMot3 doubleValue];
			oldMotor4Position = [inputPosMot4 doubleValue];
		}
}

@end
