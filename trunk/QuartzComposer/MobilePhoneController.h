//
//  MobilePhoneControllerPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffConsumerPatch.h"

@interface MobilePhoneController : iStuffConsumerPatch {
	
	// if a boolean port is TRUE, the corresponding event with the command  number
	//  is put on the Event Heap
		QCBooleanPort *inputBacklightOn;
		QCBooleanPort *inputPlaySound;
		QCBooleanPort *inputLaunchApp;
		QCStringPort *inputPath;		
		QCBooleanPort *inputCloseApp;
		QCNumberPort *inputKeyCode;
		QCNumberPort *inputScanCodePort;
		QCNumberPort *inputProfileNumber;
		QCBooleanPort *inputCaptureKeys;

// NOTE: Shouldn't the values for Repat and ScanCode also be handled 
// inside the corresponding MPProxy? The proxy should care about these values.
// Also the commands should be Strings. So a more generic patch could be created.
				
	// These variables prevent that an event is sent all the time
	// but only when there was a change in between
		bool lastInputDisconnect;
		bool lastInputBacklightOn;
		bool lastInputPlaySound;
		bool lastInputLaunchApp;
		bool lastInputCloseApp;
		bool lastInputCaptureKeys;
		
		int lastInputProfileNumber;
		BOOL processEvent;
		char* lastPathVal;
}

- (id) initWithIdentifier:(id)fp8;

@end
