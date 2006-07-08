//
//  ServoControllerPatch.h
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffConsumerPatch.h"
	
@interface ServoController : iStuffConsumerPatch {
	
	QCNumberPort *inputPosMot1;
	QCNumberPort *inputPosMot2;
	QCNumberPort *inputPosMot3;
	QCNumberPort *inputPosMot4;
	
	//These variables hold the values from one execution before
	double oldMotor1Position;
	double oldMotor2Position;
	double oldMotor3Position;
	double oldMotor4Position;
	
}

@end
