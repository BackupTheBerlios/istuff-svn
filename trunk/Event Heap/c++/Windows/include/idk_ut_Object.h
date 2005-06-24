/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_Object.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_OBJECT_H_
#define _IDK_UT_OBJECT_H_

#include <idk_ut_Base.h>

/** @file
 The definition of idk_ut_RefCounter class, idk_ut_Object class,
 and support macros for defining reference-counted interfaces.
 */

/**
 Provides the interface of reference counter which can be operated by
 shared-smartpoiner.
 <p>Users usually do not need to care of this class.
 @see idk_ut_TSharedPtr, idk_ut_Object for more details about
 the mechanism of memory management by shared-smartpointer.
 */
class IDK_DECL idk_ut_RefCounter {
public:
	virtual ~idk_ut_RefCounter() {}

	/**
	 Increments the reference counter in a multithread-safe way.
	 <p>Correct behavior is guaranteed under simultaneous calls by multiple threads.
	 */
	virtual void safeRefUp() = 0;

	/**
	 Decrements the reference counter in a multithread-safe way.
 	 <p>When the reference counter reached to zero, the object should
	 be released by itself.
	 Correct behavior is guaranteed under simultaneous calls by multiple threads.
	 */
	virtual void safeRefDown() = 0;

	/**
	 Increments the reference counter in a multithread-unsafe way.
	 <p>Correct behavior is NOT guaranteed under simultaneous calls by
	 multiple threads, but probably faster than multithread-safe version.
	 */
	virtual void unsafeRefUp() = 0;

	/**
	 Decrements the reference counter in a multithread-unsafe way.
 	 <p>When the reference counter reached to zero, the object should
	 be released by itself.
	 Correct behavior is NOT guaranteed under simultaneous calls by
	 multiple threads, but probably faster than multithread-safe version.
	 */
	virtual void unsafeRefDown() = 0;
};

/**
 Declares a reference-counted interface.
 You put this macro inside the definition of an interface,
 then it becomes reference-counted -- it can be held by
 shared-smartpointer.
 A reference-counted interface must be mixed-in with a subclass of
 idk_ut_Object to be actually used, and IDK_UT_REFCOUNTED_IMPL()
 must appear in that class's definition.  A reference-counted
 interface itself must NOT be idk_ut_Object.  Example:
 <pre>
   // IMyInterface.h -- A reference-counted interface of yours

   class IMyInterface {
     IDK_UT_REFCOUNTED_DECL();
   public:
     virtual void ~IMyInterface(); // destructor must be virtual
     virtual void func() = 0;
   };
 </pre>
 <pre>
   // MyObject.h -- A class providing an implementation of IMyInterface

   class MyObject
   : public idk_ut_RealObject, // a reference-counted interface must be mixed-in
     public IMyInterface       // with one of idk_ut_Object subclasses.
   {
     IDK_UT_REFCOUNTED_IMPL(); // you have to say this spell when mix-in.
   public:
     virtual void func();
   };
 </pre>
 <p>Troubleshooting:
 <ul>
  <li>If the compiler complains 'pure virtual function getRefCounter() is not
  implemented', probably you are failing to spell IDK_UT_REFCOUNTED_IMPL()
  when you mix-in the interface.
  <li>If the compiler complains '<i>your class</i>* cannot be converted to
  idk_ut_RefCounter*' regardless you spelled IDK_UT_REFCOUNTED_IMPL() in
  the definition of <i>your class</i>, probably <i>your class</i> is not
  inheriting idk_ut_Object.
 */
#define IDK_UT_REFCOUNTED_DECL() \
public: virtual idk_ut_RefCounter* getRefCounter() = 0;

/**
 Generates necessary implementation for reference-counted interface.
 This macro must appear in the class declaration in which an 
 reference-counted interface is mixed-in.
 @see IDK_UT_REFCOUNTED_DECL() for more details.
 */
#define IDK_UT_REFCOUNTED_IMPL() \
public: virtual idk_ut_RefCounter* getRefCounter() { return this; }

/**
 The base class for those reference-counted classes that can be held by
 shared-smartpointer.
 <p>To define your class as reference-counted so that you can hold it by
 shared-smartpointer, you should derive your class from one of the direct
 subclasses of this class (i.e. idk_ut_RealObject or idk_ut_TProxyObject,
 typically the formar one).  You cannot derive your class from this
 class directly, but you can upcast any reference-counted class to
 this class.
 <p>Multiple inheritance of this class is not allowed like Java.
 Instead, you can mix-in any reference-counted interfaces with this class.
 <p><i>Explanation of the class structure: This class inherits idk_ut_RefCounter
 abstract class.  (The actual implementation of the idk_ut_RefCounter is
 not provided by this class, but by the direct subclasses,
 because there are slight variations.)
 When a smartpointer points this class or any subclass of this class and
 needs to operate the reference counter, it calls getRefCounter() method of
 this class (declared by IDK_UT_REFCOUNTED_DECL() macro) and the method
 returns 'this' (by the implementation provided by IDK_UT_REFCOUNTED_IMPL()
 macro) -- hence the smartpointer eventually obtains the pointer to the
 idk_ut_RefCounter object to be operated.
 This structure works well also when a smartpointer points to any
 reference-counted interface.
 getRefCounter() method of the reference-counted interface should be
 overriden at the point that the interface and idk_ut_Object is mixed,
 so the method surely returns the address of object's actual reference
 counter.
 </i>
 @see idk_ut_RealObject, idk_ut_TProxyObject
 @see IDK_UT_REFCOUNTED_DECL() about reference-counted interface.
 */
class IDK_DECL idk_ut_Object : public idk_ut_RefCounter {
	IDK_UT_REFCOUNTED_DECL();
};

#endif
