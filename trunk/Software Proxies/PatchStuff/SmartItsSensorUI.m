//
//  ThresholdUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "SmartItsSensorUI.h"


@implementation SmartItsSensorUI
+ (id)viewNibName
{
	NSLog(@"in SmartItsSensorUI: viewNibName");
	return @"SmartItsSensorUI.nib";
}

- (void)_updateSources{

}

- (void)deviceMenu:(id)fp8{

}

- (void)sourceMenu:(id)fp8
{

}

- (void)setupViewForPatch:(id)fp8
{
	NSLog(@"in SmartItsSensorUI: setupViewForPatch");
	_patch = fp8;
}

@end
