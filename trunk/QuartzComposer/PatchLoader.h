//
//  PatchLoader.h
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "GFPlugInRegistrationProtocol.h"
	
// List your patch class and any QC patches you use here.
@class GFNodeManager, PowerbookTiltSensor, RFIDReader,InterfaceKit,Accelerometer,PresentationController,
	   ServoController, Filter, StringComparer, SweepController, TeleoPWMOut, MobilePhoneController,CharacterGenerator, SmartItsSensor,
	   MobilePhoneKeyListener, Shake;

@interface PatchLoader : NSObject <GFPlugInRegistration>
	
+ (void)registerNodesWithManager:(GFNodeManager*)manager;
	
@end
