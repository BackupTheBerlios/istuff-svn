/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_FileOutStream.h,v 1.6 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_FILEOUTSTREAM_H_
#define _IDK_IO_FILEOUTSTREAM_H_

#include <idk_io_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_io_RealByteOutStream.h>

/** @file
 Definition of idk_io_FileOutStream class.
 */

/**
 Output stream for a file.
 You can write to a file using this stream by specifying a file name,
 or attaching a file descriptor already opened.
 This stream calls the write system call directly,
 so you are advised to apply appropreate buffering techniques.
 */
class IDK_DECL idk_io_FileOutStream : public idk_io_RealByteOutStream {
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

private:
	idk_io_FileOutStream(const char* fileName);
	idk_io_FileOutStream(int fd, int needToClose);

public:
	~idk_io_FileOutStream();

	/**
	 Writes the specified number of data items to the stream.
	 @return The number of data items actually written.
	 It can be less than the specified size because the space
	 is not available temporarily.
	 @throws idk_io_IOException
	 @throws idk_ut_BadParameterException
	 The file descriptor is bad or already closed by someone else.
	 @throws idk_ut_OutOfResourceException
	 No disc space left.
	 */
	virtual int writeStream(const idk_byte* buf, int size);

	/**
	 Closes the stream.
	 @throws idk_io_IOException
	 @throws idk_ut_BadParameterException
	 The file descriptor is bad or already closed by someone else.
	 */
	virtual void closeStream();

	/**
	 Flushes the stream.
	 If the stream keeps inside any data waiting for being actually written,
	 it should be processed immediately.
	 @throws idk_io_IOException
	 @throws idk_ut_BadParameterException
	 The file descriptor is bad or already closed by someone else.
	 */
	virtual void flushStream();
	
	/**
	 Creates an object by specifying a file name.
	 @param fileName File name to open.
	 @throws idk_io_FileNotFoundException
	 @throws idk_ut_PermissionDeniedException
	 @throws idk_ut_OutOfResourceException Ran out of file descriptor.
	 */
	static idk_io_FileOutStreamPtr cs_createByFileName(const char* fileName);

	/**
	 Creates an object by specifying a file descriptor.
	 @param fd File descriptor which is already opened.
	 @param needToClose Non-zero to close the file descriptor on closeStream(),
	 or zero to leave it opened.
	 */
	static idk_io_FileOutStreamPtr cs_createByFileDesc(int fd, int needToClose);

	/**
	 Creates an object wrapped by idk_io_ByteBufferOutStream
	 by specifying a file name.
	 Note that the return value is not idk_io_FileOutStreamPtr
	 but idk_io_IByteInStreamPtr.
	 @param fileName File name to open.
	 @param bufSize Size of the buffer.
	 @throws idk_io_FileNotFoundException
	 @throws idk_ut_PermissionDeniedException
	 @throws idk_ut_OutOfResourceException Ran out of file descriptor.
	 */
	static idk_io_IByteOutStreamPtr
	cs_createBufferedByFileName(const char* fileName, int bufSize = 4096);

	/**
	 Creates an object wrapped by idk_io_ByteBufferOutStream
	 by specifying a file descriptor.
	 Note that the return value is not idk_io_FileOutStreamPtr
	 but idk_io_IByteInStreamPtr.
	 @param fd File descriptor which is already opened.
	 @param needToClose Non-zero to close the file descriptor on closeStream(),
	 or zero to leave it opened.
	 @param bufSize Size of the buffer.
	 */
	static idk_io_IByteOutStreamPtr
	cs_createBufferedByFileDesc(int fd, int needToClose, int bufSize = 4096);
};

IDK_UT_SHAREDPTR_DECL(idk_io_FileOutStream);

#endif
