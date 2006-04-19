//
//  MobilePhoneKeyListenerPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"
	
@interface MobilePhoneKeyListenerPatch : iStuffProviderPatch {
	// Define member variables and output ports here

    QCNumberPort *outputKeyStroke;
	QCBooleanPort *outputKeyPressed;

	//signal wether the output port should provide a new value for the outputPort
	int keyCode;
	BOOL setOutputPort;
}

- (id) initWithIdentifier:(id)fp8; // Initialization when patch instance is created.
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20; // code executed with every patch execution cycle
- (void) processEvent:(eh2_EventPtr) eventPtr;


@end

