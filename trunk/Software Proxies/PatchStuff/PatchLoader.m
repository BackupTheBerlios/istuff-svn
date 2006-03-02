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
	[manager registerNodeWithClass: [PresentationControllerPatch class]];
	[manager registerNodeWithClass: [RFIDReaderPatch class]];
	[manager registerNodeWithClass: [InterfaceKitPatch class]];
	[manager registerNodeWithClass: [AccelerometerPatch class]];
	[manager registerNodeWithClass: [ServoControllerPatch class]];
	[manager registerNodeWithClass: [Threshold class]];
	[manager registerNodeWithClass: [StringComparer class]];
	[manager registerNodeWithClass: [SweepPatch class]];
	[manager registerNodeWithClass: [TeleoPWMOutPatch class]];
	[manager registerNodeWithClass: [SmartItsSensorPatch class]];
	[manager registerNodeWithClass: [MobilePhoneControlPatch class]];
	[manager registerNodeWithClass: [CharacterGeneratorPatch class]];
	[manager registerNodeWithClass: [MobilePhoneKeyListenerPatch class]];
}
@end
