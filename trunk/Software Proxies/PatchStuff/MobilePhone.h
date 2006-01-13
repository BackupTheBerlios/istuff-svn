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
	// if a port is TRUE, the corresponding event with the command  number
	//  is put on the Event Heap
		QCBooleanPort *inputDisconnect;
		QCBooleanPort *inputBacklightOn;
		QCBooleanPort *inputBacklightOff;
		QCBooleanPort *inputPlaySound;
		QCBooleanPort *inputStopSound;
		QCBooleanPort *inputLaunchApp;
		QCStringPort *inputPath;		
		QCBooleanPort *inputCloseApp;
		QCNumberPort *inputKeyCode;
		QCNumberPort *inputRepeatPort;
		QCNumberPort *inputScanCodePort;
		QCNumberPort *inputProfileNumber;
// NOTE: Shouldn't the values for Repat and ScanCode also be handled 
// inside the corresponding MPProxy? The proxy shoud=ld care about these values.
// Also the commands should be Strings. So a more generic patch could be created.
				
	// These variables prevent that an event is sent all the time
	// but only when there was a change in between
		bool lastInputDisconnect;
		bool lastInputBacklightOff;
		bool lastInputBacklightOn;
		bool lastInputStopSound;
		bool lastInputPlaySound;
		bool lastInputLaunchApp;
		bool lastInputCloseApp;
		
		int lastInputProfileNumber;
		BOOL processEvent;
		char* lastPathVal;

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
