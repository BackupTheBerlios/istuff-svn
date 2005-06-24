/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ByteBufferOutStream.h,v 1.4 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_BYTEBUFFEROUTSTREAM_H_
#define _IDK_IO_BYTEBUFFEROUTSTREAM_H_

#include <idk_io_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_io_RealByteOutStream.h>

/** @file
 Definition of idk_io_ByteBufferOutStream class.
 */

/**
 Adds buffering capability to any other byte output stream.
 This stream writes data to another stream through a buffer,
 hence reduces the number of actual write requests.
 This buffering feature could improve efficiency of I/O
 because the cost per I/O operation call is generally high.
 The size of the buffer is configurable.
 */
class IDK_DECL idk_io_ByteBufferOutStream : public idk_io_RealByteOutStream
{
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

private:
	idk_io_ByteBufferOutStream(int bufSize);

public:
	virtual ~idk_io_ByteBufferOutStream();

	/**
	 Sets an output stream to be buffered.
	 The buffer-stream will take over the ownership of the given stream,
	 so the caller do not have to maintain that stream anymore.

     @param streamPtr Smartpointer to the stream to be buffered.
	 */
	void setStreamPtr(const idk_io_IByteOutStreamPtr& streamPtr);

	/**
	 Sets an output stream to be buffered.
	 The ownership of the given stream will remain at the caller,
	 so it is caller's responsibility to keep that stream alive
	 until the usage of the buffer-stream is completely finished.

	 @param stream Stream to be buffered.
     */
	void setStreamRef(idk_io_IByteOutStream* stream);

	virtual int writeStream(const idk_byte* buf, int size);

	/**
	 Closes the stream.
	 This method flushes the buffer,
	 then calls the closeStream() of the buffered stream.
	 */
	virtual void closeStream();

	/**
	 Flushes the stream.
	 This method flushes the buffer,
	 then calls the flushStream() of the buffered stream.
	 */
	virtual void flushStream();

	/**
	 Creates an object by setting an output stream to be buffered.
	 The buffer-stream will take over the ownership of the given stream,
	 so the caller do not have to maintain that stream anymore.

     @param streamPtr Smartpointer to the stream to be buffered.
	 @param bufSize Size of the buffer.
	 */
	static idk_io_ByteBufferOutStreamPtr
	cs_createByPtr(const idk_io_IByteOutStreamPtr& streamPtr, int bufSize);

	/**
	 Creates an object by setting an output stream to be buffered.
	 The ownership of the given stream will remain at the caller,
	 so it is caller's responsibility to keep that stream alive
	 until the usage of the buffer-stream is completely finished.

     @param stream Stream to be buffered.
	 @param bufSize Size of the buffer.
	 */
	static idk_io_ByteBufferOutStreamPtr
	cs_createByRef(idk_io_IByteOutStream* stream, int bufSize);
};

IDK_UT_SHAREDPTR_DECL(idk_io_ByteBufferOutStream);

#endif
