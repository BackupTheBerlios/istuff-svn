//
//  PowerbookTiltSensorPatch.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "MobilePhoneKeyListener.h"

@interface MobilePhoneKeyListener (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation MobilePhoneKeyListener

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [MobilePhoneKeyListenerUI class];
}

+ (int)executionMode
{
        // I have found the following execution modes:
        //  1 - Renderer, Environment - pink title bar
        //  2 - Source, Tool, Controller - blue title bar
        //  3 - Numeric, Modifier, Generator - green title bar
        return 2;
}
	
+ (BOOL)allowsSubpatches
{
        // If your patch is a parent patch, like 3D Transformation,
        // you will allow subpatches, otherwise FALSE.
	return FALSE;
}
	
- (id)initWithIdentifier:(id)fp8
{

	NSLog (@"Initializing PowerbookTiltSensor");
	// Do your initialization of variables here 
	// initialize the Event Heap client library
	// you can specify appName and deviceName, but you don't have to
	//eh2_init ("iStuffQuartzPlugin", NULL);
	eh2_init ("iStuffQuartzPlugin", "localhost");
	
	setOutputPort = false;
	[outputKeyStroke setDoubleValue:-1];


	// THE TRACER DOES NOT WORK OUTSIDE OF XCODE!
	// EXECUTABLE WILL START FROM TERMINAL BUT NOT IF DOUBLE-CLICKED IN FINDER!
	// WHY?

	// set up the tracer if you want to trace the activity of the library
	// create a tracer, keep it in a smart pointer
	//eh2_TracerPtr tracePtr = eh2_Tracer::cs_create (idk_io_FileOutStream::cs_createBufferedByFileName ("SpeechServer EH trace.txt"), eh2_Consts::TMM_ALL);
	
	// set the tracer
	//eh2_Tracer::cs_setTracer (tracePtr);
	
	// create the Event Heap instance for the client
	NSLog(@"About to create EH");
	NSString *serverName = @"localhost";
	[self createEventHeap:NULL atServer:serverName atPort:4535];
	
	NSLog (@"created EH");

	// activate the thread that receives EH events
	[self startReceivingEvents];

	return [super initWithIdentifier:fp8];
}
	
- (void)dealloc
{
	// stop thread that receives EH events
	[self stopReceivingEvents];
	
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
	
        // Read/Write any ports in here too.
		
		// if a new Character Event was received, the code value has to be posted once
		// After posting, the port is set back to the "illegal" value -1
		
		if (!setOutputPort) {
		[outputKeyStroke setDoubleValue:0];
	}
	else {
		[outputKeyStroke setDoubleValue:(double)keyCode];
		setOutputPort = false;
	}
	
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



// activate the thread that waits for Event Heap events
//
- (void) startReceivingEvents
{
	// set the flag to activate the thread
	waitForEvents = TRUE;
	
	// define the type of events you want to receive
	//[self defineEventsToReceive];
	
	// create the thread that waits for events
	[NSThread detachNewThreadSelector:@selector(waitForEvents) toTarget:self withObject:nil];

	NSLog (@"thread waitForEvents activated");
}



// deactivate the thread that waits for Event Heap events
//
- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;
}

// thread waiting for EH events, so we won't block the recognition system
// the function call (*eh)->waitForEvent is blocking !
// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
//
- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];
	
	NSLog (@"waiting for EH events...");
	
	// define the type of events you want to receive
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("iStuffMobile");
	eh2_Field* field;
	field = templatePtr->allocateField("Activity", eh2_FieldType::cs_string());
	field->setTemplateValueType(eh2_EventConsts::FVT_FORMAL);
	//templatePtr->allocateField("Activity", eh2_FieldType::cs_string());

//	templatePtr->setTemplateValueString("Activity");
//	templatePtr->setTemplateValueString("Activity", "KeyPress");
//	templatePtr->setTemplateValueString("Activity", "KeyDown");
	
	NSLog(@"Right before WaitForEvents");
	
	
	while (waitForEvents) {
	eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);

	// set the flag so that in the 'execute'-method the output port is set to the new value
		// after setting it, the flag is set to false again.
		// This allows posting one value per execution cycle
	NSLog(@"Before GetPostValueString");
		const char* activity = resultEventPtr->getPostValueString("Activity");
		NSLog(@"The String was read and is checked now: %s", activity);
		if ([@"KeyDown" isEqualToString:[NSString stringWithUTF8String:activity]]) {
		 NSLog(@"In keyDown");
			[outputKeyPressed setBooleanValue:true];
		}
		
		if ([@"KeyPress" isEqualToString:[NSString stringWithUTF8String:activity]]) {
			//read the character ASCII value from the event field
			NSLog(@"In keyPress");
			setOutputPort = true;
			keyCode = resultEventPtr->getPostValueInt("KeyCode");
			[outputKeyStroke setDoubleValue:(double) keyCode];
			//[outputPermanentASCIICode setDoubleValue:keyCode];

		}
		
		if ([@"KeyUp" isEqualToString:[NSString stringWithUTF8String:activity]]) {
		 NSLog(@"In keyUp");
			[outputKeyPressed setBooleanValue:false];
		}
		
		
	
			
		
		// print debug info
		//const char* field1, *field2;
		//field1 = resultEventPtr->getPostValueString ("SequenceNum");
		//field2 = resultEventPtr->getPostValueString ("SessionID");
		//NSLog (@"event received, seqNum %s, sessID %s", field1, field2);

		// report the received event to MyController
		//[myController processEvent:resultEventPtr];
	}

	NSLog (@"thread waitForEvents deactivated");

	[localPool release];
}



// create a new event
//
- (eh2_EventPtr *) createEvent
{
	//create a new event object
	eh2_EventPtr *eventPtr = new eh2_EventPtr;
	
	(*eventPtr) = eh2_Event::cs_create ("SpeechServer");
	
	return eventPtr;
}

	
@end
