//
//  PowerbookTiltSensorPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <eh2.h>
#import <idk_io.h>
#import "QCPatch.h"
#import "ServoControllerUI.h";
	

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class ServoControllerUI;

@interface ServoController : QCPatch {
	
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
	// pointer to the Event Heap client
	eh2_EventHeapPtr *eh;

}

+ (int)executionMode;
+ (BOOL)allowsSubpatches;
- (id)initWithIdentifier:(id)fp8;
- (id)setup:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

// create the event heap instance for the client
//- (void) createEventHeap;
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port;

@end
