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
#import "InterfaceKitPatchUI.h";

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
//here the file for the UI must be named
@class InterfaceKitPatchUI;

@interface InterfaceKitPatch : QCPatch {

	//These are the 7 seven analog ports to which other phidgets(sensors, etc.)
	//can be connected

	QCNumberPort *outputAnalogReading0;
	QCNumberPort *outputAnalogReading1;
    QCNumberPort *outputAnalogReading2;
    QCNumberPort *outputAnalogReading3;
	QCNumberPort *outputAnalogReading4;
	QCNumberPort *outputAnalogReading5;
	QCNumberPort *outputAnalogReading6;
	QCNumberPort *outputAnalogReading7;
		
	//The interface kit also has 7 digital ports that can be activated or deactivated (0 or 1).
	//To these ports other phidgets can be connected an be enabled or disabled (e.g. diods)

	QCBooleanPort *inputDigitalIn0;	
	QCBooleanPort *inputDigitalIn1;
	QCBooleanPort *inputDigitalIn2;
	QCBooleanPort *inputDigitalIn3;
	QCBooleanPort *inputDigitalIn4;
	QCBooleanPort *inputDigitalIn5;
	QCBooleanPort *inputDigitalIn6;
	QCBooleanPort *inputDigitalIn7;
//And there are 7 ports that read digital inputs from other phidgets

	QCBooleanPort *outputDigitalReading1;
	QCBooleanPort *outputDigitalReading2;
	QCBooleanPort *outputDigitalReading3;
	QCBooleanPort *outputDigitalReading4;
	QCBooleanPort *outputDigitalReading5;
	QCBooleanPort *outputDigitalReading6;
	QCBooleanPort *outputDigitalReading7;
	
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

