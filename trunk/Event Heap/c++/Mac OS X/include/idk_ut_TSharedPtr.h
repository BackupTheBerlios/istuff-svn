/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TSharedPtr.h,v 1.7 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TSHAREDPTR_H_
#define _IDK_UT_TSHAREDPTR_H_

#include <idk_ut_Base.h>
#include <idk_ut_Object.h>

/** @file
 The definition of idk_ut_TSharedPtr class.
 */

/**
 Shared-smartpointer which manages an object by using reference counter.

 <p>Shared-smartpointer is a pointer-like class
 which manages an object by operating its reference counter.
 This mechanism provides a safe and generic way to automatically release
 objects which is no longer pointed by any pointer variables.
 An object can be shared among multiple smartpointers,
 so it is also easy to transfer ownership of the object
 from one smartpointer to another.

 <p>A shared-smartpointer-manageable class needs to publish
 an interface to provide its reference counter to the smartpointer.
 The most typical way to define such a class is deriving it from
 idk_ut_RealObject class.  More generic way is provided by macro
 IDK_UT_REFCOUNTED_DECL() and IDK_UT_REFCOUNTED_IMPL().
 See the description of these classes or macros for more detais
 about how to use them.

 <p>To declare the smartpointer type for your class,
 using IDK_UT_SHAREDPTR_DECL() macro would be the most convenient way.
 By putting <code>IDK_UT_SHAREDPTR_DECL(MyClass)</code> after your class's
 definition, <code>MyClassPtr</code> is typedef'ed as an alias of
 <code>idk_ut_TSharedPtr&lt;MyClass&gt;</code>.

 <p>There are several tips to know about the usage of shared-smartpointers.
 <ul>
  <li>Never make mutual or cyclic references by smartpointers.
  The involved objects may not be released forever
  because the reference counters never reached zero.

  <li>Unlike normal pointers, you cannot upcast implicitly a smartpointer for A
  to a smartpointer for B where class B is a parent class of class A.
  You have to call cast() method exlicitly to do this.
  Do likewise when you want to downcast.  Example:
  <pre>
    class A : public B { ... };
    idk_ut_TSharedPtr&lt;A&gt; aPtr;
    idk_ut_TSharedPtr&lt;B&gt; bPtr;

    bPtr = aPtr.cast(); // upcast
    aPtr = (A*)bPtr.cast(); // downcast
  </pre>
  Note that the rule of implicit type conversion is not completely the same
  among compilers.
  Even when you try to implicitly convert from a smartpointer to a normal
  pointer (this kind of conversion is usually supposed to be allowed),
  it might not be successful depending on what compiler you are using,
  whether the target type is the identical class or the parent class,
  whether the function to which the smartpointer is passed is overloaded
  or not, and so forth.

  <li>You may need to include the entire definition of the pointed class
  in any source files where the destructor of smartpointer is called,
  even if you don't call any method of the pointed class.
  If you had uncertain compile errors about smartpointer, check it out.
 </ul>

 <p>Suggested coding guideline when you use shared-smartpointers:
 <ul>
  <li>Use a smartpointer type only when the pointer has an ownership
  (the responsibility to release the pointing object)
  in terms of data structure design.
  Otherwise, i.e. when the pointer only references the object,
  use a normal pointer.
  Being careful to keep ownerships clear, your overall
  design should become clear also, and catastrophic mutual/cyclic
  references should never happen.

  <li>The owner of an object should be only one whenever it can be.
  Although this is not an absolute rule, you should make sure
  if it is the simplest solution when you want to point an object
  by multiple smartpointers.

  <li>Where there is an argument which receives a pointer,
  use normal pointer type as long as no transfer of ownership occur.
  Or use smart pointer type when the ownership is transferred to the callee.
  Whenever a smartpointer appears on an argument, it should be const reference type
  to avoid unnecessary reference counter operation.  Example:
  <pre>
    void printObject(const MyObject*); // no transfer of ownership
    void setObject(const MyObjectPtr&amp;); // the ownership is transferred
  </pre>

  <li>Where there is an return value which returns a pointer,
  use normal pointer type as long as no transfer of ownership occur.
  Or use smartpointer type when the ownership is transferred to the caller.
  Whenever a smartpointer appears on a return value, it should NOT be
  reference type to avoid a dangling reference.  Example:
  <pre>
    const MyObject* getItem() const; // no transfer of ownership
    MyObjectPtr createObject() const; // the ownership is transferred
  </pre>
 </ul>
 */

template <class T>
class idk_ut_TSharedPtr
{
private:
	T* m_obj;

public:
	~idk_ut_TSharedPtr() { detach(); }


	/** Creates a shared-smartpointer holding NULL. */
	idk_ut_TSharedPtr() : m_obj(NULL) {}

	/** Creates a shared-smartpointer holding the given object. */
	idk_ut_TSharedPtr(T* obj) : m_obj(NULL)
			{ attach(obj); }

	/** Copy constructor. */
	idk_ut_TSharedPtr(const idk_ut_TSharedPtr<T>& other) : m_obj(NULL)
			{ attach(other.m_obj); }

	idk_ut_TSharedPtr<T>& operator=(T* obj)
			{ assign(obj); return *this; }
	idk_ut_TSharedPtr<T>& operator=(const idk_ut_TSharedPtr<T>& other)
			{ assign(other); return *this; }

	// comparison
	int operator==(T* obj) { return equals(obj); }
	int operator==(const idk_ut_TSharedPtr<T>& other) { return equals(other); }
	int operator!=(T* obj) { return !equals(obj); }
	int operator!=(const idk_ut_TSharedPtr<T>& other) { return !equals(other); }
	
	// object access
	// note that the smartpointer can return mutable references
	// even if the pointer itself is constant.
	T* operator->() const { checkNull(); return mutableThis()->m_obj; }
	operator T*() const { return mutableThis()->m_obj; }
	T& operator*() const { checkNull(); return *(mutableThis()->m_obj); }

	/**
	 Gets the raw pointer to be used to up/downcast.
	 */
	T* cast() const { return mutableThis()->m_obj; }

private:
	// assignment
	void assign(T* obj)	{
		if (m_obj != obj) {
			detach();
			attach(obj);
		}
	}

	void assign(const idk_ut_TSharedPtr<T>& other) {
		if (m_obj != other.m_obj) {
			detach();
			attach(other.m_obj);
		}
	}

	// comparison
	int equals(T* obj) const {
		return m_obj == obj;
	}

	int equals(const idk_ut_TSharedPtr<T>& other) const {
		return m_obj == other.m_obj;
	}

	// attach & detach
	void attach(T* obj) {
		IDK_UT_ASSERT(m_obj == NULL);
		if (obj != NULL) {
			obj->getRefCounter()->safeRefUp();
		}
		m_obj = obj;
	}

	void detach() {
		if (m_obj != NULL) {
			m_obj->getRefCounter()->safeRefDown();
			m_obj = NULL;
		}
	}

	// utility
	idk_ut_TSharedPtr<T>* mutableThis() const {
		return const_cast<idk_ut_TSharedPtr<T>*>(this);
	}
	
	void checkNull() const {
		IDK_UT_ASSERT(m_obj != NULL);
	}
	
};

/**
 Macro to declare smartpointer type for the specified class.
 This macro defines shared-smartpointer type for class T as TPtr.
 */
#define IDK_UT_SHAREDPTR_DECL(T) typedef idk_ut_TSharedPtr<T> T##Ptr;

IDK_UT_SHAREDPTR_DECL(idk_ut_Object);

#endif
