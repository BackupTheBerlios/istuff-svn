/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_ByteArray.h,v 1.6 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_BYTEARRAY_H_
#define _IDK_UT_BYTEARRAY_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_ByteArray class.
 */

class idki_ut_ByteArray; // impl

/**
 Resizable array of byte.
 <p>This class has reference-semantics unlike STL's vector,
 hence provides a capability to handle byte array by pointers.
 When you transfer the ownership of a byte array data,
 passing this object is much more efficient than copying a vector.
 <p>Instances of this class can be created by cs_create() method,
 not by new operator.
 */
class IDK_DECL idk_ut_ByteArray :
public idk_ut_TProxyObject<idki_ut_ByteArray>
{
private:
	friend class idki_ut_ByteArray;
	idk_ut_ByteArray(idki_ut_ByteArray* impl);

public:
	~idk_ut_ByteArray();

	/**
	 Sets the length of the array.
	 */
	void setLength(int length);

	/**
	 Returns the mutable pointer to the array.
	 */
	idk_byte* getData();
	
	/**
	 Resizes the array and copies the existing data.
	 */
	void copyData(const idk_byte* buf, int length);

	/**
	 Returns the length of the array.
	 */
	int getLength() const;

	/**
	 Returns the read-only pointer to the array.
	 */
	const idk_byte* getData() const;

	/**
	 Clones the object.
	 */
	idk_ut_ByteArrayPtr clone() const;

public:
	/**
	 Creates a new object.
	 */
	static idk_ut_ByteArrayPtr cs_create();
};

#endif
