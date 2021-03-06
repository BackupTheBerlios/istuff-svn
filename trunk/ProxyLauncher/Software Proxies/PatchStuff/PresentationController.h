//
//  PresentationControllerPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Modified and refactored by Ren� Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffConsumerPatch.h"

@interface PresentationController : iStuffConsumerPatch {
	
	QCBooleanPort *inputNextSlide;
    QCBooleanPort *inputPrevSlide;
	QCNumberPort *inputGotoSlideNumber;

	BOOL lastInputNextSlide;
	BOOL lastInputPrevSlide;
	//BOOL lastInputNextPresentation;
	//BOOL lastInputPrevPresentation;
 
	BOOL lastInputStartPresentation1;
	BOOL lastInputStartPresentation2;
	//BOOL url1Activated;
	//BOOL url2Activated;
	
	int lastInputGotoSlide;
}

@end
