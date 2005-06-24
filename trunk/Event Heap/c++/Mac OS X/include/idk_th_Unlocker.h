/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_Unlocker.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_UNLOCKER_H_
#define _IDK_TH_UNLOCKER_H_

#include <idk_th_Types.h>

/** @file
 Definition of idk_th_Unlocker class.
 */

/**
 Provides a safe way to unlock a lock object temporarily.
 <p>This class releases a lock of the specified idk_th_ILockable
 when an instance is created, and obtains it again when destructed.
 Make sure the thread has already obtained the lock before unlocking it.
 This class is value-semantics, and it would be the most typical
 usage to allocate an instance on the stack.
 */
class IDK_DECL idk_th_Unlocker
{
private:
	idk_th_ILockable* m_lockable;

public:
	~idk_th_Unlocker();

	/**
	 Create an object and unlock the specified lockable.
	 The lock will be obtained again when the object is destructed.
	 */
	idk_th_Unlocker(idk_th_ILockable* lockable);
};

#endif
