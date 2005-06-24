/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_IOException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_IOEXCEPTION_H_
#define _IDK_IO_IOEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_Exception.h>

/** @file
 Definition of idk_io_IOException class.
 */

/**
 This is the base class of errors which occurs during I/O operations.
 */
class IDK_DECL idk_io_IOException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(idk_io_IOException, idk_ut_Exception);
};

#endif
