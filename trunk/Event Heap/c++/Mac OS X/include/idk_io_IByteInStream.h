/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_IByteInStream.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_IBYTEINSTREAM_H_
#define _IDK_IO_IBYTEINSTREAM_H_

#include <idk_io_Types.h>
#include <idk_io_ITInStream.h>

/** @file
 Definition of idk_io_IByteInStream class.
 */

/**
 Interface of byte input stream.
 */
class IDK_DECL idk_io_IByteInStream : public idk_io_ITInStream<idk_byte> {
public:
	virtual ~idk_io_IByteInStream();

	virtual int skipStream(int size) = 0;
	virtual int isEOF() = 0;
	virtual int readStream(idk_byte* buf, int size) = 0;
	virtual void closeStream() = 0;
	virtual idk_byte readStream();
	virtual int readFull(idk_byte* buf, int size);

	/**
	 Cheaty shortcut for reading byte data as char.
	 */
	int readStream(char* buf, int size) {
		return readStream((idk_byte*)buf, size);
	}

	/**
	 Cheaty shortcut for reading byte data as char.
	 */
	int readFull(char* buf, int size) {
		return readFull((idk_byte*)buf, size);
	}
};

IDK_UT_SHAREDPTR_DECL(idk_io_IByteInStream);

#endif
