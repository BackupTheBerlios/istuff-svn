/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_RealByteInStream.h,v 1.2 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_REALBYTEINSTREAM_H_
#define _IDK_IO_REALBYTEINSTREAM_H_

#include <idk_io_Types.h>
#include <idk_io_IByteInStream.h>

/** @file
 Definition of idk_io_RealByteInStream class.
 */

/**
 An abstract class mixing idk_io_IByteInStream with idk_ut_RealObject.
 Inheriting this abstract class is an easy way to make your specific
 implementation of byte input stream.
 Note that this class is only for convenience of implementing
 byte input streams, but not for defining a new public operations,
 so there is no appropreate case to use pointer to this class
 instead of idk_io_IByteInStream class.
 */
class IDK_DECL idk_io_RealByteInStream
: public idk_ut_RealObject, public idk_io_IByteInStream {
	IDK_UT_REFCOUNTED_IMPL();
};

#endif
