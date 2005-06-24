/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventHeapFactory.h,v 1.8 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_EVENTHEAPFACTORY_H_
#define _EH2_EVENTHEAPFACTORY_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_EventHeapFactory class.
 @internal This header belongs to the eh2i_cl component.
 */

class eh2i_cl_EventHeapFactory; // impl

/**
 The factory of Event Heap client objects.

 <p>This class provides entry points to create eh2_EventHeap object or
 eh2_Connection object.

 <p>Applications can create eh2_EventHeap objects directly from the factory
 by createEventHeap() method.
 In this case, the network connections are established implicitly and 
 managed by the factory.

 <p>Or, applications can create eh2_Connection objects by createConnection()
 method and spawn eh2_EventHeap objects from them.
 This way allows applications to manage the network connections explicitly
 and monitor the network errors.

 <p>In the current version of ceheap2, the factory is a singleton --
 only one instance exists in a process.
 The factory is initialized by eh2_init() and released gracefully by
 eh2_finalize().
 <i>We may allow applications to manage multiple factories in the future
 if it is proven to be useful for applications to have
 a number of sets of resources.</i>
 */
class EH2_DECL eh2_EventHeapFactory :
public idk_ut_TProxyObject<eh2i_cl_EventHeapFactory>
{
private:
	friend class eh2i_cl_EventHeapFactory;
	eh2_EventHeapFactory(eh2i_cl_EventHeapFactory* impl);

public:
	~eh2_EventHeapFactory();

	/**
	 Returns the application name set to this factory.
	 Application name is set either as passed to eh2_init(),
	 or to the executable file name when the passed value was NULL.
	 */
	const char* getAppName() const;

	/**
	 Returns the device name set to this factory.
	 Device name is set either as passed to eh2_init(),
	 or to the host name when the passed value was NULL.
	 */
	const char* getDeviceName() const;

	/**
	 Returns the version number of Event Heap.
	 @return Always 2 in this version.
	 */
	int getVersion() const;

	/**
	 Creates a new connection to the Event Heap server.

	 <p>This method creates a new netrowk connection to the specified
	 Event Heap server and returns an eh2_Connection object.

	 <p>The application can set an error handler which receives
	 a callback each time an error occured on this connection.
	 This method automatically retries the attempt to connect
	 until the connection is successfully established
	 or the error handler raises an exception to indicate
	 to discontinue the attempt.
	 
	 @param machine Host name of the Event Heap server to connect.
	 @param port Port number of the Event Heap server to connect.
	 If -1 was specified, the default port number 4535 will be used.
	 @param connErrorHandlerPtr An eh2_ConnectErrorHandler object
	 which handles errors on this connection.

     @return A newly created connection object.
	 As similar to other methods which returns smartpointer type,
	 the ownership of the returned object is transferred to the caller.

     @throws eh2_EventHeapException Supported protocol version does not
	 match with the server.
	 @throws idk_ne_UnknownHostException The host name cannot be resolved.
	 @throws idk_ut_Exception The error handler
	 (see eh2_ConnectErrorHandler) raised an exception.

	 @see createEventHeap()
	 */
	eh2_ConnectionPtr createConnection(
		const char* machine,
		int port = -1,
		const eh2_ConnectErrorHandlerPtr& connErrorHandlerPtr = NULL
		);

	/**
	 Creates an instance of Event Heap client object.
	 
	 <p>This method creates a new connection
	 if the specified Event Heap server has not seen by the factory,
	 and creates an eh2_EventHeap object from the connection.
	 The connection is managed by the factory.

	 <p>This method blocks until the attempt to connect succeed.
	 If the application wants to handle errors, 
	 use createConnection() method instead, with eh2_ConnectErrorHandler.

	 @param source Source name of the newly created client.
	 If NULL was specified, the source name will be automatically generated
	 from the application name with a random number.
	 @param machine Host name of the Event Heap server to connect.
	 @param port Port number of the Event Heap server to connect.
	 If -1 was specified, the default port number 4535 will be used.
	 @param isMultiThreadSafe
	 When zero was specified, a multithread-unsafe version of 
	 client object will be created.  If your application do not share
	 a client object under multiple threads, specify zero to avoid
	 overhead of mutex.
	 When non-zero was specified, a multithread-safe version of
	 client object will be created.  If your application has
	 multiple threads which could send requests to the server
	 on behalf of the newly created client,
	 specify non-zero to guarantee safe operations.

     @return A newly created Event Heap client object.
	 As similar to other methods which returns smartpointer type,
	 the ownership of the returned object is transferred to the caller.

     @throws eh2_EventHeapException Supported protocol version does not
	 match with the server.
	 @throws idk_ne_UnknownHostException The host name cannot be resolved.

	 @see createConnection()
	*/
	eh2_EventHeapPtr createEventHeap(
		const char* source, // may be NULL
		const char* machine,
		int port = -1,
		int isMultiThreadSafe = 0
		);

	/**
	 Releases all connections managed by this factory.
	 This method has no effect on the connections explicitly created
	 by createConnection() method.
	 */
	void releaseConnections();

	/**
	 Returns the pointer to the factory.
	 */
	static eh2_EventHeapFactory*
	cs_getInstance();
};

#endif
