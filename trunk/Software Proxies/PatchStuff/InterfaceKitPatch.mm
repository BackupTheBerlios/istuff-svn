//
//  RFIDReader.m
//  QCiStuff
//
//  Created in by Ren√© Reiners on 11/25/05.
//	Template work done by Raphael Ballagas
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "InterfaceKitPatch.h"

@interface InterfaceKitPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation InterfaceKitPatch

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
	return [InterfaceKitPatchUI class];
}

+ (int)executionMode
{
        // As the InterfaceKitPatch only post values of read tags, it is a Source
        //  1 - Renderer, Environment - pink title bar
        //  2 - Source, Tool, Controller - blue title bar
        //  3 - Numeric, Modifier, Generator - green title bar
        return 2;
}
	
+ (BOOL)allowsSubpatches
{
        // If your patch is a parent patch, like 3D Transformation,
        // you will allow subpatches, otherwise FALSE.
	return FALSE; //no subpatches for a source
}
	
- (id)initWithIdentifier:(id)fp8
{

	NSLog (@"Initializing InterfaceKitPatch");
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
	NSLog(@"About to create EH for InterfaceKit");
	NSString *serverName = @"localhost";
	[self createEventHeap:NULL atServer:serverName atPort:4535];
	
	NSLog (@"created EH for InterfaceKit");

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

	NSLog (@"thread waitForEvents activated");
}



// deactivate the thread that waits for Event Heap events
//
- (void) stopReceivingEvents
{
	// set the flag to deactivate the thread
	waitForEvents = FALSE;
}



// create the event templates you want to receive from the Event Heap
//
/* - (void) defineEventsToReceive
{
	// create a new event object to use as template
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	
	templatePtr->setEventType ("CarbonSpeech");		// yet another way to set event type
	//templatePtr->setTemplateValueInt ("AGE", 30);   // search for this
	
	// the following does exactly the same as above in the normalized way.
	// first, create (or retrieve if exists) a field.
	// then, set the value to the field.
	//eh2_Field* field;
	//field = templatePtr->allocateField("AGE", eh2_FieldType::cs_int());
	//field->setTemplateValueInt(30);

	// if you want to set the value to some special value like FORMAL,
	// you should do as follows, using the normalized way mentioned above.
	//field = templatePtr->allocateField("NAME", eh2_FieldType::cs_string());
	//field->setTemplateValueType(FVT_FORMAL);

	// as long as you are sure that the field is already exist, you can set
	// special value like this also.  note that it raises an error if the
	// field does not exist, unlike when setting actual values.
	//templatePtr->setTemplateValueType("NAME", FVT_FORMAL);

	// invoke the waitForEvent operation.
	// again, you must keep the returned event in a smart pointer.
	//eh2_EventPtr resultEventPtr = eh->waitForEvent(templatePtr);
} */



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
	templatePtr->setEventType ("PhidgetInterfaceKit");

	// the thread exits if waitForEvents becomes FALSE
	while (waitForEvents) {
			//	tag = @"Was gefangen!!!";
		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);
		int analogPort;
		analogPort = resultEventPtr->getPostValueInt("Index");
		int portValue;
		portValue = resultEventPtr->getPostValueInt("Value");
		// Here depending on Index, the corresponding AnalogPortValue must be set.
		
		switch (analogPort) {
		case 0:
			 [outputAnalogReading0 setDoubleValue:portValue];
			 NSLog(@"Index 0");
			 break;
		case 1:
			 [outputAnalogReading1 setDoubleValue:portValue];
			 NSLog(@"Index 1");
			 break;
		case 2:
			 [outputAnalogReading2 setDoubleValue:portValue];
			 break;
		case	 3:
			 [outputAnalogReading3 setDoubleValue:portValue];
			 break;
		case	 4:
			 [outputAnalogReading4 setDoubleValue:portValue];
			 break;
		case	 5:
			 [outputAnalogReading5 setDoubleValue:portValue];
			 break;
		case	 6:
			 [outputAnalogReading6 setDoubleValue:portValue];
			break;
		case	 7:
			 [outputAnalogReading6 setDoubleValue:portValue];
			break;

		default:NSLog(@"Index Value not valid: probably out of bounds");
			break;
		}

		NSLog(@"InterfaceKitPatch received");
		// print debug info
		//const char* field1, *field2;
		//field1 = resultEventPtr->getPostValueString ("SequenceNum");
		//field2 = resultEventPtr->getPostValueString ("SessionID");
		//NSLog (@"event received, seqNum %s, sessID %s", field1, field2);

		// report the received event to MyController
		//[myController processEvent:resultEventPtr];*/
	}

	NSLog (@"thread waitForEvents deactivated");

	[localPool release];
}

/* is this method really needed here?

// create a new event
//
- (eh2_EventPtr *) createEvent: (char*)eventName
{
	//create a new event object
	eh2_EventPtr *eventPtr = new eh2_EventPtr;
	
	(*eventPtr) = eh2_Event::cs_create ("SpeechServer");
	NSLog(@"CREATE EVENT AUFGERUFENNN ACHTUNG!!!");
	return eventPtr;



}

*/	
@end
