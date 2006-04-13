//
//  SmartItsSensorPatch.h
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"

@interface SmartItsSensorPatch : iStuffProviderPatch {

	QCStringPort *outputSourceID;
	QCNumberPort *outputSGX;
	QCNumberPort *outputSGY;
	QCNumberPort *outputSGZ;
	QCNumberPort *outputSLI;	
	QCNumberPort *outputSFC;
	QCNumberPort *outputSTE;
	QCNumberPort *outputSSW;
	QCNumberPort *outputSAU;
	QCNumberPort *outputSVC;

}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
