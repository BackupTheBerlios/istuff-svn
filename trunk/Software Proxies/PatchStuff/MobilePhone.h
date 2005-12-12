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
#import "MobilePhoneUI.h";
	

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class MobilePhoneUI;

@interface MobilePhone : QCPatch {
	QCNumberPort *inputXValue;
	QCNumberPort *inputYValue;
	QCNumberPort *inputZValue;
	
	QCNumberPort *outputPassthrough;
	double lastInputVal;
	//QCBooleanPort *inputNextSlide;
    //QCBooleanPort *inputPrevSlide;
	//BOOL lastInputNextSlide;
	//BOOL lastInputPrevSlide;

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
