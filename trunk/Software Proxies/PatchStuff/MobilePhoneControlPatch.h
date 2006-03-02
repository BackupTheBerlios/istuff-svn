//
//  MobilePhoneControlPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffConsumerPatch.h"

@interface MobilePhoneControlPatch : iStuffConsumerPatch {
	
	// if a boolean port is TRUE, the corresponding event with the command  number
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
// inside the corresponding MPProxy? The proxy should care about these values.
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
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
