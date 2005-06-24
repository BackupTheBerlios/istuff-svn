/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TCollection.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TCOLLECTION_H_
#define _IDK_UT_TCOLLECTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_TVectorUtil.h>

/** @file
 The definition of idk_ut_TConstCollection, idk_ut_TCollection, 
 idk_ut_TArrayCollection, idk_ut_TConstArrayCollection.
 */

/**
 Provides an abstract collection of const pointer.
 @param T Type of the pointed object.
 @see idk_ut_TArrayCollection, idk_ut_TConstArrayCollection
 */
template<class T>
class IDK_DECL idk_ut_TConstCollection : public idk_ut_RealObject {
public:
	/** Smartpointer type to this class */
	typedef idk_ut_TSharedPtr<idk_ut_TConstCollection<T> > Ptr;
	/** Const pointer type to T */
	typedef const T* ConstObjectType;

protected:
	idk_ut_TConstCollection() {}

public:
	~idk_ut_TConstCollection() {}

	/** Returns the size of the collection */
	virtual int size() const = 0;

	/**
	 Returns the <i>i</i>th item of the collection.
	 @return Const pointer to T which points to the <i>i</i>th item.
	 */
	virtual ConstObjectType get(int i) const = 0;
};


/**
 Provides an abstract collection of mutable pointer.
 <p>Note that this class can be casted to idk_ut_TConstCollection<T> also.
 @param T Type of the pointed object.
 @see idk_ut_TArrayCollection
 */
template<class T>
class IDK_DECL idk_ut_TCollection :
public idk_ut_TConstCollection<T>
{
public:
	/** Smartpointer type to this class */
	typedef idk_ut_TSharedPtr<idk_ut_TCollection<T> > Ptr;
	/** Mutable pointer type to T */
	typedef T* ObjectType;
	/** Const pointer type to T (declared in the parent class)*/
	typedef typename idk_ut_TConstCollection<T>::ConstObjectType ConstObjectType;

protected:
	idk_ut_TCollection() {}

public:
	~idk_ut_TCollection() {}

	virtual ConstObjectType get(int i) const = 0;
			// actually this method is declared in the parent class, but
			// VC++ reported compilation error without declaring here...

	/**
	 Returns the <i>i</i>th item of the collection.
	 @return Mutable pointer to T which points to the <i>i</i>th item.
	 */
	virtual ObjectType get(int i) = 0;
};


/**
 Implementation of a collection using an array.
 <p>There are cases where this class is more useful than STL's vector.
 Since this class is reference-semantics, you can write natural code
 to share a collection among pointers or to transfer the ownership
 of a collection.
 Also, you can share a collection hiding the implementation details.
 The example below shows how to share a collection of smartpointers
 as if it is that of simple pointers.
 <p>Example:
 <pre>
   class MyClass {
   private:
     // A collection of MyChildPtr.  However, on the abstract interface,
     // the element is seen as MyChild*.
     idk_ut_TArrayCollection<MyChild, MyChildPtr> m_childrenPtr;

   public:
     MyClass() {
       m_childrenPtr =
         new idk_ut_TArrayCollection<MyChild, MyChildPtr>();
       m_childrenPtr->add(new MyChild(...));
       m_childrenPtr->add(new MyChild(...));
       ...
     }

     idk_ut_TConstCollection<MyChild>* getChildren() const {
         // although the collection is actually that of the smartpointer,
         // it naturally can be casted to that of const pointer.
         return m_childrenPtr;
     }

     idk_ut_TCollection<MyChild>* getChildren() {
         // although the collection is actually that of the smartpointer,
         // it naturally can be casted to that of mutable pointer.
         return m_childrenPtr;
     }
   };
 </pre>
 
 @param T Type of the pointed object on the abstract interface.
 @param VT Actual type of the element of the array.
 This should be either smartpointer or mutable pointer type to T.

 @todo More operations (e.g. remove) may be helpful.
 */
template<class T, class VT>
class IDK_DECL idk_ut_TArrayCollection :
public idk_ut_TCollection<T>
{
public:
	/** Smartpointer to this class. */
	typedef idk_ut_TSharedPtr<idk_ut_TArrayCollection<T, VT> > Ptr;
	/** Actual type of the element of the array. */
	typedef VT HeldValueType;
	/** Const pointer type to T (declared in the parent class) */
	typedef typename idk_ut_TConstCollection<T>::ConstObjectType ConstObjectType;
	/** Mutable pointer type to T (declared in the parent class) */
	typedef typename idk_ut_TCollection<T>::ObjectType  ObjectType;

private:
	IDK_UT_VECTOR(HeldValueType) m_values;

public:
	~idk_ut_TArrayCollection() {}

	/**
	 Creates an object.
	 */
	idk_ut_TArrayCollection() {}

	int size() const { return m_values.size(); }
	ConstObjectType get(int i) const { return (ConstObjectType)m_values[i]; }
	ObjectType get(int i) { return (ObjectType)m_values[i]; }

	/**
	 Provides direct access to the array element.
	 @return Mutable reference to the <i>i</i>th item.
	 */
	HeldValueType& getRaw(int i) { return m_values[i]; }

	/**
	 Adds an element to the collection.
	 */
	void add(const HeldValueType& value) {
		idk_ut_TVectorUtil<HeldValueType>::growCapacity(&m_values);
		m_values.push_back(value);
	}

	/**
	 Clears the collection.
	 */
	void clear() { m_values.clear(); }
};


/**
 Implementation of a collection using an array, which allows only
 const access.
 This class can be used when you have only const pointers of
 aggregated objects.
 @param T Type of the pointed object.
 */
template<class T>
class IDK_DECL idk_ut_TConstArrayCollection :
public idk_ut_TConstCollection<T>
{
public:
	/** Smartpointer to this class. */
	typedef idk_ut_TSharedPtr<idk_ut_TConstArrayCollection<T> > Ptr;
	/** Const pointer type to T (declared in the parent class)*/
	typedef typename idk_ut_TConstCollection<T>::ConstObjectType ConstObjectType;

private:
	IDK_UT_VECTOR(ConstObjectType) m_values;

public:
	~idk_ut_TConstArrayCollection() {}

	/**
	 Creates an object.
	 */
	idk_ut_TConstArrayCollection() {}

	int size() const { return m_values.size(); }
	ConstObjectType get(int i) const { return m_values[i]; }

	/**
	 Adds an element to the collection.
	 */
	void add(const ConstObjectType& value) {
		idk_ut_TVectorUtil<ConstObjectType>::growCapacity(&m_values);
		m_values.push_back(value);
	}
};

#endif
