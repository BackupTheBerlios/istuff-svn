//
//  PowerbookTiltSensorPatchUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "AccelerometerPatchUI.h"


@implementation AccelerometerPatchUI
+ (id)viewNibName
{
	NSLog(@"in AccelerometerPatchUI: viewNibName");
	return @"AccelerometerPatchUI.nib";
}

- (void)_updateSources{

}

- (void)deviceMenu:(id)fp8{
  //return @"RRmod.nib";
}

- (void)sourceMenu:(id)fp8
{
  //return @"RRmod.nib";
}

- (void)setupViewForPatch:(id)fp8
{
	NSLog(@"in AccelerometerPatchUI: setupViewForPatch");
	_patch = fp8;
}

@end
