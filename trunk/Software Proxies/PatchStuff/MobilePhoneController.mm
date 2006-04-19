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
	proxyName = [NSMutableString stringWithString:@"MobilePhoneController_"];
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
	eh2_EventPtr *eventPtr;
	if ( [inputDisconnect booleanValue] == TRUE && [inputDisconnect booleanValue] != lastInputDisconnect) 
	{
		NSLog(@"inputDisconnect");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);		
		(*eventPtr)->setPostValueInt("Command", 1);
		// the "event package" is ready -> post it to the Event Heap
		(*eventPtr)->setPostValueInt("TimeToLive", 50);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
	}
	
	if ([inputBacklightOn booleanValue] == TRUE && [inputBacklightOn booleanValue] != lastInputBacklightOn) 
	{
		NSLog(@"Command: Backlight On");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 2);
					// the "event package" is ready -> post it to the Event Heap
				(*eventPtr)->setPostValueInt("TimeToLive", 1000);
				(*eh)->putEvent (*eventPtr);
				delete eventPtr;
	}
	
	if ([inputBacklightOff booleanValue]  == TRUE && [inputBacklightOff booleanValue] != lastInputBacklightOff) 
	{
		NSLog(@"BackLightOff");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 3);
					// the "event package" is ready -> post it to the Event Heap
				(*eventPtr)->setPostValueInt("TimeToLive", 50);
				(*eh)->putEvent (*eventPtr);
				delete eventPtr;
	}
	
	if ([inputStopSound booleanValue]  == TRUE && [inputStopSound booleanValue] != lastInputStopSound) 
	{
		NSLog(@"Stop Sound");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 6);
					// the "event package" is ready -> post it to the Event Heap
				(*eventPtr)->setPostValueInt("TimeToLive", 50);
				(*eh)->putEvent (*eventPtr);
				delete eventPtr;
	}

	// These commands all need a "Path" parameter
	if ([inputPlaySound booleanValue]  == TRUE && [inputPlaySound booleanValue] != lastInputPlaySound) 
	 {
		NSLog(@"PlaySound");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 5);
		(*eventPtr)->setPostValueString("Path", (const char*) [inputPath stringValue]);
		// the "event package" is ready -> post it to the Event Heap
		(*eventPtr)->setPostValueInt("TimeToLive", 50);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
	}

	if ([inputLaunchApp booleanValue] == TRUE && [inputLaunchApp booleanValue] != lastInputLaunchApp) 
	{
		NSLog(@"Launch Application");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 7);
		(*eventPtr)->setPostValueString("Path", (const char*) [inputPath stringValue]);
		// the "event package" is ready -> post it to the Event Heap
		(*eventPtr)->setPostValueInt("TimeToLive", 50);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
	}
	
	
	if ([inputCloseApp booleanValue]  == TRUE && [inputCloseApp booleanValue] != lastInputCloseApp) 
	{
		NSLog(@"Close Application");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 8);
		(*eventPtr)->setPostValueString("Path", (const char*) [inputPath stringValue]);
		// the "event package" is ready -> post it to the Event Heap
		(*eventPtr)->setPostValueInt("TimeToLive", 50);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
	}
	
	// The keypress command needs to create an Event with three parameters
	if ([inputKeyCode doubleValue] > 0)
	{
		eh2_EventPtr *eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");	
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command",4);
		(*eventPtr)->setPostValueInt("Code", (int) [inputKeyCode doubleValue]);
		(*eventPtr)->setPostValueInt("Repeat", (int) [inputRepeatPort doubleValue]);
		(*eventPtr)->setPostValueInt("ScanCode", (int) [inputScanCodePort doubleValue]);
		(*eventPtr)->setPostValueInt("TimeToLive", 1000);
		NSLog(@"Putting a text event: %i",(int) [inputScanCodePort doubleValue]);
		(*eh)->putEvent (*eventPtr);
		//sendEvent = false;
		delete eventPtr;
		[inputKeyCode setDoubleValue:0];
	}

	// The change profile command should only be changed if the profile number is really different
	if (([inputProfileNumber doubleValue] != lastInputProfileNumber) && ((int) [inputProfileNumber doubleValue] != 0))
	{
		eh2_EventPtr *eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");	
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command",12);
		(*eventPtr)->setPostValueInt("ProfileNo", (int)[inputProfileNumber doubleValue]);
		(*eventPtr)->setPostValueInt("TimeToLive",1000);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
	}
	
	if ([inputCaptureKeys booleanValue]  == TRUE && [inputCaptureKeys booleanValue] != lastInputCaptureKeys) 
	{
		NSLog(@"Start Key Capture");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 10);
		// the "event package" is ready -> post it to the Event Heap
		(*eventPtr)->setPostValueInt("TimeToLive", 1000);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;

	}else if ([inputCaptureKeys booleanValue]  == FALSE && [inputCaptureKeys booleanValue] != lastInputCaptureKeys) 
	{

		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
		(*eventPtr)->setPostValueInt("Command", 11);
		// the "event package" is ready -> post it to the Event Heap
		(*eventPtr)->setPostValueInt("TimeToLive", 1000);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
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
