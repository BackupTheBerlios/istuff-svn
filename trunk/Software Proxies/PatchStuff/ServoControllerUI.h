//
//  PowerbookTiltSensorPatchUI.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "QCInspector.h"


@interface ServoControllerUI : QCInspector
{
    NSPopUpButton *devicePopup;
    NSPopUpButton *sourcePopup;
}

+ (id)viewNibName;
- (void)_updateSources;
- (void)deviceMenu:(id)fp8;
- (void)sourceMenu:(id)fp8;
- (void)setupViewForPatch:(id)fp8;

@end
