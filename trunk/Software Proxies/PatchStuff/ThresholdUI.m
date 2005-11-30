//
//  ThresholdUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "ThresholdUI.h"


@implementation ThresholdUI
+ (id)viewNibName
{
	NSLog(@"in ThresholdUI: viewNibName");
	return @"ThresholdUI.nib";
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
	NSLog(@"in ThresholdUI: setupViewForPatch");
	_patch = fp8;
}

@end
