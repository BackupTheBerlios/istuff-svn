/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ByteArrayInStream.h,v 1.4 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_BYTEARRAYINSTREAM_H_
#define _IDK_IO_BYTEARRAYINSTREAM_H_

#include <idk_io_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_io_RealByteInStream.h>

/** @file
 Definition of idk_io_ByteArrayInStream class.
 */

/**
 Byte input stream to read data from an array.
 */
class IDK_DECL idk_io_ByteArrayInStream : public idk_io_RealByteInStream {
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

private:
	idk_io_ByteArrayInStream();

public:
	~idk_io_ByteArrayInStream();

	/**
	 Sets the source array and initializes the current location to
	 the top of the array.
	 The ownership of the array remains at the caller,
	 so it is caller's responsibillity to keep the array alive
	 until the usage of the stream is finished.

	 @param buf Byte array to be read.
	 @param size Size of the array.
	 */
	void setArrayRef(const idk_byte* buf, int size);

	/**
	 Reads the specified number of bytes.
	 @return The number of data items actually read.
	 0 means the stream reached its end.
	 */
	int readStream(idk_byte* buf, int size);

	/**
	 Returns non-zero if the current location is at the end of the array. 
	 */
	int isEOF();

	/**
	 Skips the specified number of bytes.
	 */
	int skipStream(int size);

	/**
	 Closes the stream.
	 There's no effect on this implementation.
	 */
	void closeStream();

	/**
	 Creates an object by setting the source array.
	 The ownership of the array remains at the caller,
	 so it is caller's responsibillity to keep the array alive
	 until the usage of the stream is finished.

	 @param buf Byte array to be read.
	 @param size Size of the array.
	 */
	static idk_io_ByteArrayInStreamPtr
	cs_createByRef(const idk_byte* buf, int size);
};

#endif
