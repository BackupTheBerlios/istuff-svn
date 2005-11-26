//
//  PresentationUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "PresentationUI.h"


@implementation PresentationUI
+ (id)viewNibName
{
	NSLog(@"in PresentationUI: viewNibName");
	return @"PresentationUI.nib";
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
	NSLog(@"in PresentationUI: setupViewForPatch");
	_patch = fp8;
}

@end
