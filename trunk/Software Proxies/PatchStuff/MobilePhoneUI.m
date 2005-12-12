//
//  MobilePhoneUI.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/20/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhoneUI.h"


@implementation MobilePhoneUI
+ (id)viewNibName
{
	NSLog(@"in MobilePhoneUI: viewNibName");
	return @"MobilePhoneUI.nib";
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
	NSLog(@"in MobilePhoneUI: setupViewForPatch");
	_patch = fp8;
}

@end
