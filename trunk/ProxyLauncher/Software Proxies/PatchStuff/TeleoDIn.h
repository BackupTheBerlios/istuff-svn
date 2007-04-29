//
//  TeleoDInPatch.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Refactored by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h";

@interface TeleoDIn : iStuffProviderPatch {

	QCNumberPort *outputX;
    QCNumberPort *outputY;
    QCNumberPort *outputZ;
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
- (void) processEvent:(iStuffEvent *) event;

@end
