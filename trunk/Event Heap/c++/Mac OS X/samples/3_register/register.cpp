#include <eh2.h>
#include <idk_th.h>

class EventLogger : public idk_th_Thread {
private:
	eh2_EventRegistrationPtr m_erPtr;
	idk_string m_name;

protected:
	EventLogger(const char* name) {
		m_name = name;
	}

	void setRegistration(const eh2_EventRegistrationPtr& erPtr) {
		m_erPtr = erPtr;
	}

public:
	void run() {
		fprintf(stderr, "[%s] started\n", m_name.c_str());
		try {
			while (1) {
				eh2_EventPtr eventPtr = m_erPtr->waitForResult(NULL);
				fprintf(stderr, "[%s] type='%s' seq='%d'\n",
					m_name.c_str(),
					eventPtr->getEventType(),
					eventPtr->getPostValueInt(eh2_Consts::FN_SEQUENCENUM)
					);
			}
		}
		catch (idk_th_InterruptedException&) {
			// interrupted by deregister
		}
		fprintf(stderr, "[%s] finished\n", m_name.c_str());
	}

	void quit() {
		m_erPtr->deregister();
	}
};

IDK_UT_SHAREDPTR_DECL(EventLogger);

class AllEventLogger : public EventLogger {
public:
	AllEventLogger(eh2_EventHeap* eh) : EventLogger("AllEventLogger") {
		// register a query
		eh2_EventRegistrationPtr erPtr = eh->registerForAll();
		setRegistration(erPtr);
	}
};

class MyEventLogger : public EventLogger {
public:
	MyEventLogger(eh2_EventHeap* eh) : EventLogger("MyEventLogger") {
		// register a query
		eh2_EventCollectionPtr templatesPtr = eh2_EventCollection::cs_create();
		templatesPtr->add(eh2_Event::cs_create("MyEventType"));
		eh2_EventRegistrationPtr erPtr = eh->registerForEvents(templatesPtr);

		setRegistration(erPtr);
	}
};

void run()
{
	// create an EventHeap object as usual.
	eh2_EventHeapFactory* ehf = eh2_EventHeapFactory::cs_getInstance();
	eh2_EventHeapPtr ehPtr =
		ehf->createEventHeap(NULL, "localhost", -1, 1/*multithread safe*/);

	EventLoggerPtr allLoggerPtr = new AllEventLogger(ehPtr);
	EventLoggerPtr myLoggerPtr = new MyEventLogger(ehPtr);
	allLoggerPtr->start();
	myLoggerPtr->start();

	fprintf(stderr, "press ENTER to gracefully shutdown the loggers\n");
	getchar();

	allLoggerPtr->quit();
	myLoggerPtr->quit();

	allLoggerPtr->join();
	myLoggerPtr->join();

	fprintf(stderr, "press ENTER again to quit the program\n");
	getchar();
}

int main()
{
	eh2_init(NULL, NULL);
	run();
	eh2_finalize();
	return 0;
}
