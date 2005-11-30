//
//  ServoController.mm
//  QCiStuff
//
//  Created by RenŽ Reiners on 11/29/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "ServoController.h"

@interface ServoController (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation ServoController

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [ServoControllerUI class];
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
        // If your patch is a parent patch, like 3D Transformation,
        // you will allow subpatches, otherwise FALSE.
	return FALSE;
}
	
- (id)initWithIdentifier:(id)fp8
{

	NSLog (@"Initializing ServoController");
	// Do your initialization of variables here 
	// initialize the Event Heap client library
	// you can specify appName and deviceName, but you don't have to
	//eh2_init ("iStuffQuartzPlugin", NULL);
	eh2_init ("iStuffQuartzPlugin", "coltrane");

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
	
        // Read/Write any ports in here too.
		// only if one of the input ports changed, a new event has to be posted
		// and the other operations have to be performed
				int motor1Position = (int) [inputPosMot1 doubleValue];
				int motor2Position = (int) [inputPosMot2 doubleValue];
				int motor3Position = (int) [inputPosMot3 doubleValue];
				int motor4Position = (int) [inputPosMot4 doubleValue];

			if ((oldMotor1Position != [inputPosMot1 doubleValue]) ||
			    (oldMotor2Position != [inputPosMot2 doubleValue]) ||
				(oldMotor3Position != [inputPosMot3 doubleValue]) ||
				(oldMotor4Position != [inputPosMot4 doubleValue]))
				{
			
				NSLog(@"At least one input has changed --> post new event");
				
				//create a new event object
				eh2_EventPtr *eventPtr = new eh2_EventPtr;
				(*eventPtr) = eh2_Event::cs_create ("ServoController");
		//	*eventPtr->setTimeToLive (50);
	// The TimeToLive should also be reduced in order to prevent Event Heap flooding...
			
			// The controller is able to control 4 different motors
			// The acceleration and speed of each motor can be controlled
			// Therefore everytime an event is posted, two fields for each motor are posted 
			// inside the event. This results in 8  fields.
			
			// Conversion for the input values:
			// In order to protect the servos, position values
			//may only range from 30 to 215
			
							
				if ( motor1Position < 30) {motor1Position = 30;};
				if ( motor2Position < 30) {motor2Position = 30;};
				if ( motor3Position < 30) {motor3Position = 30;};
				if ( motor4Position < 30) {motor4Position = 30;};
				if ( motor1Position > 215) {motor1Position = 215;};
				if ( motor2Position > 215) {motor2Position = 215;};
				if ( motor3Position > 215) {motor3Position = 215;};
				if ( motor4Position > 215) {motor4Position = 215;};
				
				(*eventPtr)->setPostValueInt("PosMot1", motor1Position);
				(*eventPtr)->setPostValueInt("PosMot2", motor2Position);
				(*eventPtr)->setPostValueInt("PosMot3", motor3Position);
				(*eventPtr)->setPostValueInt("PosMot4", motor4Position);


						
			/*
			(*eventPtr)->setPostValueInt("PosMot1", (int) [inputPosMot1 doubleValue]);
			(*eventPtr)->setPostValueInt("PosMot2", (int) [inputPosMot2 doubleValue]);
			(*eventPtr)->setPostValueInt("PosMot3", (int) [inputPosMot3 doubleValue]);
			(*eventPtr)->setPostValueInt("PosMot4", (int) [inputPosMot4 doubleValue]);
			
			*/
			/* The following would be helpful with a Motor Controller
			(*eventPtr)->setPostValueInt("Motor1Speed", (int) [inputSpeedMot1 doubleValue]);
			(*eventPtr)->setPostValueInt ("Motor1Acceleration", (int) [inputAccMot1 doubleValue]);
			(*eventPtr)->setPostValueInt("Motor2Speed", (int) [inputSpeedMot2 doubleValue]);
			(*eventPtr)->setPostValueInt ("Motor2Acceleration", (int) [inputAccMot2 doubleValue]);
			(*eventPtr)->setPostValueInt("Motor3Speed", (int) [inputSpeedMot3 doubleValue]);
			(*eventPtr)->setPostValueInt ("Motor3Acceleration", (int) [inputAccMot3 doubleValue]);
			(*eventPtr)->setPostValueInt("Motor4Speed", (int) [inputSpeedMot4 doubleValue]);
			(*eventPtr)->setPostValueInt ("Motor4Acceleration", (int) [inputAccMot4 doubleValue]);
			*/
			
			// the "event package" is ready -> post it to the Event Heap
				(*eventPtr)->setPostValueInt("TimeToLive", 50);
				(*eh)->putEvent (*eventPtr);
				delete eventPtr;

			// keep the old values and only post a new event if an input really changes! :)
			oldMotor1Position = [inputPosMot1 doubleValue];
			oldMotor2Position = [inputPosMot2 doubleValue];
			oldMotor3Position = [inputPosMot3 doubleValue];
			oldMotor4Position = [inputPosMot4 doubleValue];
			}
			// the demanded RETURN-value
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
