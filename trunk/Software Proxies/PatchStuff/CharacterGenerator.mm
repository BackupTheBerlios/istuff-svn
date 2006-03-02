//
//  CharacterGenerator.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners on 01/07/05.
//	Template work done by Raphael Ballagas
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
// This patch waits for "Text Event" from the event heap and directs them
// to the output ports as integers with the ACII code number. As only events are processed, no input ports are needed.

#import "CharacterGenerator.h"

@interface CharacterGenerator (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation CharacterGenerator

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [CharacterGeneratorUI class];
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
	
	setOutputPort = false;
	[outputKeyStroke setDoubleValue:-1];
	[outputPermanentASCIICode setDoubleValue:-1];
	
	// create the Event Heap instance for the client
//	NSString *serverName = @"localhost";
//	[self createEventHeap:NULL atServer:serverName atPort:4535];

	// activate the thread that receives EH events
	[self startReceivingEvents];

	return [super initWithIdentifier:fp8];
}
	
- (void)dealloc
{
	// stop thread that receives EH events
	[self stopReceivingEvents];
	NSLog(@"IN DEALLOC CHARACTERGEN");
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
		[outputKeyStroke setDoubleValue:[outputKeyStroke doubleValue]];
		setOutputPort = false;
	}
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
	
	NSString *serverName = @"localhost";
	[self createEventHeap:NULL atServer:serverName atPort:4535];

	
	NSLog (@"waiting for EH events...");
	
	// define the type of events you want to receive
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("TextEvent");

	// the thread exits if waitForEvents becomes FALSE
	while (waitForEvents) {

		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		
		// set the flag so that in the 'execute'-method the output port is set to the new value
		// after setting it, the flag is set to false again.
		// This allows posting one value per execution cycle
		setOutputPort = true;
		
		//read the character ASCII value from the event field
		int keyCode;
		keyCode = resultEventPtr->getPostValueInt("Character");
		[outputKeyStroke setDoubleValue:(double) keyCode];
		[outputPermanentASCIICode setDoubleValue:keyCode];
	
	}

	NSLog (@"thread waitForEvents deactivated");

	[localPool release];
}


@end
