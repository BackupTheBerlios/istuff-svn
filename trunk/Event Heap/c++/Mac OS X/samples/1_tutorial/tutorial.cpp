#include <eh2.h> // include eh2 package
#include <idk_io.h> // include idk_io package

class Tutorial : protected eh2_Consts
	// by inheriting eh2_Consts, you can omit prefix eh2_Const::
	// when you use constant values.
{
public:
	void initialize()
	{
		// initialize the event heap client library.
		// you can specify appName and deviceName, but you don't have to.
		eh2_init(NULL, NULL);

		//
		// if you want to trace the activity of the library,
		// set up the tracer.
		//

		// create a tracer.  keep it in a smart pointer.
		eh2_TracerPtr tracerPtr = eh2_Tracer::cs_create(
			idk_io_FileOutStream::cs_createBufferedByFileName("trace.txt"),
			TMM_ALL
			);

		// set the tracer.
		eh2_Tracer::cs_setTracer(tracerPtr);
	}

	void finalize()
	{
		// gracefully finalize the library.
		eh2_finalize();
	}

	eh2_EventHeapPtr createEventHeap()
	{
		// at first, get the event heap factory.
		// you can get only the reference to the factory because it is the
		// singleton.  you are not responsible for releasing it.
		eh2_EventHeapFactory* factory = eh2_EventHeapFactory::cs_getInstance();

		// then, ask to the factory for creating the event heap client instance.
		// you have the ownership of the returned object, so you have to keep it
		// in smart pointer.
		eh2_EventHeapPtr eventHeapPtr =	factory->createEventHeap(
			NULL, // not specifying source name
			"localhost", // event heap host
			-1 // default port
			);

		// when you return an object with ownership, the return type must be
		// smart pointer.  the caller must receive it by smart pointer also.
		return eventHeapPtr;
	}

	void doPutEvent(eh2_EventHeap* eh)
	{
		// this function does not have the ownership of the event heap but only use it,
		// so the parameter type should be normal pointer.

		// create a new event object.  keep it in smart pointer.
		eh2_EventPtr eventPtr = eh2_Event::cs_create("MyEventType");
		
		// you can set values to the event like this.
		eventPtr->setPostValueString("NAME", "Tomoto Shimizu");
		eventPtr->setPostValueInt("AGE", 30);
		
		// then, put it.
		eh->putEvent(eventPtr);
		// (note the passed event may be modified since autoset values
		//  are set.  if you examine the event after this call, you will
		//  see the exact values which has been sent.)

		// let's put a couple more.

		eventPtr->setPostValueString("NAME", "Ryusuke Ito");
		eventPtr->setPostValueInt("AGE", 32);
		eh->putEvent(eventPtr);
		
		eventPtr->setPostValueString("NAME", "Itaru Nishizawa");
		eventPtr->setPostValueInt("AGE", 34);
		eh->putEvent(eventPtr);
		
	}

	void printEvent(const char* title, const eh2_Event* event)
	{
		// now let's discuss about how to retrieve values in a event.

		// you can get the type of this event like this.
		const char* eventType = event->getEventType();

		if (strcmp(event->getEventType(), "MyEventType") != 0) {
			// now we leave events which are not our concern.
			printf("%s: unknown event type %s\n", title, eventType);
			return;
		}

		// this is the easiest way to get a value.
		// if something is wrong, an exception should occur.
		const char* name = event->getPostValueString("NAME");
		
		// if you want to be more careful, the following is the complete way.
		int age = -1;
		const eh2_Field* field = event->getField("AGE");
		if (field == NULL) {
			// the event has no AGE field.
		}
		else if (! field->getType()->equals(eh2_FieldType::cs_int())) {
			// the field is not expected type.
		}
		else if (field->getPostValueType() != FVT_ACTUAL) {
			// the field does not have an actual value.
		}
		else if (field->isPostValueNull()) {
			// the content of the actual value is null.
		}
		else {
			// the field has a non-null actual value.
			age = field->getPostValueInt();
		}

		// you can access to standard fields by using eh2_Consts::FN_XXX.
		int seq = event->getPostValueInt(FN_SEQUENCENUM);
		const char* source = event->getPostValueString(FN_SOURCE);

		printf("%s: SOURCE=%s SEQ=%d NAME=%s AGE=%d\n", title, source, seq, name, age);

	}

	void printEventsInXML(const char* file, const eh2_EventCollection* events)
	{
		// this is a convenient way to debug -- outputs the events content
		// in XML format.

		// create an output stream
		idk_io_IByteOutStreamPtr outStreamPtr =
			idk_io_FileOutStream::cs_createBufferedByFileName(file);

		// create the event-to-XML converter
		eh2_EventToXMLPtr converterPtr = eh2_EventToXML::cs_create();

		converterPtr->convert(outStreamPtr, events);
	
	}

	void doWaitForEvent(eh2_EventHeap* eh)
	{
		// create a new event object to use as template.
		eh2_EventPtr templatePtr = eh2_Event::cs_create();
		templatePtr->setEventType("MyEventType"); // yet another way to set event type
		
		templatePtr->setTemplateValueInt("AGE", 30); // we'll search 30-year-old stuff.

		// the following does exactly the same as above in the normalized way.
		// first, create (or retrieve if exists) a field.
		// then, set the value to the field.
		eh2_Field* field;
		field = templatePtr->allocateField("AGE", eh2_FieldType::cs_int());
		field->setTemplateValueInt(30);

		// if you want to set the value to some special value like,
		// you should do as follows, using the normalized way mentioned above.
		field = templatePtr->allocateField("NAME", eh2_FieldType::cs_string());
		field->setTemplateValueType(FVT_FORMAL);

		// as long as you are sure that the field is already exist, you can set
		// special value like this also.  note that it raises an error if the
		// field does not exist, unlike when setting actual values.
		templatePtr->setTemplateValueType("NAME", FVT_FORMAL);

		// invoke the waitForEvent operation.
		// again, you must keep the returned event in a smart pointer.
		eh2_EventPtr resultEventPtr = eh->waitForEvent(templatePtr);
			// (note: during this call, the passed template may be modified
			//  since autoset values were supplied.  if you examine the template
			//  events after the call, you will see exact values which was sent
			//  to the server.)

		// we'll discuss about how to retrieve values in events in this function.
		printEvent("doWaitForEvent", resultEventPtr);
	}

	void doGetAll(eh2_EventHeap* eh)
	{
		// here you will see how to handle event collections.

		// invoke getAll operation.  it results a collection of events.
		// keep it in a smart pointer.
		eh2_EventCollectionPtr eventsPtr = eh->getAll();

		int i;
		for (i = 0; i < eventsPtr->size(); i++) {
			// use get(i) method to see an event in the collection.
			const eh2_Event* event = eventsPtr->get(i);
			// you can also use a smart pointer to assign the return value of get(i).
			// it is useful in case you want to "carry" the event still after the
			// collection is discarded.
			// e.g. eh2_EventPtr eventPtr = eventsPtr->get(i);

			printEvent("doGetAll", event);
		}

	}

	void doGetEvent2(eh2_EventHeap* eh)
	{
		// now let's see how to use a number of templates for getEvent etc.

		// create an event collection by yourself.
		eh2_EventCollectionPtr templatesPtr = eh2_EventCollection::cs_create();

		// create a template event.
		eh2_EventPtr templatePtr;
		templatePtr = eh2_Event::cs_create("MyEventType");
		templatePtr->setTemplateValueInt("AGE", 32);

		// add the template to the collection.  the template will obtain the
		// ownership of the passed event, so you may release your smart poitner.
		templatesPtr->add(templatePtr);

		// let's add another template.
		templatePtr = eh2_Event::cs_create("MyEventType");
		templatePtr->setTemplateValueInt("AGE", 34);
		templatesPtr->add(templatePtr);

		// then invoke getEvent.
		eh2_EventPtr resultEventPtr;
		resultEventPtr = eh->getEvent(templatesPtr, NULL);

		printEvent("doGetEvent2", resultEventPtr);

		// you can examine which templates matched to the retrieved event
		// by following the steps below.

		// create another event collection.
		eh2_EventCollectionPtr matchedTemplatePtr =	eh2_EventCollection::cs_create();

		// pass the collection as the 2nd argument of getEvent.
		resultEventPtr = eh->getEvent(templatesPtr, matchedTemplatePtr);

		if (resultEventPtr != NULL) {
			printEvent("doGetEvent2", resultEventPtr);

			// when an event is returned, the matched templates are set to
			// the matchedTemplate.
			printEventsInXML("matchedEventsOfDoGetEvents2.xml", matchedTemplatePtr);

		}
	}

};

int main(int argc, char* argv[]) {

	Tutorial test;

	test.initialize();

	try {
		eh2_EventHeapPtr eventHeapPtr = test.createEventHeap();
			// never forget to assign objects which you own to smart pointer.

		test.doPutEvent(eventHeapPtr);
			// you can pass smart pointers to a parameter whose type is normal
			// pointer.  it means you "show" (not "give") the object to the function.

		test.doWaitForEvent(eventHeapPtr);

		test.doGetAll(eventHeapPtr);

		test.doGetEvent2(eventHeapPtr);
	}
	catch (idk_ut_Exception& ex) {
		puts(ex.getMessage());
	}

	test.finalize();

	fprintf(stderr, "press ENTER to finish\n");
	getchar();

	return 0;
}
