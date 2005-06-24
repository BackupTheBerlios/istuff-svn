#include <idk.h>
#include <idk_th.h>
#include <idk_ne.h>
#include <idk_ut.h>

//
// this is an example of "stateful" error handler.
// error handler of this type is spawned per each connection by
// an error handler factory and there's no chance to be called
// from multiple threads at the same time.
// this type is suitable for tasks which require variable states.
// this sample shows an implementation of stateful error handler
// which marks any servers unable to be connected for the specified
// duration as dead so that the app can check the server's status.
//

//
// exception to notify that the connection is failing for a long time.
//
class ConnectionTimedoutException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(ConnectionTimedoutException, idk_ut_Exception);
};

IDK_UT_EXCEPTION_IMPL(ConnectionTimedoutException, idk_ut_Exception);

//
// stateful error handler.
//
class TimeoutErrorHandler :
public idk_ut_RealObject,
public eh2_ConnectErrorHandler
	// Stateful handler does not need lock. 
{
	IDK_UT_REFCOUNTED_IMPL(); // this macro is necessary to mix-in
							  // eh2_ConnectErrorHandler interface
private:
	int m_timeoutDuration;
	idk_long m_timeoutAbsTime;
	int m_serverDead;

public:
	// the timeout value is passed by the factory
	TimeoutErrorHandler(int timeout) {
		m_timeoutDuration = timeout;
		m_timeoutAbsTime = 0;
		m_serverDead = 0;
	}

	int isServerDead() const { return m_serverDead; }

	virtual void startConnect(eh2_ErrorContext* ctx) {
		// calculates the absolute time of timeout
		m_timeoutAbsTime =
			idk_ut_SystemUtil::getCurrentTimeMillis() +
			m_timeoutDuration;
	}

	virtual void endConnect(eh2_ErrorContext* ctx, int isSuccess) {
		if (isSuccess) {
			// connection established.
			// if the server was marked as "dead", clears it.
			m_serverDead = 0;
		}
	}

	virtual void errorOnConnect(eh2_ErrorContext* ctx, idk_ut_Exception& ex) {
		int diff = m_timeoutAbsTime - idk_ut_SystemUtil::getCurrentTimeMillis();
		if (diff > 0) {
			// timeout has not been reached yet.  seems temporary failure.
			printf("TimeoutErrorHandler: Connection failed, retrying. (%d milliseconds left)\n", diff);
		} else {
			printf("TimeoutErrorHandler: Attempt to connect timed out.  The server seems dead.\n");

			// timeout has been reached.  the server seems dead.
			m_serverDead = 1;

			// throws an exception to terminate the attempt in case of
			// blocking app's thread.
			throw ConnectionTimedoutException("Attempt to connect timed out");
		}
	}
};

IDK_UT_SHAREDPTR_DECL(TimeoutErrorHandler);

//
// main
//
class StatefulErrorHandlerTest : eh2_Consts
{
public:
	void run() {
		eh2_EventHeapFactory* ehf = eh2_EventHeapFactory::cs_getInstance();

		// create an instance of error handler
		// the handler is stateful, so you have to create
		// one instance per connection.
		TimeoutErrorHandlerPtr errorHandlerPtr =
			new TimeoutErrorHandler(15000); // 15 secs for timeout

		try {
			// create a connection passing the error handler
			// instead of creating an event heap client directly.
			// an exception can be raised by the error handler.
			eh2_ConnectionPtr connPtr =
				ehf->createConnection("localhost", -1, errorHandlerPtr.cast());

			// create an event heap client object
			eh2_EventHeapPtr ehPtr = connPtr->createEventHeap(NULL, 0);

			// set timeout to poll the server's state.
			ehPtr->setTimeout(3000);
			eh2_EventPtr templatePtr = eh2_Event::cs_create("MyEvent");
			
			while (1) {
				try {
					printf("Waiting for MyEvent...\n");
					eh2_EventPtr resultPtr = ehPtr->waitForEvent(templatePtr);
					printf("MyEvent %d received.\n",
						resultPtr->getPostValueInt(FN_SEQUENCENUM)
						);
				}
				catch (idk_th_MonitorTimedoutException&) {
					// waitForEvent timed out.
					// Checks if the server is dead.
					if (errorHandlerPtr->isServerDead()) {
						// The server seems dead.  exits program.
						printf("The error handler indicated the server is dead.  Exiting...\n");
						break;
					}
				}
			}
		}
		catch (idk_ut_Exception& ex) {
			printf("Exception raised.  [%s]\n", ex.getMessage());
		}

		// the error handler must be healthy until all connections
		// and event heap clients which use the handler are gone.
	}
};
