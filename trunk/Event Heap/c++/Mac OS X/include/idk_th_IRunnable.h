/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_IRunnable.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_IRUNNABLE_H_
#define _IDK_TH_IRUNNABLE_H_

#include <idk_th_Types.h>

/** @file
 Definition of idk_th_IRunnable.
 */

/**
 Provides interface to execute code.
 You can execute idk_th_IRunnable in another thread using idk_th_Thread.
 @see idk_th_Thread
 */
class IDK_DECL idk_th_IRunnable {
	IDK_UT_REFCOUNTED_DECL();

public:
	virtual ~idk_th_IRunnable() {}

	/**
	 Called when the object is executed.
	 */
	virtual void run() = 0;
};

IDK_UT_SHAREDPTR_DECL(idk_th_IRunnable);

#endif
