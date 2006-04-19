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
	[manager registerNodeWithClass: [PowerbookTiltSensor class]];
	[manager registerNodeWithClass: [PresentationController class]];
	[manager registerNodeWithClass: [RFIDReader class]];
	[manager registerNodeWithClass: [InterfaceKit class]];
	[manager registerNodeWithClass: [Accelerometer class]];
	[manager registerNodeWithClass: [ServoController class]];
	[manager registerNodeWithClass: [Filter class]];
	[manager registerNodeWithClass: [StringComparer class]];
	[manager registerNodeWithClass: [SweepController class]];
	[manager registerNodeWithClass: [TeleoPWMOut class]];
	[manager registerNodeWithClass: [SmartItsSensor class]];
	[manager registerNodeWithClass: [MobilePhoneController class]];
	[manager registerNodeWithClass: [CharacterGenerator class]];
	[manager registerNodeWithClass: [MobilePhoneKeyListener class]];
}
@end
