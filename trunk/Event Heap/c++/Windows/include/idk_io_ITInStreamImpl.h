/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ITInStreamImpl.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_ITINSTREAMIMPL_H_
#define _IDK_IO_ITINSTREAMIMPL_H_

#include <idk_io_Types.h>
#include <idk_io_EOFException.h>

/** @file
 Implementation of a part of idk_io_ITInStream class.
 Users who want to use input stream for other types than byte type
 should include this file
 somewhere in the source codes and instantiate the template.
 */

template <class T>
IDK_DECL
T
idk_io_ITInStream<T>::
readStream()
{
	T result;
	int readSize = readStream(&result, 1);
	if (readSize == 0) throw idk_io_EOFException();
	return result;
}

template <class T>
IDK_DECL
int
idk_io_ITInStream<T>::
readFull(T* buf, int size)
{
	int totalSize = 0;
	while (totalSize < size) {
		int readSize = readStream(buf + totalSize, size - totalSize);
		if (readSize == 0) break;
		totalSize += readSize;
	}
	return totalSize;
}

#endif
