/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_InetAddress.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_INETADDRESS_H_
#define _IDK_NE_INETADDRESS_H_

#include <idk_ne_Types.h>
#include <idk_ut_TProxyObject.h>

/** @file
 Definition of idk_ne_InetAddress class.
 */

class idki_ne_InetAddress; // impl

/**
 This class represents an Internet address.
 Only supports IPv4.
 */
class IDK_DECL idk_ne_InetAddress :
public idk_ut_TProxyObject<idki_ne_InetAddress>
{
private:
	friend class idki_ne_InetAddress;
	idk_ne_InetAddress(idki_ne_InetAddress* impl);

public:
	~idk_ne_InetAddress();

	/**
	 Creates an InetAddress object by host name.
	 @param hostName Host name
	 @returns New InetAddress object representing the specified host.
	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_ne_UnknownHostException Cannot resolve the host name.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 */
	static idk_ne_InetAddressPtr cs_createByName(const char* hostName);

	/**
	 Creates an InetAddress object representing the localhost.
	 @returns New InetAddress object representing the localhost.
	 @throws idk_ne_NetSystemException Network subsystem failure.
	 @throws idk_ut_UnknownHostException Cannot resolve the host name.
	 @throws idk_io_InterruptedIOException The operation was interrupted by a signal.
	 */
	static idk_ne_InetAddressPtr cs_createLocalHost();

	/**
	 Clones the object.
	 */
	idk_ne_InetAddressPtr clone() const;

	/**
	 Gets in_addr structure.  This would not be useful in normal usage.
	 @returns in_addr structure in the object.
	 */
	const in_addr& getAddress() const;

	/**
	 Gets the host address in a string format like "192.168.0.1".
	 @return a string representing the host address.
	 */
	const char* getHostAddress() const;

	/**
	 Gets the host name.
	 @return Host name.  Not canonicalized.
	 */
	const char* getHostName() const;

	/**
	 Returns the hash value of the object.
	 */
	int hashCode() const;

	/**
	 Returns non-zero if the object is identical with the given object.
	 Two InetAddress objects are identical when they holds the same IP address
	 even if the host names are different.
	 */
	int equals(const idk_ne_InetAddress* other) const;
};

#endif
