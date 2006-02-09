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
#import "MobilePhoneKeyListenerUI.h";
	
// MobilePhoneKeyListenerUI should somehow register with the Notification Center
// Here the notifications should be caught. MobilePhoneKeyListenerUI is also imported.
// Therefore a variable can be declared.

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class MobilePhoneKeyListenerUI;

@interface MobilePhoneKeyListener : QCPatch {
	//QCBooleanPort *outputKeyPressed;
    QCNumberPort *outputKeyStroke;
	QCBooleanPort *outputKeyPressed;
	
	// pointer to the Event Heap client
	eh2_EventHeapPtr *eh;

	//signal wether the output port should provide a new value for the outputPort
	int keyCode;
	BOOL setOutputPort;

	// signal whether or not to exit the thread waitforEvent
	BOOL waitForEvents;
}

+ (int)executionMode;
+ (BOOL)allowsSubpatches;
- (id)initWithIdentifier:(id)fp8;
- (id)setup:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

// create the event heap instance for the client
//- (void) createEventHeap;
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port;

// activate/deactivate the thread that waits for EventHeap events
- (void) startReceivingEvents;
- (void) stopReceivingEvents;

// create / post an event
- (eh2_EventPtr *) createEvent;
@end
