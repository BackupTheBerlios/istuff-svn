//
//  TeleoPWMOutPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Refactored by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffConsumerPatch.h";

@interface TeleoPWMOut : iStuffConsumerPatch {

	QCNumberPort *inputPWMOut0;
	QCNumberPort *inputPWMOut1;
	
	int lastInputPWMOut0;
	int lastInputPWMOut1;
}

- (id) initWithIdentifier:(id)fp8;

@end
