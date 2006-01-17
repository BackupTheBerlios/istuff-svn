//
//  PowerbookTiltSensorPatchUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "PowerbookTiltSensorPatchUI.h"


@implementation PowerbookTiltSensorPatchUI
// this method is called when a patch is inserted and 
// the inspector is  shown for the first time
+ (id)viewNibName
{
	NSLog(@"in PowerbookTiltSensorPatchUI: viewNibName");
	return @"PowerbookTiltSensorPatchUI.nib";
}

- (void)_updateSources{
	NSLog(@"in PowerbookTiltSensorPatchUI: updateSources");


}

- (void)deviceMenu:(id)fp8{
	NSLog(@"in PowerbookTiltSensorPatchUI: deviceMenu");

}

- (void)sourceMenu:(id)fp8
{
	NSLog(@"in PowerbookTiltSensorPatchUI: sourceMenu");

}

// This method is always called  when the inspector is called
// and maybe when tab is called for the first time...
- (void)setupViewForPatch:(id)fp8
{
	NSLog(@"in PowerbookTiltSensorPatchUI: setupViewForPatch");
	_patch = fp8;
}

@end
