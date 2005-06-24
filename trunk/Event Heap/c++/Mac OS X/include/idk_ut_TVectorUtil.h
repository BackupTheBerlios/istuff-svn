/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TVectorUtil.h,v 1.6 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TVECTORUTIL_H_
#define _IDK_UT_TVECTORUTIL_H_

#include <idk_ut_Types.h>
#include <idk_ut_TRealIterator.h>

/** @file
 The definition of idk_ut_TVectorUtil class.
 */

/**
 Parameter-independent part of idk_ut_TVectorUtil class.
 Users do not have to care about this class.
 */
class IDK_DECL idk_ut_VectorUtilBase {
public:
	static int adjustedSize(int requiredSize);
};

/**
 Provides utility functions to handle IDK_UT_VECTOR(T).
 <p>The current implementation of this class provides several functions
 to expand the capacity of vector.
 The motivation to use these functions is the empirical knowledge
 that some implementation of STL does this job in a very inefficient way.
 (We don't like that a memory reallocation occurs each time push_back
  is called, or memory for 1024 elements is allocated at the first
  call of push_back.)
 Using this utility, you can ensure the capacity is aligned on power of 2
 and avoid either too much reallocation or too much waste of memory.
 @param T Type of the element of the vector to be operated.
 */
template <class T>
class IDK_DECL idk_ut_TVectorUtil : protected idk_ut_VectorUtilBase {
public:
	typedef IDK_UT_VECTOR(T) vector_type;

	/**
	 Reserves the capacity of a vector enough to hold the specified
	 number of elements more.
	 It would be a good idea to use this function before you call push_back
	 like the following example:
     <pre>
     IDK_UT_VECTOR(MyClass) v;
     ...
     idk_ut_TVectorUtil&lt;MyClass&gt;::growCapacity(&amp;v);
     v.push_back(myClass);
     </pre>

	 @param pVector [out] An vector to be operated.
	 @param grow size to grow.
	 */
	static void growCapacity(vector_type* pVector, int grow = 1) {
		capacity(pVector, pVector->size() + grow);
	}

	/**
	 Reserves the capacity of a vector enough to hold the specified
	 number of elements.
	 @param pVector [out] An vector to be operated.
	 @param size size to reserve.
	 */
	static void capacity(vector_type* pVector, int size) {
		if (pVector->capacity() < size) {
			pVector->reserve(adjustedSize(size));
		}
	}

	/**
	 Adds the specified number of elements to the vector.
	 @param pVector [out] An vector to be operated.
	 @param grow count of elements fo add.
	 */
	static void growSize(vector_type* pVector, int grow) {
		resize(pVector, pVector->size() + grow);
	}

	/**
	 Resizes the vector.
	 @param pVector [out] An vector to be operated.
	 @param size count of elements.
	 */
	static void resize(vector_type* pVector, int size) {
		capacity(pVector, size);
		pVector->resize(size);
	}

	/**
	 Returns a mutable pointer to the array.
	 <i>Actually, according to the STL specification,
	 there's no guarantee that this implementation works.
	 But, practically, it works.</i>
	 */
	static T* getArray(vector_type* pVector) {
	  return &*(pVector->begin());
	}

	/**
	 Returns a const pointer to the array.
	 <i>Actually, according to the STL specification,
	 there's no guarantee that this implementation works.
	 But, practically, it works.</i>
	 */
	static const T* getArray(const vector_type* pVector) {
	  return &*(pVector->begin());
	}
};


/**
 Iterator implementing idk_ut_ITIterator<T> interface which iterates
 values on a mutable vector.
 <p>Note that this class is reference-semantics unlike STL's iterator.
 You have to allocate this object on the heap, and hold by a
 smartpointer (to keep the ownership) or a pointer (just to reference).
 <p>The type returned by this iterator can be mutable on the vector.
 i.e. Non-constant pointer types or smartpointer types can be acceptable.

 @param VectorType Type of the vector to be iterated.
 @param ResultType Type of returned value which must be compatible
 with the value type of the vector.
 */
template <class VectorType, class ResultType>
class idk_ut_TVectorIterator : public idk_ut_TRealIterator<ResultType>
{
private:
	typename VectorType::iterator m_cur;
	typename VectorType::iterator m_end;
public:
	~idk_ut_TVectorIterator() {}

	/**
	 Creates an object.
	 Allocate the object on the heap, not on the stack.
	 @param pVector Pointer to the vector to be iterated.
	 (Why pointer? because the iterator may modify the vector)
	 */
	idk_ut_TVectorIterator(VectorType* pVector) {
		m_cur = (*pVector).begin();
		m_end = (*pVector).end();
	}

	/**
	 Returns the next value.
	 */
	ResultType next() {
		ResultType result = *m_cur;
		++m_cur;
		return result;
	}

	/**
	 Returns non-zero if there are values left to be iterated.
	 */
	int hasNext() {
		return m_cur != m_end;
	}
};


/**
 Iterator implementing idk_ut_ITIterator<T> interface which iterates
 keys on a constant vector.
 <p>Note that this class is reference-semantics unlike STL's iterator.
 You have to allocate this object on the heap, and hold by a
 smartpointer (to keep the ownership) or a pointer (just to reference).
 <p>The type returned by this iterator should not violate the constness of
 the vector.  i.e. Non-pointer types (e.g. int) or const pointer types
 can be acceptable.

 @param VectorType Type of the vector to be iterated.
 @param ResultType Type of returned value which must be compatible
 with the value type of the vector.
 */
template <class VectorType, class ResultType>
class idk_ut_TVectorConstIterator
: public idk_ut_RealObject, public idk_ut_TRealIterator<ResultType>
{
private:
	typename VectorType::const_iterator m_cur;
	typename VectorType::const_iterator m_end;
public:
	~idk_ut_TVectorConstIterator() {}

	/**
	 Creates an object.
	 Allocate the object on the heap, not on the stack.
	 @param vector Vector to be iterated.
	 */
	idk_ut_TVectorConstIterator(const VectorType& vector) {
		m_cur = vector.begin();
		m_end = vector.end();
	}

	/**
	 Returns the next value.
	 */
	ResultType next() {
		const ResultType& result = *m_cur;
		++m_cur;
		return result;
	}

	/**
	 Returns non-zero if there are keys left to be iterated.
	 */
	int hasNext() {
		return m_cur != m_end;
	}
};


#endif
