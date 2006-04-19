//
//  Filter.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CustomPatch.h"

@interface Filter : CustomPatch {
	
	QCNumberPort *inputInputValue;
	QCNumberPort *inputThreshold;
	QCNumberPort *inputChangeBy;
	
	QCNumberPort *outputPassthrough;
	double lastInputVal;
	//QCBooleanPort *inputNextSlide;
    //QCBooleanPort *inputPrevSlide;
	//BOOL lastInputNextSlide;
	//BOOL lastInputPrevSlide;

}
+ (int) executionMode;
- (id)initWithIdentifier:(id)fp8;
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
