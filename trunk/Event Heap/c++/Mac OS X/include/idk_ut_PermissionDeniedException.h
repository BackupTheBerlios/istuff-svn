/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_PermissionDeniedException.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_PERMISSIONDENIEDEXCEPTION_H_
#define _IDK_UT_PERMISSIONDENIEDEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_RuntimeException.h>

/** @file
 The definition of idk_ut_PermissionDeniedException class.
 */

/**
 Thrown when an attempt to do an operation without appropreate permission
 was made.
 */
class IDK_DECL idk_ut_PermissionDeniedException : public idk_ut_RuntimeException {
	IDK_UT_EXCEPTION_DECL(idk_ut_PermissionDeniedException, idk_ut_RuntimeException);
};

#endif
