//
//  SmartItsSensor.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners on 01/07/05.
//	Template work done by Raphael Ballagas
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
// This patch waits for "Text Event" from the event heap and directs them
// to the output ports as integers with the ACII code number. As only events are processed, no input ports are needed.

#import "SmartItsSensor.h"

@interface SmartItsSensor (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation SmartItsSensor

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [SmartItsSensorUI class];
}

+ (int)executionMode
{
        // As the Character Generator only post values of pressed keys, it is a Source
        //  1 - Renderer, Environment - pink title bar
        //  2 - Source, Tool, Controller - blue title bar
        //  3 - Numeric, Modifier, Generator - green title bar
        return 2;
}
	
+ (BOOL)allowsSubpatches
{
	return FALSE; //no subpatches for a source
}
	
- (id)initWithIdentifier:(id)fp8
{
	// Do your initialization of variables here 
	// initialize the Event Heap client library
	eh2_init ("iStuffQuartzPlugin", "localhost");
	
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
    	
		// if a new Character Event was received, the code value has to be posted once
		// After posting, the port is set back to the "illegal" value -1
		return TRUE;
}


// create the Event Heap instance for the client

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

- (void) startReceivingEvents
{
	// set the flag to activate the thread
	waitForEvents = TRUE;
	
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
	templatePtr->setEventType ("Particle_Packet");

	// the thread exits if waitForEvents becomes FALSE
	while (waitForEvents) {

		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		
		// set the flag so that in the 'execute'-method the output port is set to the new value
		// after setting it, the flag is set to false again.
		// This allows posting one value per execution cycle
		
		// Read the values from the different fields of the events
		// The checks are necessary because not every field is created inside an event
		// That depends on the attached sensors. The proxy cares about that. This is a general patch
		// that only post the values if they exist
		
		[outputSourceID setStringValue:[NSString stringWithCString:resultEventPtr->getPostValueString("ParticleSrcId")]];
		
		if ( resultEventPtr->fieldExists("sgx") )
		{ [outputSGX setDoubleValue:(double) resultEventPtr->getPostValueInt("sgx")]; }
		if ( resultEventPtr->fieldExists("sgy") )
		{ [outputSGY setDoubleValue:(double) resultEventPtr->getPostValueInt("sgy")]; }
		if ( resultEventPtr->fieldExists("sgz") )
		{ [outputSGZ setDoubleValue:(double) resultEventPtr->getPostValueInt("sgz")]; }
		if ( resultEventPtr->fieldExists("sli") )
		{ [outputSLI setDoubleValue:(double) resultEventPtr->getPostValueInt("sli")]; }
		if ( resultEventPtr->fieldExists("ste") )
		{ [outputSTE setDoubleValue:(double) resultEventPtr->getPostValueInt("ste")]; }
		if ( resultEventPtr->fieldExists("sfc") )
		{ [outputSFC setDoubleValue:(double) resultEventPtr->getPostValueInt("sfc")]; }
		if ( resultEventPtr->fieldExists("sau") )
		{ [outputSAU setDoubleValue:(double) resultEventPtr->getPostValueInt("sau")]; }
		if ( resultEventPtr->fieldExists("ssw") )
		{ [outputSSW setDoubleValue:(double) resultEventPtr->getPostValueInt("ssw")]; }
		if ( resultEventPtr->fieldExists("svc") )
		{ [outputSVC setDoubleValue:(double) resultEventPtr->getPostValueInt("svc")]; }
	NSLog(@"Event processed!");
	}

	NSLog (@"thread waitForEvents deactivated");

	[localPool release];
}


@end
