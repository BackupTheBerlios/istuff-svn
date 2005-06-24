/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_EOFException.h,v 1.3 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_EOFEXCEPTION_H_
#define _IDK_IO_EOFEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_io_IOException.h>

/** @file
 Definition of idk_io_EOFException class.
 */

/**
 Thrown when an attempt to read/write beyond the end of file was made.
 */
class IDK_DECL idk_io_EOFException : public idk_io_IOException {
	IDK_UT_EXCEPTION_DECL(idk_io_EOFException, idk_io_IOException);
};

#endif
