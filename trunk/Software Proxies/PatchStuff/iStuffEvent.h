//
//  iStuffEvent.h
//  QCiStuff
//
//  Created by Rene Reiners on 6/13/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <eh2.h>
#import <idk_io.h>
#import "QCPatch.h"
#import "iStuffPatchUI.h"	
#include <unistd.h>

@interface iStuffEvent : NSObject {

	eh2_EventHeapPtr *eventHeapPtr;
	NSString *eventType;
	NSMutableString *eventID;
	eh2_EventPtr *eventPtr;
}

- (id) initWithTypeAndID:(NSString *)type eventID:(NSString *)idName;
- (id) initWithType:(NSString *)type;
- (id) initWithPointer:(eh2_EventPtr)eventPointer;

- (void) setEventHeap:(NSString *)eventHeapName;
- (void) setEventType:(NSString *)eventType;
- (void) addNewIntegerField:(NSString *)fieldName intValue:(int)value;
- (void) addNewStringField:(NSString *)fieldName stringValue:(NSString *)value;
- (void) addNewStringTemplateField:(NSString *)fieldName;
- (void) postEvent:(eh2_EventHeapPtr *) eventHeapPointer;
- (void) setTimeToLive:(int)time;

- (void) setEventID:(NSString*) proxyName;
- (eh2_EventPtr) eventPointer;
- (int) intValueForField:(NSString *)fieldName;
- (double) doubleValueForField:(NSString *) fieldName;
- (BOOL) fieldExists:(NSString *) fieldName;
- (NSString *) stringValueForField:(NSString *) fieldName;
- (NSString *) eventType;
- (NSString *) eventID;

- (void) dealloc;





@end
