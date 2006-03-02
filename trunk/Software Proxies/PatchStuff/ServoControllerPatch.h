//
//  ServoControllerPatch.h
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffConsumerPatch.h"
	
@interface ServoControllerPatch : iStuffConsumerPatch {
	
	QCNumberPort *inputPosMot1;
	QCNumberPort *inputPosMot2;
	QCNumberPort *inputPosMot3;
	QCNumberPort *inputPosMot4;
	
	//These variables hold the values from one execution before
	double oldMotor1Position;
	double oldMotor2Position;
	double oldMotor3Position;
	double oldMotor4Position;
	
	/*the following could be used for a motor control
	QCNumberPort *inputSpeedMot1;
	QCNumberPort *inputSpeedMot2;
	QCNumberPort *inputSpeedMot3;
	QCNumberPort *inputSpeedMot4;	
    QCNumberPort *inputAccMot1;
    QCNumberPort *inputAccMot2;
    QCNumberPort *inputAccMot3;
    QCNumberPort *inputAccMot4;
	*/
}

- (id)initWithIdentifier:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
