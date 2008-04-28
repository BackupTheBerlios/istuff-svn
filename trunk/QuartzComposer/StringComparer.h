//
//  PowerbookTiltSensorPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CustomPatch.h"

// possible input/output types. 
@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class StringComparerUI;

@interface StringComparer : CustomPatch {
	QCStringPort *inputCompareThisString;
	QCStringPort *inputWithString;
	QCBooleanPort *outputResult;
}

+ (int) executionMode;
- (id)initWithIdentifier:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
