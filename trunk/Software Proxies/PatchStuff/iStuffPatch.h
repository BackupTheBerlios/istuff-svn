//
//  iStuffPatch.h
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//	Media Computing Group
//	
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <eh2.h>
#import <idk_io.h>
#import "QCPatch.h"
#import "iStuffPatchUI.h"	

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class iStuffPatchUI;
@interface iStuffPatch : QCPatch
{
// Event Heap Connection Management - Components of each iStuff patch
	NSString *eventHeapName;
	NSString *hostName;
	
	BOOL connectToEventHeaps;
	BOOL tryToConnect;
	BOOL connectedToEventHeap;
	BOOL advancedOptionsHidden;
	BOOL standby;
	int radioButtonIndex;
	//list of Event Heaps
	NSMutableArray *netServices;
	NSNetServiceBrowser *netServiceBrowser;
	NSMutableArray *services;
	// pointer to the Event Heap client
	eh2_EventHeapPtr *eh;

	//	Specification of the input and output ports of the patch

}

// Methods to be extended for a specific patch
+ (int) executionMode;
+ (BOOL) allowsSubpatches;
- (id) initWithIdentifier:(id)fp8;
- (id) setup:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

// Methods that give internal information
- (NSMutableArray *) foundEventHeaps;
- (NSString *) eventHeapName;
- (BOOL) connected;
- (BOOL) advancedOptionsHidden;
- (BOOL) suspended;
- (int) radioButtonIndex;


// Methods for the Event Heap connection management
- (void) netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveService:(NSNetService *)aNetService moreComing:(BOOL)moreComing;
- (void) netServiceBrowser:(NSNetServiceBrowser*)aNetServiceBrowser didFindService:(NSNetService *)aNetService moreComing:(BOOL)moreComing;
- (void) sendEHSListUpdate;

- (void) establishEHConnection:(NSNotification *) notification;
- (void) disconnectFromEH;

// create the event heap instance for the client
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port;

- (BOOL) connected;
- (void) dealloc;
- (void) nodeWillRemoveFromGraph;

// Methods to change internal settings
- (void) setEventHeapName:(NSString *)newEventHeapName;
- (void) setAdvancedOptionsHidden:(BOOL) flag;
- (void) setRadioButtonIndex:(int)index;


@end