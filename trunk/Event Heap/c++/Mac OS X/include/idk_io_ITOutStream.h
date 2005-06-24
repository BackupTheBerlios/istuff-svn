/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ITOutStream.h,v 1.5 2004/03/21 17:41:35 tomoto Exp $ */

#ifndef _IDK_IO_ITOUTSTREAM_H_
#define _IDK_IO_ITOUTSTREAM_H_

#include <idk_ut_Types.h>

/** @file
 Definition of idk_io_ITOutStream class.
 */

/**
 Interface of output stream for type T.
 Users who need output stream for byte type should always use
 idk_io_IByteOutStream instead of this class.
 Users who need output stream for other types can use this class,
 but note that it is necessary to include idk_io_ITOutStreamImpl.h
 somewhere in the source codes and instantiate the template.

 <i>If your had link errors related to writeStream() and writeFull()
 member functions, please try again with -DIDK_UT_EXPOSE_TEMPLATE_IMPL
 compile option to always include idk_io_ITOutStreamImpl.h.
 </i>
 */
template <class T>
class IDK_DECL idk_io_ITOutStream {
	IDK_UT_REFCOUNTED_DECL();

public:
	/** Shared-smartpointer to this class. */
	typedef idk_ut_TSharedPtr<idk_io_ITOutStream<T> > Ptr;

public:
	virtual ~idk_io_ITOutStream() {}

	/**
	 Writes the specified number of data items to the stream.
	 @return The number of data items actually written.
	 It can be less than the specified size because the space
	 is not available temporarily.
	 @throws idk_io_IOException
	 */
	virtual int writeStream(const T* buf, int size) = 0;

	/**
	 Closes the stream.
	 @throws idk_io_IOException
	 */
	virtual void closeStream() = 0;

	/**
	 Flushes the stream.
	 If the stream keeps inside any data waiting for being actually written,
	 it should be processed immediately.
	 @throws idk_io_IOException
	 */
	virtual void flushStream() = 0;

	/**
	 Writes one data item to the stream.
	 @throws idk_io_IOException
	 */
	virtual void writeStream(const T& value);


	/**
	 Writes the specified number of data items to the stream.
	 Unlike writeStream, this method attemps to write exact number as specified.
	 @return The data size actually read.
	 @throws idk_io_IOException
	 */
	virtual int writeFull(const T* buf, int size);
};

#ifdef IDK_UT_EXPOSE_TEMPLATE_IMPL
#include <idk_io_ITOutStreamImpl.h>
#endif

#endif
