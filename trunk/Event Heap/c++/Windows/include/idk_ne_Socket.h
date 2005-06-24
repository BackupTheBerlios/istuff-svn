/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_Socket.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_SOCKET_H_
#define _IDK_NE_SOCKET_H_

#include <idk_ne_Types.h>

/**
 Definition of idk_ne_Socket class.
 */

class idki_ne_Socket; // impl

/**
 Represents a network socket (client socket).
 */
class IDK_DECL idk_ne_Socket :
public idk_ut_TProxyObject<idki_ne_Socket>
{
private:
	friend class idki_ne_Socket;
	idk_ne_Socket(idki_ne_Socket* impl);

public:
	~idk_ne_Socket();

	/**
	 Gets the input stream for the socket.
	 */
	idk_io_IByteInStream* getInStream();

	/**
	 Gets the output stream for the socket.
	 */
	idk_io_IByteOutStream* getOutStream();

	/**
	 Closes the socket.
	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 @throws idk_ut_BadParameterException The socket passed by the caller is not a socket.
	 <i>Should not occur in the current implementation.</i>
	 */
	void closeSocket();

	/**
	 Sets TCP_NODELAY socket option.
	 @throws idk_io_EOFException already closed
	 */
	void setTcpNoDelay(int flag);

public:
	/**
	 Creates a TCP socket and opens the connection.

     @param addr Internet address to connect.
	 @param port Port number to connect.

	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_ut_OutOfResourceException No more socket handle or buffer available.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 @throws idk_ut_BadParameterException Cannot create a socket because of
	 invalid parameter values.
	 @throws idk_ut_PermissionDeniedException Cannot create a socket because
	 the requested operation is not allowed.
	 @throws idk_ne_NoConnectionException An error occured during connecting.
	 */
	static idk_ne_SocketPtr
	cs_create(const idk_ne_InetAddress* addr, int port);

	/**
	 Creates a socket and opens the connection.
	 See idk_ne_Socket(const idk_ne_InetAddress* addr, int port) for details.
	 @see idk_ne_Socket(const idk_ne_InetAddress* addr, int port)
	 */
	static idk_ne_SocketPtr
	cs_create(const idk_ne_SocketAddress* addr);

};

IDK_UT_SHAREDPTR_DECL(idk_ne_Socket);

#endif
