/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_Types.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_TYPES_H_
#define _IDK_NE_TYPES_H_

/** @file
 Declaration of typenames of the idk_ne package.
 */

// directly dependent packages
#include <idk_io_Types.h>

// basic types related to socket
#ifdef WINDOWS
#include <winsock.h>
#elif defined(unix)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#error unsupported platform
#endif

// declaration of typenames
class idk_ne_InetAddress;
IDK_UT_SHAREDPTR_DECL(idk_ne_InetAddress);

class idk_ne_SocketAddress;
IDK_UT_SHAREDPTR_DECL(idk_ne_SocketAddress);

class idk_ne_Socket;
IDK_UT_SHAREDPTR_DECL(idk_ne_Socket);

class idk_ne_ServerSocket;
IDK_UT_SHAREDPTR_DECL(idk_ne_ServerSocket);

class idk_ne_SocketInStream;
IDK_UT_SHAREDPTR_DECL(idk_ne_SocketInStream);

class idk_ne_SocketOutStream;
IDK_UT_SHAREDPTR_DECL(idk_ne_SocketOutStream);

#endif
