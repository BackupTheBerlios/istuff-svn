/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TUnsharedPtr.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TUNSHAREDPTR_H_
#define _IDK_UT_TUNSHAREDPTR_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_TUnsharedPtr class.
 */

/**
 Unshared-smartpointer which manages an object exclusively.

 <p>Unshared-smartpointer is a pointer-like class which releases
 the pointing object automatically when it is destructed.
 An unshared-smartpointer releases the object regardless it is 
 pointed by any other smartpointers, therefore an relationship
 between unshared-smartpointer and the pointed object must be
 exclusive.  It means unshared-smartpointer is not assignable.
 <p>Usually you should use shared-smartpointer instead of this class
 since it is much more generic way of managing objects.
 The only reason to use unshared-smartpointer is its capability to
 manage any objects even if they are not reference-counted.
 @see idk_ut_TSharedPtr
 */
template <class T>
class IDK_DECL idk_ut_TUnsharedPtr {
private:
	T* m_obj;

public:
	// destructor
	~idk_ut_TUnsharedPtr() {
		detach();
	}

	/**
	 Create an unshared-smartpointer which pointes NULL.
	 */
	idk_ut_TUnsharedPtr() : m_obj(NULL) {
	}

	/**
	 Create an unshared-smartpointer which points the given object.
	 */
	idk_ut_TUnsharedPtr(T* obj) : m_obj(NULL) {
		attach(obj);
	}

	T* operator->() const { checkNull(); return mutableThis()->m_obj; }
	operator T*() const { return mutableThis()->m_obj; }
	T& operator*() const { checkNull(); return *(mutableThis()->m_obj); }

	idk_ut_TUnsharedPtr<T>& operator=(T* obj) {
		if (m_obj != obj) {
			detach();
			attach(obj);
		}
		return *this;
	}

	/**
	 Detach the object from the management of this unshared-smartpointer.
	 This method is the only way to recover the ownership of the pointed object.
	 */
	T* detach() {
		T* obj = m_obj;
		if (m_obj != NULL) {
			delete m_obj;
			m_obj = NULL;
		}
		return obj;
	}

private:
	void attach(T* obj) {
		IDK_UT_ASSERT(m_obj == NULL);
		m_obj = obj;
	}

	// utility
	idk_ut_TUnsharedPtr<T>* mutableThis() const {
		return const_cast<idk_ut_TUnsharedPtr<T>*>(this);
	}
	
	void checkNull() const {
		IDK_UT_ASSERT(m_obj != NULL);
	}

private:
	idk_ut_TUnsharedPtr(const idk_ut_TUnsharedPtr<T>& other); // forbidden
	idk_ut_TUnsharedPtr<T>& operator=(const idk_ut_TUnsharedPtr<T>& other); // forbidden
};

/**
 Macro to declare unshared-smartpointer type for the specified class.
 This macro defines unshared-smartpointer type for class T as TUshPtr.
 */
#define IDK_UT_UNSHAREDPTR_DECL(T) typedef idk_ut_TUnsharedPtr<T> T##UshPtr;

#endif
