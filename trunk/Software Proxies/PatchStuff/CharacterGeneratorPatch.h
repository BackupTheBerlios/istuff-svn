//
//  CharacterGeneratorPatch.h
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"

@interface CharacterGeneratorPatch : iStuffProviderPatch {

	QCNumberPort *outputKeyStroke;
	QCNumberPort *outputPermanentASCIICode;
	BOOL setOutputPort;
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
//- (void) waitForEvents;
- (void) processEvent:(eh2_EventPtr) eventPtr;
@end
