//
//  SweepPatch.m
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "SweepPatch.h"
#import "string.h"

@interface SweepPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation SweepPatch

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [SweepPatchUI class];
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

	NSLog (@"Initializing");
	// Do your initialization of variables here 
	// initialize the Event Heap client library
	// you can specify appName and deviceName, but you don't have to
	eh2_init ("iStuffQuartzPlugin", NULL);

	// THE TRACER DOES NOT WORK OUTSIDE OF XCODE!
	// EXECUTABLE WILL START FROM TERMINAL BUT NOT IF DOUBLE-CLICKED IN FINDER!
	// WHY?

	// set up the tracer if you want to trace the activity of the library
	// create a tracer, keep it in a smart pointer
	//eh2_TracerPtr tracePtr = eh2_Tracer::cs_create (idk_io_FileOutStream::cs_createBufferedByFileName ("SpeechServer EH trace.txt"), eh2_Consts::TMM_ALL);
	
	// set the tracer
	//eh2_Tracer::cs_setTracer (tracePtr);
	
	// create the Event Heap instance for the client
	NSString *serverName = @"localhost";
	[self createEventHeap:NULL atServer:serverName atPort:4535];

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

	//NSLog (@"thread waitForEvents activated");
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
	templatePtr->setEventType ("iPhone");

	// the thread exits if waitForEvents becomes FALSE
	while (waitForEvents) {
		int dX, dY;
		double drZ;
		
		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		
		NSLog(@"Received Event");
		char* type = (char*) resultEventPtr->getPostValueString("type");
	
		if(type != NULL){
			NSLog(@"type has data: %s", type);
			if( strcmp(type, "translation") == 0){
				dX = resultEventPtr->getPostValueInt("dX");
				dY = resultEventPtr->getPostValueInt("dY");
				[outputdX setDoubleValue:dX];
				[outputdY setDoubleValue:dY];
			} else if (strcmp(type, "rotation") == 0){
				drZ = resultEventPtr->getPostValueDouble("angle");
				[outputdrZ setDoubleValue:drZ];
			} else if (strcmp(type, "click") == 0){
				char* state = (char*) resultEventPtr->getPostValueString("state");
				if( strcmp(state, "pressed") == 0){
					[outputClick setBooleanValue:TRUE];
				}else{
					[outputClick setBooleanValue:FALSE];				
				}
				
			} 
			/*else if (strcmp(type, "code")){
				[code initWithCString:resultEventPtr->getPostValueString("code") encoding:NSASCIIStringEncoding];
				targetX = resultEventPtr->getPostValueInt("targetX");
				targetY = resultEventPtr->getPostValueInt("targetY");
			}*/
		}
		
	}

	NSLog (@"thread waitForEvents deactivated");

	[localPool release];

}



@end
