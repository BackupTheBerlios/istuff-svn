//
//  SweepPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Refactored by René Reiners on 03/02.06
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "IStuffProviderPatch.h"

@interface SweepController : iStuffProviderPatch {
	
	QCNumberPort *outputdX;
    QCNumberPort *outputdY;
    QCNumberPort *outputdrZ;
	QCBooleanPort *outputClick;

	BOOL setOutputPort;

}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
