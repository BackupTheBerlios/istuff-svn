/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_NoConnectionException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_NE_NOCONNECTIONEXCEPTION_H_
#define _IDK_NE_NOCONNECTIONEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_io_IOException.h>

/** @file
 Definition of idk_ne_NoConnectionException class.
 */

/**
 Thrown to indicate the connection has been lost or not connected yet.
 */
class IDK_DECL idk_ne_NoConnectionException : public idk_io_IOException {
	IDK_UT_EXCEPTION_DECL(idk_ne_NoConnectionException, idk_io_IOException);
};

#endif
