/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_AssertionFailedException.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_ASSERTIONFAILEDEXCEPTION_H_
#define _IDK_UT_ASSERTIONFAILEDEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_RuntimeException.h>

/** @file
 The definition of idk_ut_AssertionFailedException class.
 */

/**
 This exception is thrown to indicate an assertion failure.
 <p>When the IDK_UT_ASSERT macro detected an assertion failure, and if the
 release version of IDK library is linked, this exception should be thrown.
 Note that in the debug version the assertion failure causes immediate abort.
 */
class IDK_DECL idk_ut_AssertionFailedException : public idk_ut_RuntimeException {
	IDK_UT_EXCEPTION_DECL(idk_ut_AssertionFailedException, idk_ut_RuntimeException.);
};

#endif
