#include <idk.h>
#include <idk_th.h>
#include <idk_ne.h>
#include <idk_ut.h>

//
// this is an example of "stateless" error handler.
// error handler of this type is shared by all connections managed
// by the same eh2_EventHeapFactory and called by any of them
// at the same time.
// this type is suitable for tasks which require no variable state.
// this sample shows an implementation of stateless error handler
// which simply displays all passed information.
//
class EchoErrorHandler :
public idk_th_Lockable,
public eh2_ConnectErrorHandler
{
	IDK_UT_REFCOUNTED_IMPL(); // this macro is necessary to mix-in
							  // eh2_ConnectErrorHandler interface

private:
	void printAddress(eh2_ErrorContext* ctx) {
		// you can get the server's address from the context.
		printf("EchoErrorHandler connecting to %s:%d: ",
			ctx->getAddress()->getInetAddress()->getHostName(),
			ctx->getAddress()->getPort()
			);
	}

public:
	virtual void startConnect(eh2_ErrorContext* ctx) {
		// probably you need to lock this block.
		// because stateless error handler can be called from multiple
		// threads at the same time when two or more connections are active.
		idk_th_Locker locker(this);

		// prints the information
		printAddress(ctx);
		printf("Starting attempt to connect.\n");
	}

	virtual void endConnect(eh2_ErrorContext* ctx, int isSuccess) {
		// lock this block likewise.
		idk_th_Locker locker(this);

		//  prints the information.
		printAddress(ctx);

		// isSuccess indicates whether the attempt for connection
		// was successful or not.
		// if failed, it means the receiver/sender threads were shutting
		// down since the factory was being released.
		if (isSuccess) {
			printf("Connection established.\n");
		} else {
			printf("Interrupted.\n");
		}
	}

	virtual void errorOnConnect(eh2_ErrorContext* ctx, idk_ut_Exception& ex) {
		{
			// lock this block likewise.
			idk_th_Locker locker(this);

			// prints the information.
			printAddress(ctx);
			printf("Error occured.  [%s]\n", ex.getMessage());
		}

		// this is an example of implementing retry policy.
		// to retry, simply return.  to terminate the attempt,
		// throw an exception.
		// note that you can't terminate the attempt during
		// automatic reconnection executed in background,
		// which is indicated by isBackgroundThread() != 0.
		// in this case, the raised exception is simply ignored.
		//
		// this policy decides to terminate in case of protocol
		// version mismatch, or to retry otherwise.
		// if protocol version mismatch occured during automatic
		// reconnection, it blocks the thread for 30 seconds,
		// instead of throwing exception, so that the application
		// gets timeout while avoiding useless connection requests.
		//
		try {
			// tests the type of the exception.
			// (it would look more elegant if you can use a sort
			//  of "instanceof" operator.
			//  perhaps you can choose to use it, but you would have
			//  to enable funky RTTI mechanism by compiler option.)
			ex.raise();
		}
		catch (eh2_EventHeapProtocolException&) {
			// protocol version mismatch.  retry is useless.
			if (ctx->isBackgroundThread()) {
				// now in background thread.
				// sleeps 30 seconds hoping the app's timeout.
				// note that the lock is already released.
				idk_ut_SystemUtil::sleep(30000);
			} else {
				// rethrows the exception to terminate the attempt
				throw;
			}
		}
		catch (idk_ut_Exception&) {
			// retry
		}
	}
};

//
// main
//
class StatelessErrorHandlerTest : eh2_Consts
{
public:
	void run() {
		eh2_EventHeapFactory* ehf = eh2_EventHeapFactory::cs_getInstance();

		// create an instance of error handler
		// the handler is stateless, so this instance can be shared
		// among connections.
		eh2_ConnectErrorHandlerPtr errorHandlerPtr = new EchoErrorHandler();

		try {
			// create a connection passing the error handler
			// instead of creating an event heap client directly.
			eh2_ConnectionPtr connPtr =
				ehf->createConnection("localhost", -1, errorHandlerPtr);

			// create an event heap client object
			eh2_EventHeapPtr ehPtr = connPtr->createEventHeap(NULL, 0);

			// if the server downed too long (15 secs), exits program.
			ehPtr->setTimeout(15000);

			// posts events every 1 second.
			while (1) {
				eh2_EventPtr eventPtr = eh2_Event::cs_create("MyEvent");
				ehPtr->putEvent(eventPtr);
				printf("MyEvent %d posted.\n",
					eventPtr->getPostValueInt(FN_SEQUENCENUM)
					);
				idk_ut_SystemUtil::sleep(1000);
			}
		}
		catch (idk_ut_Exception& ex) {
			printf("Exception raised.  [%s]\n", ex.getMessage());
		}

		// the error handler must be healthy until all connections
		// and event heap clients which use the handler are gone.
	}
};
