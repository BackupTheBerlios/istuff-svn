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
		// These Commands are only passed through --> no changes are performed
		// put command and the corresponding command number onto the Event Heap
		QCBooleanPort *inputDisconnect;
		QCBooleanPort *inputBacklightOn;
		QCBooleanPort *inputBacklightOff;
		QCBooleanPort *inputStopSound;
		
		QCBooleanPort *inputPlaySound;
		QCNumberPort *inputRepeatPort;
		QCBooleanPort *inputLaunchApp;
		QCBooleanPort *inputCloseApp;
		QCNumberPort *inputKeyCode;
		QCNumberPort *inputScanCodePort;
		
		QCStringPort *inputPath;
	
		// This paramater is needed so that only a new command is posted
		// otherwise the same command is posted several times
		char* lastPathVal;
		// This variable is used to specifify that a command Event should really be posted
		// or if it is just a repetition
		bool lastInputDisconnect;
		bool lastInputBacklightOff;
		bool lastInputBacklightOn;
		bool lastInputStopSound;
		bool lastInputPlaySound;
		bool lastInputLaunchApp;
		bool lastInputCloseApp;
		
		BOOL processEvent;

		// pointer to the Event Heap client
		eh2_EventHeapPtr *eh;
}

+ (int)executionMode;
+ (BOOL)allowsSubpatches;
- (id)initWithIdentifier:(id)fp8;
- (id)setup:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

// create the event heap instance for the client
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port;

@end
