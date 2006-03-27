//
//  InterFaceKitPatch.h
//  QCiStuff
//
//  Created by Rene Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group RWTH Aachen, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"

@interface InterfaceKitPatch : iStuffProviderPatch {

	//These are the 7 seven analog ports to which other phidgets(sensors, etc.)
	//can be connected

	QCNumberPort *outputAnalogReading0;
	QCNumberPort *outputAnalogReading1;
    QCNumberPort *outputAnalogReading2;
    QCNumberPort *outputAnalogReading3;
	QCNumberPort *outputAnalogReading4;
	QCNumberPort *outputAnalogReading5;
	QCNumberPort *outputAnalogReading6;
	QCNumberPort *outputAnalogReading7;
		
	//The interface kit also has 7 digital ports that can be activated or deactivated (0 or 1).
	//To these ports other phidgets can be connected an be enabled or disabled (e.g. diods)
/*
	QCBooleanPort *inputDigitalIn0;	
	QCBooleanPort *inputDigitalIn1;
	QCBooleanPort *inputDigitalIn2;
	QCBooleanPort *inputDigitalIn3;
	QCBooleanPort *inputDigitalIn4;
	QCBooleanPort *inputDigitalIn5;
	QCBooleanPort *inputDigitalIn6;
	QCBooleanPort *inputDigitalIn7;
*/	
//And there are 7 ports that read digital inputs from other phidgets

/*	QCBooleanPort *outputDigitalReading1;
	QCBooleanPort *outputDigitalReading2;
	QCBooleanPort *outputDigitalReading3;
	QCBooleanPort *outputDigitalReading4;
	QCBooleanPort *outputDigitalReading5;
	QCBooleanPort *outputDigitalReading6;
	QCBooleanPort *outputDigitalReading7;
*/
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
- (void) waitForEvents;

@end

