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
#import "SmartItsSensorUI.h";
	

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class SmartItsSensorUI;

@interface SmartItsSensor : QCPatch {

	QCStringPort *outputSourceID;
	QCNumberPort *outputSGX;
	QCNumberPort *outputSGY;
	QCNumberPort *outputSGZ;
	QCNumberPort *outputSLI;	
	QCNumberPort *outputSFC;
	QCNumberPort *outputSTE;
	QCNumberPort *outputSSW;
	QCNumberPort *outputSAU;
	QCNumberPort *outputSVC;
	
	eh2_EventHeapPtr *eh;
	BOOL waitForEvents;
}

+ (int)executionMode;
+ (BOOL)allowsSubpatches;
- (id)initWithIdentifier:(id)fp8;
- (id)setup:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

// create the event heap instance for the client
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port;

// activate/deactivate the thread that waits for EventHeap events
- (void) startReceivingEvents;
- (void) stopReceivingEvents;

@end
