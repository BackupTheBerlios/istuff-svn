/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ByteArrayOutStream.h,v 1.4 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_BYTEARRAYOUTSTREAM_H_
#define _IDK_IO_BYTEARRAYOUTSTREAM_H_

#include <idk_io_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_io_RealByteOutStream.h>

/** @file
 Definition of idk_io_ByteArrayOutStream class.
 */

/**
 Output stream to write data into dynamically allocated array.
 */
class IDK_DECL idk_io_ByteArrayOutStream : public idk_io_RealByteOutStream {
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

private:
	idk_io_ByteArrayOutStream(int initialCapacity);

public:
	~idk_io_ByteArrayOutStream();

	/**
	 Returns the address of the top of the array.
	 */
	const idk_byte* getArray() const;

	/**
	 Returns the current size of the array.
	 */
	int getArraySize() const;

	/**
	 Clears the array.
	 */
	void clear();
	
	/**
	 Writes the specified number of bytes to the array.
	 @returns The number of data items actually written.
	 It is always equal to the specified size.
	 */
	virtual int writeStream(const idk_byte* buf, int size);

	/**
	 Closes the stream.
	 There's no actual effect on this implementation.
	 */
	virtual void closeStream();
	
	/**
	 Flushes the stream.
	 There's no actual effect on this implementation.
	 */
	virtual void flushStream();

	/**
	 Creates an object.
	 @param initialCapacity Size of the array initially allocated.
	 You can tune this value to avoid unnecessary reallocations.
	 */
	static idk_io_ByteArrayOutStreamPtr
	cs_create(int initialCapacity = 0);
};

#endif
