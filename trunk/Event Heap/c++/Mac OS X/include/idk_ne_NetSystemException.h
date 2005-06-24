/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_NetSystemException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_NETSYSTEMEXCEPTION_H_
#define _IDK_NE_NETSYSTEMEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_RuntimeException.h>

/** @file
 Definition of idk_ne_NetSystemException class.
 */

/**
 Thrown to indicate the network subsystem (e.g. winsock on Windows) has been failed.
 */
class IDK_DECL idk_ne_NetSystemException : public idk_ut_RuntimeException {
	IDK_UT_EXCEPTION_DECL(idk_ne_NetSystemException, idk_ut_RuntimeException);
};

#endif
