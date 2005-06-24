/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ByteLoggingInStream.h,v 1.4 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_BYTELOGGINGINSTREAM_H_
#define _IDK_IO_BYTELOGGINGINSTREAM_H_

#include <idk_io_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_io_RealByteInStream.h>

/** @file
 Definition of idk_io_ByteLoggingInStream class.
 */

/**
 Input stream which provides a capability to send a copy of read data
 to another output stream.
 This is an experimental API, but would be useful to debug
 the byte sequence which the application actually received.
 */
class IDK_DECL idk_io_ByteLoggingInStream : public idk_io_RealByteInStream {
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

public:
	virtual ~idk_io_ByteLoggingInStream();

	/**
	 Creates an object.
	 @param isPtr Input stream to be read.
	 @param logOSPtr Output stream to send a copy of read data.
	 */
	idk_io_ByteLoggingInStream(
		const idk_io_IByteInStreamPtr& isPtr,
		const idk_io_IByteOutStreamPtr& logOSPtr
		);

	virtual int skipStream(int size);
	virtual int isEOF();
	virtual int readStream(idk_byte* buf, int size);
	virtual void closeStream();
};

IDK_UT_SHAREDPTR_DECL(idk_io_ByteLoggingInStream);

#endif
