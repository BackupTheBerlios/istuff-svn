/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Connection.h,v 1.6 2003/06/02 08:02:03 tomoto Exp $ */

#ifndef _EH2_CONNECTION_H_
#define _EH2_CONNECTION_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <idk_ne_SocketAddress.h>

/** @file
 Definition of eh2_Connection class.
 @internal This header belongs to the eh2i_cl component.
 */

class eh2i_cl_Connection; // impl

/**
 Represents a connection to an Event Heap server.

 <p>This class manages the network connection to an Event Heap server
 and creates client (eh2_EventHeap) objects associated with the server.
 This class allows applications to monitor the status of the network
 connection and explicitly shut down the connection to release all
 related resources and blocked clients gracefully.

 <p>To monitor the status of the connection, the application should
 pass an error handler (eh2_ConnectErrorHandler) object to
 eh2_EventHeapFactory::createConnection() method.
 The connection will call it back each time an error occured.

 <p>The connection object will be maintained while any of the child
 eh2_EventHeap objects spawned from the connection are alive
 although the application released the smartpointer to the connection.
 */
class EH2_DECL eh2_Connection :
public idk_ut_TProxyObject<eh2i_cl_Connection>
{
private:
	friend class eh2i_cl_Connection;
	eh2_Connection(eh2i_cl_Connection* impl);

public:
	~eh2_Connection();

	/**
	 Returns the factory which created this connection.
	 */
	const eh2_EventHeapFactory* getFactory() const;

	/**
	 Returns the factory which created this connection.
	 */
	eh2_EventHeapFactory* getFactory();

	/**
	 Returns the address and the port number of the Event Heap server.
	 */
	const idk_ne_SocketAddress* getAddress() const;

	/**
	 Returns the error handler which is set to this connection.
	 */
	eh2_ConnectErrorHandler* getConnectErrorHandler();

	/**
	 Create an Event Heap client object upon this connection.

	 @param source Source name of the newly created client.
	 If NULL was specified, the source name will be automatically generated
	 from the application name with a random number.
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
	
	 @see eh2_EventHeap
	 */
	eh2_EventHeapPtr createEventHeap(
		const char* source = NULL,
		int isMultiThreadSafe = 1
		);

	/**
	 Returns the number of requests which are waiting for being sent.

	 The application should be aware of this value when using
	 eh2_EventHeap::putEventAsync().
	 */
	int getBacklogCount() const;

	/**
	 Shuts down the connection.

	 <p>This function causes the network connection to be closed
	 and all blocked Event Heap client calls to immediately return
	 with raising idk_th_InterruptedException.

	 <p>Do not shutdown the connections managed by the factory.
	 (i.e. connections retrieved from eh2_EventHeap objects
	  which are directly created from eh2_EventHeapFactory.)
	 If you need to do so, use eh2_EventHeapFactory::releaseConnections() instead.
	 */
	void shutdown();
};

#endif
