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
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// This is where the execution of your patch happens.
        // Everything in this method gets executed once
        // per 'clock cycle', which is available in fp12 (time).
	
        // fp8 is the QCOpenGLContext*.  Don't forget to set
        // it before you start drawing.  
	
        // Read/Write any ports in here too.
			
	
		if( [inputPWMOut0 doubleValue] != lastInputPWMOut0 ){
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
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
			(*eventPtr)->setPostValueInt ("ID", 1);
			(*eventPtr)->setPostValueInt ("VALUE", (int) [inputPWMOut1 doubleValue]);
			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
			lastInputPWMOut1 = (int) [inputPWMOut1 doubleValue];
		}

        return [super execute:fp8 time:fp12 arguments:fp20];
}

@end
