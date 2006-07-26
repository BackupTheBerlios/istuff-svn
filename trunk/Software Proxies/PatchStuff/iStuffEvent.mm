//
//  iStuffEvent.mm
//  QCiStuff
//
//  Created by Rene Reiners on 6/13/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

#import "iStuffEvent.h"

@implementation iStuffEvent

- (id) initWithTypeAndID:(NSString *)type eventID:(NSString *)idName{
	if ([super init] != nil) {
		eventType = type;
		[eventType retain];
		[eventID setString: idName];
		[eventID retain];
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ([eventType cString]);
		[self addNewStringField:@"ProxyID" stringValue:idName];
	}
	return self;
}

- (id) initWithType:(NSString *)type {
	if ([super init] != nil) {
		eventType = type;
		[eventType retain];
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ([eventType cString]);
		// For stability reasons, only events with a "ProxyID" field are generated
		[self addNewStringTemplateField:@"ProxyID"];
	}
	return self;
}

- (id) initWithPointer:(eh2_EventPtr)eventPointer {
	if ([super init] != nil) {
		eventType = [NSString stringWithCString:eventPointer->getEventType()];
		[eventType retain];
		eventID = [NSMutableString stringWithCString:eventPointer->getPostValueString("ProxyID")];
		[eventID retain];
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eventPointer;
		// For stability reasons, only events with a "ProxyID" field are generated
		[self addNewStringTemplateField:@"ProxyID"];
	}
	return self;
}

- (BOOL) fieldExists:(NSString *) fieldName {
	return ((*eventPtr)->fieldExists([fieldName cString]));
}

- (void) postEvent:(eh2_EventHeapPtr *) eventHeapPointer {
	if (eventPtr != nil) {
		(*eventHeapPointer)->putEvent (*eventPtr);
	}
}

- (void) setEventType:(NSString *)type {
	eventType = type;
	[eventType retain];
	eventPtr = new eh2_EventPtr;
	(*eventPtr) = eh2_Event::cs_create ([eventType cString]);
}

- (void) addNewIntegerField:(NSString *)fieldName intValue:(int)value {
	if (eventPtr != nil)
		(*eventPtr)->setPostValueInt ([fieldName cString], value);
}

- (void) addNewStringField:(NSString *)fieldName stringValue:(NSString *)value {
	if (eventPtr != nil);
		(*eventPtr)->setPostValueString([fieldName cString], [value cString]);	
}

- (void) addNewTemplateValueString:(NSString *)fieldName stringValue:(NSString *)value {
	(*eventPtr)->setTemplateValueString([fieldName cString], [value cString]); 
}

- (void) addNewTemplateValueInt:(NSString *)fieldName intValue:(int)value {
	(*eventPtr)->setTemplateValueInt([fieldName cString], value); 
}

- (void) addNewStringTemplateField:(NSString *)fieldName{
		eh2_Field* field;
		field = (*eventPtr)->allocateField([fieldName cString], eh2_FieldType::cs_string());
		field->setTemplateValueType(eh2_EventConsts::FVT_FORMAL);
}

- (void) setEventHeap:(NSString *)eventHeapName {
}

- (void) setTimeToLive:(int)time {
	if (eventPtr != nil)
	(*eventPtr)->setPostValueInt("TimeToLive", time);
}

- (eh2_EventPtr) eventPointer{
	return (*eventPtr);
}

- (int) intValueForField:(NSString *) fieldName{
		return (*eventPtr)->getPostValueInt([fieldName cString]);
}

- (double) doubleValueForField:(NSString *) fieldName{
		return (*eventPtr)->getPostValueDouble([fieldName cString]);
}

- (NSString *) stringValueForField:(NSString *) fieldName{
		return ([NSString stringWithCString:(*eventPtr)->getPostValueString([fieldName cString])]);
}

- (NSString *) eventType {
	return eventType;
}

- (NSString *) eventID {
	return eventID;
}

- (void) setEventID:(NSString*) idName {
	[eventID release];
	[eventID setString:idName];
	[eventID retain];
}

- (void) dealloc {
	[eventType release];
	[eventID release];
	[super dealloc];
}

@end
