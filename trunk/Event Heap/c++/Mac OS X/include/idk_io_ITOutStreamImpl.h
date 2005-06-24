/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_ITOutStreamImpl.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_ITOUTSTREAMIMPL_H_
#define _IDK_IO_ITOUTSTREAMIMPL_H_

#include <idk_io_ITOutStream.h>

/** @file
 Implementation of a part of idk_io_ITOutStream class.
 Users who want to use output stream for other types than byte type
 should include this file
 somewhere in the source codes and instantiate the template.
 */

template <class T>
IDK_DECL
void
idk_io_ITOutStream<T>::
writeStream(const T& value)
{
	writeStream(&value, 1);
}

template <class T>
IDK_DECL
int 
idk_io_ITOutStream<T>::
writeFull(const T* buf, int size)
{
	int totalSize = 0;
	while (totalSize < size) {
		int writtenSize = writeStream(buf + totalSize, size - totalSize);
		if (writtenSize == 0) break;
		totalSize += writtenSize;
	}
	return totalSize;
}

#endif
