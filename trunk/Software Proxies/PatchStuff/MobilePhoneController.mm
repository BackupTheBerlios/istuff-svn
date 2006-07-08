//
//  MobilePhoneControlPatch.mm
//  QCiStuff
//
//  Created by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhoneController.h"

@implementation MobilePhoneController
	
- (id)initWithIdentifier:(id)fp8
{	
//	proxyName = [NSMutableString stringWithString:@"MobilePhoneController_"];
	//processEvent = true;
	lastPathVal = "";
	[inputRepeatPort setDoubleValue:0];
	[inputScanCodePort setDoubleValue:0];
	
	lastInputDisconnect = false;
	lastInputBacklightOff = false;
	lastInputBacklightOn = false;
	lastInputCloseApp = false;
	lastInputLaunchApp = false;
	lastInputPlaySound = false;
	lastInputStopSound = false;
	lastInputCaptureKeys = false;

	return [super initWithIdentifier:fp8];
}
	
- (void) executeCustomPatch {
	// In this early version, the according parameters are alos realized as editable input ports
	// later on they should be specified in the corresponding GUI element of the patch
	
	// These Events do not have special parameters
	// Only the corresponding command numbers have to be posted		
	
	if ( [inputDisconnect booleanValue] == TRUE && [inputDisconnect booleanValue] != lastInputDisconnect) 
	{
		NSLog(@"inputDisconnect");
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:1];
		[event postEvent:eh];
	}
	
	if ([inputBacklightOn booleanValue] == TRUE && [inputBacklightOn booleanValue] != lastInputBacklightOn) 
	{
		NSLog(@"Command: Backlight On");
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:2];
		[event postEvent:eh];
	}
	
	if ([inputBacklightOff booleanValue]  == TRUE && [inputBacklightOff booleanValue] != lastInputBacklightOff) 
	{
		NSLog(@"BackLightOff");
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:3];
		[event postEvent:eh];

	}
	
	if ([inputStopSound booleanValue]  == TRUE && [inputStopSound booleanValue] != lastInputStopSound) 
	{
		NSLog(@"Stop Sound");
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:6];
		[event postEvent:eh];

	}

	// These commands all need a "Path" parameter
	if ([inputPlaySound booleanValue]  == TRUE && [inputPlaySound booleanValue] != lastInputPlaySound) 
	 {
		NSLog(@"PlaySound");
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:5];
		[event addNewStringField:@"Path" stringValue:[inputPath stringValue]];
		[event postEvent:eh];

	}

	if ([inputLaunchApp booleanValue] == TRUE && [inputLaunchApp booleanValue] != lastInputLaunchApp) 
	{
		NSLog(@"Launch Application");
		//delete eventPtr;
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:7];
		[event addNewStringField:@"Path" stringValue:[inputPath stringValue]];
		[event postEvent:eh];

	}
	
	
	if ([inputCloseApp booleanValue]  == TRUE && [inputCloseApp booleanValue] != lastInputCloseApp) 
	{
		NSLog(@"Close Application");
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:8];
		[event addNewStringField:@"Path" stringValue:[inputPath stringValue]];
		[event postEvent:eh];
	}
	
	// The keypress command needs to create an Event with three parameters
	if ([inputKeyCode doubleValue] > 0)
	{
		NSLog(@"Putting a text event: %i",(int) [inputScanCodePort doubleValue]);

		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:4];
		[event addNewIntegerField:@"Code" intValue:(int) [inputKeyCode doubleValue]];
		[event addNewIntegerField:@"Repeat" intValue:(int) [inputRepeatPort doubleValue]];
		[event addNewIntegerField:@"ScanCode" intValue:(int) [inputScanCodePort doubleValue]];
		[event postEvent:eh];
		
		
		[inputKeyCode setDoubleValue:0];
	}

	// The change profile command should only be changed if the profile number is really different
	if (([inputProfileNumber doubleValue] != lastInputProfileNumber) && ((int) [inputProfileNumber doubleValue] != 0))
	{
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:12];
		[event addNewIntegerField:@"ProfileNo" intValue:(int) [inputProfileNumber doubleValue]];
		[event postEvent:eh];
	}
	
	if ([inputCaptureKeys booleanValue]  == TRUE && [inputCaptureKeys booleanValue] != lastInputCaptureKeys) 
	{
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:10];
		[event postEvent:eh];

	}else if ([inputCaptureKeys booleanValue]  == FALSE && [inputCaptureKeys booleanValue] != lastInputCaptureKeys) 
	{
		iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"iStuffMobile" eventID:[self eventID]];
		[event setTimeToLive:50];
		[event addNewIntegerField:@"Command" intValue:11];
		[event postEvent:eh];
	}
	
	lastInputDisconnect = [inputDisconnect booleanValue];
	lastInputBacklightOn = [inputBacklightOn booleanValue];
	lastInputBacklightOff = [inputBacklightOff booleanValue];
	lastInputCloseApp = [inputCloseApp booleanValue];
	lastInputLaunchApp = [inputLaunchApp booleanValue];
	lastInputPlaySound = [inputPlaySound booleanValue];
	lastInputStopSound = [inputStopSound booleanValue];
	lastInputProfileNumber = (int) [inputProfileNumber doubleValue];
	lastInputCaptureKeys = [inputCaptureKeys booleanValue];
}

@end
