//
//  MobilePhone.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhone.h"

@interface MobilePhone (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation MobilePhone

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [MobilePhoneUI class];
}

+ (int)executionMode
{
        // I have found the following execution modes:
        //  1 - Renderer, Environment - pink title bar
        //  2 - Source, Tool, Controller - blue title bar
        //  3 - Numeric, Modifier, Generator - green title bar
        return 1;
}
	
+ (BOOL)allowsSubpatches
{
	return FALSE;
}
	
- (id)initWithIdentifier:(id)fp8
{
	
	NSLog (@"Initializing MobilePhone");
	// Do your initialization of variables here 
	// initialize the Event Heap client library
	eh2_init ("iStuffQuartzPlugin", "localhost");
	
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

	
	// create the Event Heap instance for the client
	NSString *serverName = @"localhost";
	[self createEventHeap:NULL atServer:serverName atPort:4535];
	
	return [super initWithIdentifier:fp8];
}
	
- (void)dealloc
{	
	eh2_finalize ();
	[super dealloc];
}
	
- (id)setup:(id)fp8
{
	// setup vars here
	return fp8;
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{

	// This is where the execution of your patch happens.
        // Everything in this method gets executed once
        // per 'clock cycle', which is available in fp12 (time).
	
        // fp8 is the QCOpenGLContext*.  Don't forget to set
        // it before you start drawing.  
	

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
		(*eventPtr)->setPostValueInt("Command", 2);
					// the "event package" is ready -> post it to the Event Heap
				//(*eventPtr)->setPostValueInt("TimeToLive", 1000);
				(*eh)->putEvent (*eventPtr);
				delete eventPtr;
	}
	
	if ([inputBacklightOff booleanValue]  == TRUE && [inputBacklightOff booleanValue] != lastInputBacklightOff) 
	{
		NSLog(@"BackLightOff");
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
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
		(*eventPtr)->setPostValueInt("Command",4);
		(*eventPtr)->setPostValueInt("Code", (int) [inputKeyCode doubleValue]);
		(*eventPtr)->setPostValueInt("Repeat", (int) [inputRepeatPort doubleValue]);
		(*eventPtr)->setPostValueInt("ScanCode", (int) [inputScanCodePort doubleValue]);
		(*eventPtr)->setPostValueInt("TimeToLive", 50);
		(*eh)->putEvent (*eventPtr);
		//sendEvent = false;
		delete eventPtr;
	}

	// The change profile command should only be changed if the profile number is really different
	if (([inputProfileNumber doubleValue] != lastInputProfileNumber) && ((int) [inputProfileNumber doubleValue] != 0))
	{
		eh2_EventPtr *eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");	
		(*eventPtr)->setPostValueInt("Command",7);
		(*eventPtr)->setPostValueString("Path","Z:\\System\\Apps\\Profileapp\\profileapp.app");
		(*eventPtr)->setPostValueInt("TimeToLive",1000);
		(*eh)->putEvent (*eventPtr);
		delete eventPtr;
		// Now check what profile number was received and post it to the event heap.
		for (int i= (int)[inputProfileNumber doubleValue]; i > 1; i--) {
		    eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
			(*eventPtr)->setPostValueInt("Command",4);
			(*eventPtr)->setPostValueInt("Code", 63498);
			(*eventPtr)->setPostValueInt("Repeat", (int) [inputRepeatPort doubleValue]);
			(*eventPtr)->setPostValueInt("ScanCode", (int) [inputScanCodePort doubleValue]);
			(*eventPtr)->setPostValueInt("TimeToLive", 1000);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
		}
		
		for (int i= 0; i < 2; i++) {
			eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
			(*eventPtr)->setPostValueInt("Command",4);
			(*eventPtr)->setPostValueInt("Code", 63557);
			(*eventPtr)->setPostValueInt("Repeat", (int) [inputRepeatPort doubleValue]);
			(*eventPtr)->setPostValueInt("ScanCode", (int) [inputScanCodePort doubleValue]);
			(*eventPtr)->setPostValueInt("TimeToLive", 1000);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
		}
		
		eventPtr = new eh2_EventPtr;
		(*eventPtr) = eh2_Event::cs_create ("iStuffMobile");
		(*eventPtr)->setPostValueInt("Command",8);
		(*eventPtr)->setPostValueString("Path","Profiles");
		(*eventPtr)->setPostValueInt("TimeToLive",1000);
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

	
		// Yes, the method ran successfully
        return TRUE;
}


// create the Event Heap instance for the client
//
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *)serverName atPort:(int)port
{
	// first, get the Event Heap factory
	// you are not responsible of releasing the reference to it
	eh2_EventHeapFactory *factory = eh2_EventHeapFactory::cs_getInstance ();
	
	// then, ask the factory for creating the Event Heap client instance
	// you have the ownership of the returned object, so you have to keep it in a smart pointer
	// specify source name, event heap host (e.g., "localhost"), and default port

	// allocate memory for Event Heap client
	eh = new (eh2_EventHeapPtr);
	
	//(*eh) = factory->createEventHeap (NULL, "localhost", 4535);
	(*eh) = factory->createEventHeap ([sourceName cString], [serverName cString], port);
}

@end
