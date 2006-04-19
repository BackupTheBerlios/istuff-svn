//
//  TeleoPWMOutPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Refactored by RenŽ Reiners in winter 2005/2006 
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "TeleoPWMOutPatch.h"

@implementation TeleoPWMOutPatch
	
- (id)initWithIdentifier:(id)fp8
{
	lastInputPWMOut0=-1;
	lastInputPWMOut1=-1;
	
	return [super initWithIdentifier:fp8];
}
	
- (void) executeCustomPatch {
			
		if( [inputPWMOut0 doubleValue] != lastInputPWMOut0 ){
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
			(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
			(*eventPtr)->setPostValueInt ("ID", 0);
			(*eventPtr)->setPostValueInt ("VALUE", (int) [inputPWMOut0 doubleValue]);
			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
			lastInputPWMOut0 = (int)[inputPWMOut0 doubleValue];
		}
		
		if( [inputPWMOut1 doubleValue] != lastInputPWMOut1 ){
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
			(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
			(*eventPtr)->setPostValueInt ("ID", 1);
			(*eventPtr)->setPostValueInt ("VALUE", (int) [inputPWMOut1 doubleValue]);
			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
			lastInputPWMOut1 = (int) [inputPWMOut1 doubleValue];
		}
}

@end
