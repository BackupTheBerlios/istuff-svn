//
//  PatchLoader.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "PatchLoader.h"


@implementation PatchLoader
+ (void)registerNodesWithManager:(GFNodeManager*)manager
{
	[manager registerNodeWithClass: [PowerbookTiltSensorPatch class]];
	[manager registerNodeWithClass: [Presentation class]];
	[manager registerNodeWithClass: [RFIDReaderPatch class]];
	[manager registerNodeWithClass: [InterfaceKitPatch class]];
	[manager registerNodeWithClass: [AccelerometerPatch class]];
	[manager registerNodeWithClass: [Presentation class]];
	[manager registerNodeWithClass: [ServoControllerPatch class]];
}
@end
