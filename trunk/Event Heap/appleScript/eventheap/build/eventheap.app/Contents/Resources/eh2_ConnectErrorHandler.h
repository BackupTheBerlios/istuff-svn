/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_ConnectErrorHandler.h,v 1.3 2003/06/02 08:02:03 tomoto Exp $ */

#ifndef _EH2_CONNECTERRORHANDLER_H_
#define _EH2_CONNECTERRORHANDLER_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_ConnectErrorHandler class.
 @internal This header belongs to the eh2i_cl component.
 */

/**
 Defines the interface to receive callbacks about the status of
 network connections.
 
 <p>Applications can create its own handler by implementing
 this interface and associate it with a connection (eh2_Connection)
 object to be notified the change of the status of the connection.

 <p>The handler receives callbacks when an attempt to connect
 was started, finished, and errors occured during the attempt.
 Since the library automatically retries even if
 an error occured in connecting to the server,
 the handler may receive more than one error notifications between
 the start and the finish.

 <p>The handler may be called in two different cases,
 in different threads respectively.
 The first case is when a connection is being newly created,
 i.e. the application is calling the
 eh2_EventHeapFactory::createConnection() API.
 In this case, the handler is called in the same thread with
 the caller of the API.  Besides, the handler can raise an exception
 from the errorOnConnect() callback to discontinue the attempt to
 connect and the exception will be passed to the caller.
 Another case is when the connection initiated reconnection
 sequence because the network connection was dead after once established.
 In the latter case, the handler is called in the background thread
 which is usually engaging in sending/receiving Event Heap packets.
 In contrary to the former case, raising exception can not stop
 reconnection sequence; instead, the application can shutdown
 the connection object outside the handler to deactivate.
 The handler can always check in which thread it is being called now.

 <p>This interface is reference counted.  Do not forget to mix-in with
 idk_ut_RealObject class and place IDK_UT_REFCOUNTED_IMPL() macro
 provided by IDK.

 <pre>
 class MyHandler :
 public idk_ut_RealObject, // mix-in
 public eh2_ConnectErrorHandler // inherit this class
 {
   IDK_UT_REFCOUNTED_IMPL(); // put this macro

 public:
   // override methods here
 };
 </pre>
 */
class EH2_DECL eh2_ConnectErrorHandler {
	IDK_UT_REFCOUNTED_DECL();

public:
	virtual ~eh2_ConnectErrorHandler();

	/**
	 Called when an attempt to connect started.

	 The handler should initialize its state in this method.

	 @param ctx The information about the current context.
	 */
	virtual void startConnect(eh2_ErrorContext* ctx) = 0;

	/**
	 Called when an attempt to connect finished.

	 This method is called in both cases when 1) the connection was
	 established 2) the attempt to connect was terminated
	 by an exception from errorOnConnect() or thread interruption.

	 @param ctx The information about the current context.
	 @param isSuccess Non-zero if the connection was established.
	 Zero if the attempt was terminated.
	 */
	virtual void endConnect(eh2_ErrorContext* ctx, int isSuccess) = 0;

	/**
	 Called when an error occured during connecting to the server.
	 
	 When called in the foreground thread, this method can raise
	 an exception to discontinue the attempt to connect and
	 the exception will be eventually passed to the caller of the
	 eh2_EventHeapFactory::createConnection() API.
	 In the background thread, raised exceptions will be discarded.

	 @param ctx The information about the current context.
	 @param ex Exception occured in the attempt to connect which means:
	 <ul>
	  <li>eh2_EventHeapProtocolException - protocol version mismatch
	  <li>idk_io_IOException - network errors
	  <li>idk_ut_Exception - other errors
	 </ul>
	 */
	virtual void errorOnConnect(eh2_ErrorContext* ctx, idk_ut_Exception& ex) = 0;
};

#endif
