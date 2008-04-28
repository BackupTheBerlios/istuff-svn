//
//  CustomPatch.h
//  QCiStuff
//
//  Created by Rene Reiners on 3/2/06.
//  Copyright 2006 Media Computing Group RWTH Aachen, Germany. All rights reserved.
//
// This class can be used to subuclass custom patches that behave like standard Quartz Composer Patches.

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import "QCPatch.h"
#import "CustomPatchUI.h"	

@class QCIndexPort, QCNumberPort, QCStringPort,
        QCBooleanPort, QCVirtualPort, QCColorPort,
        QCImagePort;
		
@class customPatchUI;

@interface CustomPatch : QCPatch {

}

+ (int) executionMode;
+ (BOOL) allowsSubpatches;
- (id) initWithIdentifier:(id)fp8;
- (id) setup:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;
- (void) dealloc;

@end
