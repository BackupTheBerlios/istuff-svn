/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_Locker.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_LOCKER_H_
#define _IDK_TH_LOCKER_H_

#include <idk_th_Types.h>

/** @file
 Definition of idk_th_Locker class.
 */

/**
 Provides a way to lock and unlock a lockable object correctly.
 <p>This class obtains a lock of the specified idk_th_ILockable
 when an instance is created, and releases it when destructed.
 This class is value-semantics, and it would be the most typical
 usage to allocate an instance on the stack.
 <p>Example:
 <pre>
    class MyClass {
    private:
      idk_th_LockablePtr m_lockablePtr;

    public:
      MyClass() {
        m_lockablePtr = new idk_th_Lockable();
      }

      void synchronizedFunc() {
        idk_th_Locker lock(m_lockablePtr); // lock the lockable object
        ...
		...
		// the lock is released when 
      }
    };
 </pre>
 @see idk_th_ILockable
 */
class IDK_DECL idk_th_Locker
{
private:
	idk_th_ILockable* m_lockable;

public:
	~idk_th_Locker();

	/**
	 Create an object and lock the specified lockable.
	 The lock will be released when the object is destructed.
	 */
	idk_th_Locker(idk_th_ILockable* lockable);
};

#endif
