//
//  TeleoPWMOut.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "TeleoPWMOut.h"

@interface TeleoPWMOut (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation TeleoPWMOut

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [TeleoPWMOutUI class];
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

	NSLog (@"Initializing TeleoPWMOut");
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

	// intialize variables
	lastInputPWMOut0=-1;
	lastInputPWMOut1=-1;
	
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
			
	
		if( [inputPWMOut0 doubleValue] != lastInputPWMOut0 ){
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
			(*eventPtr)->setPostValueInt ("ID", 0);
			(*eventPtr)->setPostValueInt ("VALUE", [inputPWMOut0 doubleValue]);
			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
			lastInputPWMOut0 = [inputPWMOut0 doubleValue];
		}
		
		if( [inputPWMOut1 doubleValue] != lastInputPWMOut1 ){
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("TELEO_PWMOUT");
			(*eventPtr)->setPostValueInt ("ID", 1);
			(*eventPtr)->setPostValueInt ("VALUE", [inputPWMOut1 doubleValue]);
			(*eventPtr)->setPostValueInt ("TimeToLive", 500);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
			lastInputPWMOut1 = [inputPWMOut1 doubleValue];
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

@end