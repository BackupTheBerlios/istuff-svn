//
//  PowerbookTiltSensorPatchUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "InterfaceKitPatchUI.h"


@implementation InterfaceKitPatchUI
+ (id)viewNibName
{
	NSLog(@"in InterfaceKitPatchUI: viewNibName");
	return @"InterfaceKitPatchUI.nib";
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
	NSLog(@"in InterfaceKitPatchUI: setupViewForPatch");
	_patch = fp8;
}

@end
