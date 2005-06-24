/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_SocketAddress.h,v 1.6 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_SOCKETADDRESS_H_
#define _IDK_NE_SOCKETADDRESS_H_

#include <idk_ne_Types.h>

/** @file
 Definition of idk_ne_SocketAddress class.
 */

class idki_ne_SocketAddress; // impl

/**
 This class represents a pair of Internet address and port number.
 This class is only a holder and has no intelligence.
 */
class IDK_DECL idk_ne_SocketAddress :
public idk_ut_TProxyObject<idki_ne_SocketAddress>
{
private:
	friend class idki_ne_SocketAddress;
	idk_ne_SocketAddress(idki_ne_SocketAddress* impl);

public:
	~idk_ne_SocketAddress();

	/**
	 Returns the Internet address part.
	 */
	const idk_ne_InetAddress* getInetAddress() const;

	/**
	 Returns the port number part.
	 */
	int getPort() const;

	/**
	 Returns the hash value of this object.
	 */
	int hashCode() const;

	/**
	 Returns non-zero if the object is identical with the given object.
	 */
	int equals(const idk_ne_SocketAddress* other) const;

	/**
	 Clones the oblect.
	 */
	idk_ne_SocketAddressPtr clone() const;

	/**
	 Creates an object by specifying an Internet address and a port number.
	 @param addrPtr Smartpointer to the Internet address.
	 The newly created object takes over the ownership of this object.
	 @param port Port number.
	 */
	static idk_ne_SocketAddressPtr cs_create(
		const idk_ne_InetAddressPtr& addrPtr, int port
		);
};

IDK_UT_SHAREDPTR_DECL(idk_ne_SocketAddress);

#endif
