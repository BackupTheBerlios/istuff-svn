/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_ServerSocket.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_SERVERSOCKET_H_
#define _IDK_NE_SERVERSOCKET_H_

#include <idk_ne_Types.h>

/**
 Definition of idk_ne_ServerSocket class.
 */

class idki_ne_ServerSocket; // impl

/**
 Represents a server-side network socket.
 @see idk_ne_Socket
 */
class IDK_DECL idk_ne_ServerSocket :
public idk_ut_TProxyObject<idki_ne_ServerSocket>
{
private:
	friend class idki_ne_ServerSocket;
	idk_ne_ServerSocket(idki_ne_ServerSocket* impl);

public:
	~idk_ne_ServerSocket();

	/**
	 Waits for and accepts a request to connect.
	 @return idk_ne_Socket object representing the newly established connection.
	 The caller must take over the ownership of the returned object
	 by holding it with a smartpointer.
	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_ut_OutOfResourceException No more buffers are available.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 @throws idk_ut_BadParameterException The socket passed by the caller is not a socket.
	 <i>Should not occur in the current implementation.</i>
	 */
	idk_ne_SocketPtr accept();

	/**
	 Closes the socket.
	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 @throws idk_ut_BadParameterException The socket passed by the caller is not a socket.
	 <i>Should not occur in the current implementation.</i>
	 */
	void closeSocket();

public:
	/**
	 Creates a server-side socket and makes it ready to accept.
	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_ut_OutOfResourceException No more socket handles or buffers are available.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 @throws idk_ut_BadParameterException Cannot open a socket because of
	 invalid parameter values.
	 @throws idk_ut_PermissionDeniedException Cannot create a socket because
	 the requested operation is not allowed.
	 */
	static idk_ne_ServerSocketPtr cs_create(int port, int backlog);
};

IDK_UT_SHAREDPTR_DECL(idk_ne_ServerSocket);

#endif
