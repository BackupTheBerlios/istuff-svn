//
//  RFIDReaderPatch.h
//  QCiStuff
//
//  Created by Rene Reiners on 11/25/05.
//  Copyright 2005 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <eh2.h>
#import <idk_io.h>
#import "QCPatch.h"
#import "RFIDReaderPatchUI.h";

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
//here the file for the UI must be named
@class RFIDReaderPatchUI;

@interface RFIDReaderPatch : QCPatch {
	QCStringPort *outputTag;
	
	// pointer to the Event Heap client
	eh2_EventHeapPtr *eh;
	
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

//is this needed here?
// create / post an event
//- (eh2_EventPtr *) createEvent;
@end

