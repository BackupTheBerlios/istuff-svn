/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_Lockable.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_LOCKABLE_H_
#define _IDK_TH_LOCKABLE_H_

#include <idk_th_Types.h>
#include <idk_th_ILockable.h>
#include <idk_ut_TUnsharedPtr.h>

/** @file
 Definition of idk_th_Lockable class.
 */

/**
 Provides a standard implementation of inter-thread lock.
 You can create an instance of this class to use as a lock object,
 or you can derive a subclass from this class and
 make it lockable like a Java object.
 @see idk_ut_ILockable
 */
class IDK_DECL idk_th_Lockable
: public idk_ut_RealObject, public idk_th_ILockable
{
	IDK_UT_REFCOUNTED_IMPL();

private:
	// delegates once to insulate the implementation
	idk_th_ILockablePtr m_lockPtr;

public:
	~idk_th_Lockable();

	/**
	 Creates an object.
	 */
	idk_th_Lockable();

	/**
	 Obtains the lock.
	 If another thread already owned the lock of this object,
	 this function blocks until it becomes available.
	 A thread which already owns the lock can call this method again,
	 but it must call unlock as the same times.
	 */
	void lock();

	/**
	 Releases the lock.
	 A thread must own the lock of the object before calling this function.
	 Or, you may have an assertion failure or other undefined behavior.
	 If the thread called lock() multiple times, the lock will be actually
	 released when this method is called as the same times.
	 */
	void unlock();
};

IDK_UT_SHAREDPTR_DECL(idk_th_Lockable);

#endif
