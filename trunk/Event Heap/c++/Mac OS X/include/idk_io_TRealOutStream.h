/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_TRealOutStream.h,v 1.2 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_TREALOUTSTREAM_H_
#define _IDK_IO_TREALOUTSTREAM_H_

#include <idk_io_Types.h>
#include <idk_io_ITOutStream.h>

/** @file
 Definition of idk_io_TRealInStream class.
 */

/**
 An abstract class mixing idk_io_ITOutStream with idk_ut_RealObject.
 Inheriting this abstract class is an easy way to make your specific
 implementation of output stream.
 Users who want to implement byte output stream should use
 idk_io_RealByteOutStream instead of this template.
 Note that this class is only for convenience of implementing output streams,
 but not for defining a new public operations,
 so there is no appropreate case to use pointer to this class
 instead of idk_io_ITOutStream class.
 */
template <class T>
class IDK_DECL idk_io_TRealOutStream
: public idk_ut_RealObject, public idk_io_ITOutStream<T> {
	IDK_UT_REFCOUNTED_IMPL();
};

#endif
