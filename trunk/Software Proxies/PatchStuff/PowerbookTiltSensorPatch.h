//
//  PowerbookTiltSensorPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Modified and refactored by René Reiners in winter 2005/2006 
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h";

@interface PowerbookTiltSensorPatch : iStuffProviderPatch{
	QCNumberPort *outputX;
    QCNumberPort *outputY;
    QCNumberPort *outputZ;
	
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
- (void) waitForEvents;

@end
