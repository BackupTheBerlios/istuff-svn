//
//  AccelerometerPatch.h
//  QCiStuff
//
//  Created by Rene Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group RWTH Aachen, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"

@interface Accelerometer : iStuffProviderPatch {

	QCStringPort *outputX;
	QCStringPort *outputY;
}

- (id) initWithIdentifier:(id)fp8;
- (void) processEvent:(iStuffEvent *) event;

@end

