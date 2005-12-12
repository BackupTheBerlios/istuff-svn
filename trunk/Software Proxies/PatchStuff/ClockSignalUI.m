//
//  ClockSignalUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "ClockSignalUI.h"


@implementation ClockSignalUI
+ (id)viewNibName
{
	NSLog(@"in ClockSignalUI: viewNibName");
	return @"ClockSignalUI.nib";
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
	NSLog(@"in ClockSignalUI: setupViewForPatch");
	_patch = fp8;
}

@end
