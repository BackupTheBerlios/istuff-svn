/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_RealObject.h,v 1.5 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_REALOBJECT_H_
#define _IDK_UT_REALOBJECT_H_

#include <idk_ut_Base.h>
#include <idk_ut_Object.h>

/** @file
 The definition of idk_ut_RealObject class.
 */

/**
 The base class of a reference-counted class which provides
 an actual implementation of reference counter.
 <p>This class is one of the direct subclasses of idk_ut_Object which
 will be most typically used to derive a reference-counted concrete class.
 This class has an actual implementation of reference counter
 and is deleted automatically when the reference counter reached zero.
 Just deriving your class from idk_ut_RealObject, your class becomes
 reference-counted and capable to be managed by smartpointers.
 <p>This class is a reference-semantics class.  You should allocate
 an instance on the heap, and handle it by smartpointers (to keep the
 ownership) or pointers (to just reference).
 Never allocate an instance by using an instance variable.
 Otherwise, you will have serious problems because of attempting to
 free non-heap memory.
 */
class IDK_DECL idk_ut_RealObject : public idk_ut_Object
{
	IDK_UT_REFCOUNTED_IMPL();

private:
	idk_ut_LockedCounter m_refCounter;

public:
	virtual ~idk_ut_RealObject();
	
	/**
	 Deletes the object itself.
	 <p>Called when the reference counter reached zero.
	 <p><i>I defined this method as public and overrideable in case of need,
	 but I don't see any usecase so far.  Do not override or call this!</i>
	 */
	virtual void destroy();

protected:
	/**
	 Protected constructor.
	 */
	idk_ut_RealObject();

public:
	void safeRefUp();
	void safeRefDown();
	void unsafeRefUp();
	void unsafeRefDown();

private:
	// forbid to copy
	idk_ut_RealObject(const idk_ut_RealObject&);
	idk_ut_RealObject& operator=(const idk_ut_RealObject&);
};

#endif
