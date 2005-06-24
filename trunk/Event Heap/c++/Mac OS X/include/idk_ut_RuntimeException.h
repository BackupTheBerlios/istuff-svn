/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_RuntimeException.h,v 1.3 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_RUNTIMEEXCEPTION_H_
#define _IDK_UT_RUNTIMEEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_Exception.h>

/** @file
 The definition of idk_ut_RuntimeException class.
 */

/**
 This class is the base class of general runtime errors which unavoidably
 occur during normal operations.
 */
class IDK_DECL idk_ut_RuntimeException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(idk_ut_RuntimeException, idk_ut_Exception);
};

#endif
