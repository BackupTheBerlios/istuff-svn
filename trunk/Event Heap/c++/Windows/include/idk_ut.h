/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut.h,v 1.7 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_H_
#define _IDK_UT_H_

/** @file
 This file includes all definitions of the idk_ut package.
 The idk_ut package provides a set of fundamental definitions and
 functionalities such like basic data types, basic data structures,
 automatic memory management, system operation, exception handling,
 etc. in a platform independent way.
 */

// Interfaces
#include <idk_ut_ITIterator.h>
#include <idk_ut_ILogger.h>

// Classes
#include <idk_ut_Types.h>
#include <idk_ut_ByteArray.h>
#include <idk_ut_NullableString.h>
#include <idk_ut_TCollection.h>
#include <idk_ut_TQueue.h>
#include <idk_ut_TFakeHashTable.h>
#include <idk_ut_Tracer.h>
#include <idk_ut_DateStruct.h>

// Utilities
#include <idk_ut_StrUtil.h>
#include <idk_ut_SystemUtil.h>
#include <idk_ut_TVectorUtil.h>
#include <idk_ut_LogUtil.h>
#include <idk_ut_ExceptionUtil.h>

// Exceptions
#include <idk_ut_Exception.h>
#include <idk_ut_AssertionFailedException.h>
#include <idk_ut_BadParameterException.h>
#include <idk_ut_OutOfResourceException.h>
#include <idk_ut_PermissionDeniedException.h>
#include <idk_ut_RuntimeException.h>

#endif
