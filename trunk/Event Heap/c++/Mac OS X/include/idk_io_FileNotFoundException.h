/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_FileNotFoundException.h,v 1.2 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_FILENOTFOUNDEXCEPTION_H_
#define _IDK_IO_FILENOTFOUNDEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_io_IOException.h>

/** @file
 Definition of idk_io_FileNotFoundException class.
 */

/**
 Thrown to indicate the specified file does not exist.
 */
class IDK_DECL idk_io_FileNotFoundException : public idk_io_IOException {
	IDK_UT_EXCEPTION_DECL(idk_io_FileNotFoundException, idk_io_IOException);
};

#endif
