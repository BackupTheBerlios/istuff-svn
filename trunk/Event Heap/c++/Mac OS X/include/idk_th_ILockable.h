/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_ILockable.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_ILOCKABLE_H_
#define _IDK_TH_ILOCKABLE_H_

#include <idk_th_Types.h>

/** @file
 Definition of idk_th_ILockable interface.
 */

/**
 Provides interface to lock and unlock an object.
 Logically, while a thread owns a lock of an object,
 other threads cannot obtain it.
 idk_th_Lockable provides the standard implementation of inter-thread lock.
 idk_th_Locker (and idk_th_Unlocker also) helps you to manipulate
 idk_th_ILockable in a safe way.
 @see idk_th_Lockable, idk_th_Locker, idk_th_Unlocker
 */
class IDK_DECL idk_th_ILockable {
	IDK_UT_REFCOUNTED_DECL();

public:
	virtual ~idk_th_ILockable() {}

	/**
	 Obtains the lock.
	 */
	virtual void lock() = 0;

	/**
	 Releases the lock.
	 */
	virtual void unlock() = 0;
};

#endif
