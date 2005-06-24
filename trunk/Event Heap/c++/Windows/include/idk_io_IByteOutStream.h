/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_IByteOutStream.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_IBYTEOUTSTREAM_H_
#define _IDK_IO_IBYTEOUTSTREAM_H_

#include <idk_io_Types.h>
#include <idk_io_ITOutStream.h>

/** @file
 Definition of idk_io_IByteOutStream class.
 */

/**
 Interface of byte output stream.
 */
class IDK_DECL idk_io_IByteOutStream : public idk_io_ITOutStream<idk_byte> {
public:
	virtual ~idk_io_IByteOutStream();

	virtual int writeStream(const idk_byte* buf, int size) = 0;
	virtual void closeStream() = 0;
	virtual void flushStream() = 0;
	virtual void writeStream(const idk_byte& value);
	virtual int writeFull(const idk_byte* buf, int size);

	/**
	 Cheaty shortcut for writing char data as byte.
	 @see writeStream(const idk_byte*, int)
	 */
	int writeStream(const char* buf, int size) {
		return writeStream((const idk_byte*)buf, size);
	}

	/**
	 Cheaty shortcut for writing char data as byte.
	 @see writeFull(const idk_byte*, int)
	 */
	int writeFull(const char* buf, int size) {
		return writeFull((const idk_byte*)buf, size);
	}
};

IDK_UT_SHAREDPTR_DECL(idk_io_IByteOutStream);

#endif
