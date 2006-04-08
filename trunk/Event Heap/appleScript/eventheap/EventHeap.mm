//
//  EventHeap.mm
//  SpeechServer
//
//  Created by Daniel Spelmezan on Fri Jun 04 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import "EventHeap.h"

@implementation EventHeap

- (id) init
{
	if (self == [super init]) {
		// no Event Heap instance created yet
		eh = NULL;
		
		// initialize Event Heap client library and set up tracer
		[self initialize];
	}
	
	return self;
}



- (void) dealloc
{
	// balance call to "new (eh2_EventHeapPtr)" in createEventHeap
	if (eh)
		delete (eh);

	[self finalize];
}



// initialize the Event Heap client library and set up tracer
//
- (void) initialize
{
	// initialize the Event Heap client library
	// you can specify appName and deviceName, but you don't have to
	eh2_init ("SpeechServer", NULL);
	
	// THE TRACER DOES NOT WORK OUTSIDE OF XCODE!
	// EXECUTABLE WILL START FROM TERMINAL BUT NOT IF DOUBLE-CLICKED IN FINDER!
	// WHY?

	// set up the tracer if you want to trace the activity of the library
	// create a tracer, keep it in a smart pointer
	//eh2_TracerPtr tracePtr = eh2_Tracer::cs_create (idk_io_FileOutStream::cs_createBufferedByFileName ("SpeechServer EH trace.txt"), eh2_Consts::TMM_ALL);
	
	// set the tracer
	//eh2_Tracer::cs_setTracer (tracePtr);
	
	// create the Event Heap instance for the client
	/*
	NSString *serverName = @"127.0.0.1";
	if ([[[NSProcessInfo processInfo] arguments] count] >= 2){
		serverName = [[[NSProcessInfo processInfo] arguments] objectAtIndex:1];
	}
	[self createEventHeap:NULL atServer:serverName atPort:4535];*/
	
	// activate the thread that receives EH events
	[self startReceivingEvents];
}



// finalize the Event Heap client library
//
- (void) finalize
{
	// stop thread that receives EH events
	[self stopReceivingEvents];
	
	eh2_finalize ();
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



// create the event templates you want to receive from the Event Heap
//
/* - (void) defineEventsToReceive
{
	// create a new event object to use as template
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	
	templatePtr->setEventType ("MyType");		// yet another way to set event type
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
	
	
	
	// define the type of events you want to receive
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("My Event");

	// the thread exits if waitForEvents becomes FALSE
	/*
	NSLog (@"waiting for EH events...");
	while (waitForEvents) {
		// invoke the waitForEvent operation, keep the returned event in a smart pointer
		eh2_EventPtr resultEventPtr = (*eh)->waitForEvent (templatePtr);

		// print debug info
		//const char* field1, *field2;
		//field1 = resultEventPtr->getPostValueString ("SequenceNum");
		//field2 = resultEventPtr->getPostValueString ("SessionID");
		//NSLog (@"event received, seqNum %s, sessID %s", field1, field2);

		// report the received event to MyController
		[myController processEvent:resultEventPtr];
	}
	NSLog (@"thread waitForEvents deactivated");
	*/
	[localPool release];
}



// create a new event
//
- (eh2_EventPtr *) createEvent: (NSString *)eventTypeName
{
	//create a new event object
	eh2_EventPtr *eventPtr = new eh2_EventPtr;
	
	(*eventPtr) = eh2_Event::cs_create ([eventTypeName cString]);
	
	return eventPtr;
}



// post the event to the heap
//
- (void) postEvent:(eh2_EventPtr *)eventPtr
{
	(*eh)->putEvent (*eventPtr);
	
	// balance call to "new eh2_EventPtr" in createEvent
	delete eventPtr;
}



// put a key/value pair to the event, value is a string
//
- (void) putStrKey:(char *)key andStrValue:(char *)value toEvent:(eh2_EventPtr *)eventPtr
{
	(*eventPtr)->setPostValueString (key, value);
}



// put a key/value pair to the event, value is an int
//
- (void) putStrKey:(char *)key andIntValue:(int)value toEvent:(eh2_EventPtr *)eventPtr
{
	(*eventPtr)->setPostValueInt (key, value);
}

@end