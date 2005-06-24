/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_BadParameterException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_BADPARAMETEREXCEPTION_H_
#define _IDK_UT_BADPARAMETEREXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_RuntimeException.h>

/** @file
 The definition of idk_ut_BadParameterException class.
 */

/**
 This exception is thrown when an illegal parameter is passed to a function.
 */
class IDK_DECL idk_ut_BadParameterException : public idk_ut_RuntimeException {
	IDK_UT_EXCEPTION_DECL(idk_ut_BadParameterException, idk_ut_RuntimeException);
};

#endif
