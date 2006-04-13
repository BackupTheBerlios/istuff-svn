//
//  RFIDReaderPatch.h
//  QCiStuff
//
//  Created by Rene Reiners in winter 2005 / 2006
//  Copyright 2005 Media Computing Group RWTH Aachen, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"

@interface RFIDReaderPatch : iStuffProviderPatch {

	QCStringPort *outputTag;
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
 
@end

