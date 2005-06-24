/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_Types.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_TYPES_H_
#define _IDK_TH_TYPES_H_

/** @file
 Declaration of typenames of the idk_th package.
 */

// directly dependent packages
#include <idk_ut_Types.h>

// basic types related to thread
#ifdef WINDOWS
#include <windows.h>
#elif defined(unix)
#include <pthread.h>
#else
#error unsupported platform
#endif

// declaration of typenames
class idk_th_Thread;
IDK_UT_SHAREDPTR_DECL(idk_th_Thread);

class idk_th_IRunnable;
IDK_UT_SHAREDPTR_DECL(idk_th_IRunnable);

class idk_th_ILockable;
IDK_UT_SHAREDPTR_DECL(idk_th_ILockable);

class idk_th_Lockable;
IDK_UT_SHAREDPTR_DECL(idk_th_Lockable);

class idk_th_Monitor;
IDK_UT_SHAREDPTR_DECL(idk_th_Monitor);


#endif
