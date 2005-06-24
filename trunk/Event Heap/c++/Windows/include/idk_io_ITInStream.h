/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ITInStream.h,v 1.5 2004/03/21 17:41:35 tomoto Exp $ */

#ifndef _IDK_IO_ITINSTREAM_H_
#define _IDK_IO_ITINSTREAM_H_

#include <idk_io_Types.h>

/** @file
 Definition of idk_io_ITInStream class.
 */

/**
 Interface of input stream for type T.
 Users who need input stream for byte type should always use
 idk_io_IByteInStream instead of this class.
 Users who need input stream for other types can use this class,
 but note that it is necessary to include idk_io_ITInStreamImpl.h
 somewhere in the source codes and instantiate the template.

 <i>If your had link errors related to readStream() and readFull()
 member functions, please try again with -DIDK_UT_EXPOSE_TEMPLATE_IMPL
 compile option to always include idk_io_ITInStreamImpl.h.
 </i>
 */
template <class T>
class IDK_DECL idk_io_ITInStream  {
	IDK_UT_REFCOUNTED_DECL();

public:
	/** Shared-smartpointer to this class. */
	typedef idk_ut_TSharedPtr<idk_io_ITInStream<T> > Ptr;

public:
	virtual ~idk_io_ITInStream() {}

	/**
	 Skips the specified number of data items.
	 @throws idk_io_IOException
	 */
	virtual int skipStream(int size) = 0;

	/**
	 Returns non-zero if the stream has already reached its end.
	 @throws idk_io_IOException
	 */
	virtual int isEOF() = 0;

	/**
	 Reads the specified number of data items from the stream into array.
	 @return The number of data items actually read.
	 It can be less than the specified size because the data is not available yet.
	 0 means the stream reached its end.
	 @throws idk_io_IOException
	 */
	virtual int readStream(T* buf, int size) = 0;

	/**
	 Closes the stream.
	 @throws idk_io_IOException
	 */
	virtual void closeStream() = 0;

	/**
	 Reads one data item from the stream.
	 @return Read data item.
	 @throws idk_io_IOException, idk_io_EOFException
	 */
	virtual T readStream();

	/**
	 Reads the specified number of data item from the stream into array.
	 Unlike readStream, this method attempts to read exact number as specified
	 unless the stream reached its end.
	 @return The data size actually read.  It can be less than the specific
	 size only when it reached at the EOF.
	 @throws idk_io_IOException
	 */
	virtual int readFull(T* buf, int size);

};

#ifdef IDK_UT_EXPOSE_TEMPLATE_IMPL
#include <idk_io_ITInStreamImpl.h>
#endif

#endif
