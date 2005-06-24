/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_TimedoutIOException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_TIMEDOUTIOEXCEPTION_H_
#define _IDK_IO_TIMEDOUTIOEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_io_IOException.h>

/** @file
 Definition of idk_io_TimedoutIOException class.
 */

/**
 Thrown when an I/O operation reached to timeout.
 */
class IDK_DECL idk_io_TimedoutIOException : public idk_io_IOException {
	IDK_UT_EXCEPTION_DECL(idk_io_TimedoutIOException, idk_io_IOException);
};

#endif
