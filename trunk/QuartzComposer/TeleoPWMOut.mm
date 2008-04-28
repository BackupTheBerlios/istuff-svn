//
//  TeleoPWMOutPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Refactored by RenŽ Reiners in winter 2005/2006 
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "TeleoPWMOut.h"

@implementation TeleoPWMOut
	
- (id)initWithIdentifier:(id)fp8
{
	lastInputPWMOut0=-1;
	lastInputPWMOut1=-1;
	
	return [super initWithIdentifier:fp8];
}
	
- (void) executeCustomPatch {
			
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"Teleo_PWMOUT" eventID:[self eventID]];
		[event setTimeToLive:500];
		
		if( [inputPWMOut0 doubleValue] != lastInputPWMOut0 ){
			//eh2_EventPtr *eventPtr = new eh2_EventPtr;
			//eventPtr = new eh2_EventPtr;
			//(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
			//[self createNewEventType:@"TELEO_PWMOUT"];
			//[self addNewStringField:@"ProxyID" stringValue:eventID];
			
			[event addNewIntegerField:@"ID" intValue:0];
			[event addNewIntegerField:@"VALUE" intValue:(int) [inputPWMOut0 doubleValue]];
			//(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		
			//(*eventPtr)->setPostValueInt ("ID", 0);
//			(*eventPtr)->setPostValueInt ("VALUE", (int) [inputPWMOut0 doubleValue]);
//			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
//			(*eh)->putEvent (*eventPtr);
//			delete eventPtr;
			lastInputPWMOut0 = (int)[inputPWMOut0 doubleValue];
			[event postEvent:eh];
		}
		
		if( [inputPWMOut1 doubleValue] != lastInputPWMOut1 ){
//			eh2_EventPtr *eventPtr = new eh2_EventPtr;
//			eventPtr = new eh2_EventPtr;
//			(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
//			(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
//			(*eventPtr)->setPostValueInt ("ID", 1);
//			(*eventPtr)->setPostValueInt ("VALUE", (int) [inputPWMOut1 doubleValue]);
//			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
//			(*eh)->putEvent (*eventPtr);
//			delete eventPtr;
			[event addNewIntegerField:@"ID" intValue:1];
			[event addNewIntegerField:@"VALUE" intValue:(int) [inputPWMOut1 doubleValue]];			
			[event postEvent:eh];
			lastInputPWMOut1 = (int) [inputPWMOut1 doubleValue];
		}
}

@end
