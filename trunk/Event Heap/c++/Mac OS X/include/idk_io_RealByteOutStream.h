/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_RealByteOutStream.h,v 1.2 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_REALBYTEOUTSTREAM_H_
#define _IDK_IO_REALBYTEOUTSTREAM_H_

#include <idk_io_Types.h>
#include <idk_io_IByteOutStream.h>

/** @file
 Definition of idk_io_RealByteOutStream class.
 */

/**
 An abstract class mixing idk_io_IByteOutStream with idk_ut_RealObject.
 Inheriting this abstract class is an easy way to make your specific
 implementation of byte output stream.
 Note that this class is only for convenience of implementing
 byte output streams, but not for defining a new public operations,
 so there is no appropreate case to use pointer to this class
 instead of idk_io_IByteOutStream class.
 */
class IDK_DECL idk_io_RealByteOutStream
: public idk_ut_RealObject, public idk_io_IByteOutStream {
	IDK_UT_REFCOUNTED_IMPL();
};

#endif
