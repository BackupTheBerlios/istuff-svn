/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ByteBufferInStream.h,v 1.4 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_BYTEBUFFERINSTREAM_H_
#define _IDK_IO_BYTEBUFFERINSTREAM_H_

#include <idk_io_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_io_RealByteInStream.h>

/** @file
 Definition of idk_io_ByteBufferInStream class.
 */

/**
 Adds buffering capability to any other byte input stream.
 This stream reads data from another stream through a buffer,
 hence reduces the number of actual read requests.
 This buffering feature could improve efficiency of I/O
 because the cost per I/O operation call is generally high.
 The size of the buffer is configurable.
 */
class IDK_DECL idk_io_ByteBufferInStream : public idk_io_RealByteInStream {
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

private:
	idk_io_ByteBufferInStream(int bufSize);

public:
	virtual ~idk_io_ByteBufferInStream();

	/**
	 Sets an input stream to be buffered.
	 The buffer-stream will take over the ownership of the given stream,
	 so the caller do not have to maintain that stream anymore.

     @param streamPtr Smartpointer to the stream to be buffered.
	 */
	void setStreamPtr(const idk_io_IByteInStreamPtr& streamPtr);

	/**
	 Sets an input stream to be buffered.
	 The ownership of the given stream will remain at the caller,
	 so it is caller's responsibility to keep that stream alive
	 until the usage of the buffer-stream is completely finished.

	 @param stream Stream to be buffered.
     */
	void setStreamRef(idk_io_IByteInStream* stream);

	/**
	 Skips the specified number of bytes.
	 The actual behavior depends on the stream to be buffered.
	 */
	virtual int skipStream(int size);

	/**
	 Returns non-zero if the stream has already reached its end.
	 The actual behavior depends on the stream to be buffered.
	 */
	virtual int isEOF();

	/**
	 Reads the specified number of data items from the stream into array.
	 The actual behavior depends on the stream to be buffered.
	 */
	virtual int readStream(idk_byte* buf, int size);

	/**
	 Closes the stream.
	 The actual behavior depends on the stream to be buffered.
	 */
	virtual void closeStream();

	/**
	 Creates an object by setting an input stream to be buffered.
	 The buffer-stream will take over the ownership of the given stream,
	 so the caller do not have to maintain that stream anymore.

     @param streamPtr Smartpointer to the stream to be buffered.
	 @param bufSize Size of the buffer.
	 */
	static idk_io_ByteBufferInStreamPtr
	cs_createByPtr(const idk_io_IByteInStreamPtr& streamPtr, int bufSize);

	/**
	 Creates an object by setting an input stream to be buffered.
	 The ownership of the given stream will remain at the caller,
	 so it is caller's responsibility to keep that stream alive
	 until the usage of the buffer-stream is completely finished.

     @param stream Stream to be buffered.
	 @param bufSize Size of the buffer.
	 */
	static idk_io_ByteBufferInStreamPtr
	cs_createByRef(idk_io_IByteInStream* stream, int bufSize);
};

IDK_UT_SHAREDPTR_DECL(idk_io_ByteBufferInStream);

#endif
