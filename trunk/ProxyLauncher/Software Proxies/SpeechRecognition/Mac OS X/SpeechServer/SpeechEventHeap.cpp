/*
 *  SpeechEventHeap.cpp
 *  CarbonSpeechTest
 *
 *  Created by Daniel Spelmezan on Thu Jun 03 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */

#include "SpeechEventHeap.h"


// constructor with event heap initialization
SpeechEventHeap :: SpeechEventHeap () {

	// initialize the event heap client library
	// you can specify appName and deviceName, but you don't have to
	eh2_init ("SpeechEventHeap", NULL);
	
	// set up the tracer if you want to trace the activity of the library
	
	// create a tracer, keep it in a smart pointer
	eh2_TracerPtr tracePtr = eh2_Tracer::cs_create (idk_io_FileOutStream::cs_createBufferedByFileName ("trace.txt"), TMM_ALL);
	
	// set the tracer
	eh2_Tracer::cs_setTracer (tracePtr);
}



// destructor
SpeechEventHeap :: ~SpeechEventHeap () {

	// finalize the library
	eh2_finalize ();
}



// create the event heap instance for the client
eh2_EventHeapPtr SpeechEventHeap :: createEventHeap () {

	// first, get the event heap factory
	// you are not responsible of releasing the reference to it
	eh2_EventHeapFactory *factory = eh2_EventHeapFactory::cs_getInstance ();
	
	// then, ask the factory for creating the event heap client instance
	// you have the ownership of the returned object, so you have to keep it in a smart pointer
	// specify source name, event heap host, and default port
	eh2_EventHeapPtr eventHeapPtr = factory->createEventHeap (NULL, "localhost", -1);
	
	//return the event heap pointer	
	return eventHeapPtr;
}



// put an event to the event heap
void SpeechEventHeap :: putEvent (eh2_EventHeap* eh) {

	// this function does not have th eownership of the event heap but only uses it,
	// so the parameter type should be normal pointer

	//create a new event object, keep it in smart pointer
	eh2_EventPtr eventPtr = eh2_Event::cs_create ("MyEventType");
	
	// set values to the event like this
	eventPtr->setPostValueString ("NAME", "Daniel");
	eventPtr->setPostValueInt ("AGE", 27);

	// then, put it
	eh->putEvent (eventPtr);
}



// retrieve values from an event
void SpeechEventHeap :: printEvent (const eh2_Event* event) {

	// get the type of the event
	const char* eventType = event->getEventType ();
	
	if (strcmp (eventType, "NAME") != 0) {
		printf ("unknown event type: %s\n", eventType);
	}
	
	// get the event value
	// if something is wrong, an exception should occur
	const char* name = event->getPostValueString ("NAME");
	
	int age = -1;
	const eh2_Field* field = event->getField ("AGE");
	if (field == NULL) {
		// the event has no age field
	}
	else if (! field->getType()->equals(eh2_FieldType::cs_int())) {
		// the field is not expected type
	}
	else if (field->isPostValueNull ()) {
		// the content of the value is null
	}
	else {
		// get the int value
		age = field->getPostValueInt ();
	}
	
	// you can access the standard fields by using eh2_Consts::FN_XXX
	int seq = event->getPostValueInt (FN_SEQUENCENUM);
	const char* source = event->getPostValueString (FN_SOURCE);
	
	printf ("SOURCE=%s SEQ=%d NAME=%s AGE=%d\n", source, seq, name, age);
}



// wait for events
void SpeechEventHeap :: waitForEvent (eh2_EventHeap* eh) {

	// create a new event object to use as template
	eh2_EventPtr templatePtr = eh2_Event::cs_create ();
	templatePtr->setEventType ("MyEventType");  // yet another way to set event type
	
	templatePtr->setTemplateValueInt ("AGE", 30);   // search for this
	
	// invoke the waitForEvent operation
	// you must keep the returned event in a smart pointer
	eh2_EventPtr resultEventPtr = eh->waitForEvent (templatePtr);
	
	// print the result
	printEvent (resultEventPtr);
}



// handle event collections
void SpeechEventHeap :: getAll (eh2_EventHeap* eh) {

	// invoke getAll operation, which results in a collection of events
	// keep in smart pointer
	eh2_EventCollectionPtr eventsPtr = eh->getAll ();

	for (int i = 0; i < eventsPtr->size(); i++) {
		// use get(i) method to see an event in the collection
		const eh2_Event* event = eventsPtr->get(i);
		// or use s amrt pointer to assign the return value of get(i)
		// in case you want to carry the event after the collection is discarded
		// eh2_EventPtr eventPtr = eventsPtr->geet(i);
		
		printEvent (event);
	}
}