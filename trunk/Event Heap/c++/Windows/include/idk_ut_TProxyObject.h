/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TProxyObject.h,v 1.2 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TPROXYOBJECT_H_
#define _IDK_UT_TPROXYOBJECT_H_

#include <idk_ut_Base.h>
#include <idk_ut_Object.h>

/** @file
 The definition of idk_ut_TProxyObject class and supporting macros to utilize it.
 */

/**
 The base class of a reference-counted class which works as an embedded
 proxy for another class.
 <p>This class is one of the direct subclasses of idk_ut_Object which
 can be used when you make an embedded proxy class.
 An 'embedded proxy' is one of the ways of insulation.  Insulation is a
 technique to avoid exposing implementation-related data structures on the
 API headers of your library so that the user applications do not need to
 be recompiled even if the implementation of the library has been changed.
 Applecation programmers need not care about this, but generally
 middleware programmers should.
 <p>An embedded proxy is published to users as a proxy for its implementation
 class.  The proxy has only one member variable which points to the
 implementation class and has API functions which users can call,
 while the implementation class has all messy stuff necessary for the
 implementation.  The proxy delegates all the API function calls to the
 implementation class.
 <p>An embedded proxy is not created as an independent object,
 but embedded as an instance variable inside the implementation class.
 Hence, the proxy has exactly the same lifecycle as the implementation
 class, and they are interchangeable each other -- like different
 faces of an identical object.
 Besides, the operations on the reference counter of a proxy
 are delegated to the implementation class.  It means a smartpointer
 to a proxy works correctly as if it is pointing the actual
 implementation object.  Note that users cannot create a proxy by 
 new operator because the proxy is not an independent object actually,
 therefore it is your library's responsibility to provide a function to
 create an implementation object and returns its proxy.
 A typical example of object creation function will be shown below.
 <p>This class is logically reference-semantics although it is embedded
 as an instance variable in the implementation class.  You will handle
 the object by pointers or smartpointers.
 <p>Example:
 <pre>
   //
   // MyClass.h -- This is the API (proxy) class to be published to the users.
   //

   #include <idk_ut_Types.h> // idk_ut_TProxyObject.h is included

   class MyClassImpl; // declare the implementation class name.
                      // never include the entire class definition!

   class MyClass :
   public idk_ut_TProxyObject<MyClassImpl> // inherit idk_ut_TProxyObject
   {
     // do not put any other member variables on this class.
   private:
     // constructor -- users cannot call, but the implementation class does.
     friend class MyClassImpl;
     MyClass(MyClassImpl* impl);

   public:
     // API functions here.
     void func();

     // creates an object (the alternative of new)
     static MyClassPtr cs_create();
   };
 </pre>
 <pre>
   //
   // MyClassImpl.h -- This is a secret implementation class.
   //

   #include <MyClass.h> // include entire definition of the API (proxy) class

   class MyClassImpl : public idk_ut_Object {
     IDK_UT_PROXYOBJECT_EMBED(MyClass); // embed the proxy as a variable 'm_api'

   private:
     // Implementation-related member variables here.
     // brabrabra
   public:
     // Constructor
	 MyClassImpl();
     // The implementation of API functions here.
     void func();

     // Any other implementation-related functions here.
     // brabrabra
   };

   // declaration of functions to convert between the proxy and the impl.
   // it should come in the implementation header like this.
   IDK_UT_PROXYOBJECT_CONVERT_DECL(MyClass, MyClassImpl);
 </pre>
 <pre>
   //
   // MyClass.cpp
   //

   #include <MyClass.h>
   #include <MyClassImpl.h> // impl

   // Pass the impl to the constructor of idk_ut_TProxyObject.
   MyClass::MyClass(MyClassImpl* impl) :
     idk_ut_TProxyObject<MyClassImpl>(impl)
   {
   }

   void MyClass::func() {
     // get the implementation and delegate to it.
     // fs_impl() is generated by macro IDK_UT_PROXYOBJECT_CONVERT_DECL().
     fs_impl(this)->func();
   }

   MyClassPtr MyClass::cs_create() {
     // create a new object and return its proxy.
     // fs_api() is generated by macro IDK_UT_PROXYOBJECT_CONVERT_DECL().
	 return fs_api( new MyClassImpl() );
   }
 </pre>
 <pre>
   //
   // MyClassImpl.cpp
   //

   #include <MyClassImpl.h>

   // Set 'this' to the proxy.
   // Member variable 'm_api' is created by macro IDK_UT_PROXYOBJECT_EMBED().
   void MyClassImpl::MyClassImpl() : m_api(this) {
   }

   void MyClassImpl::func() {
     // the implementation comes here.
   }
 </pre>
 */
template <class T>
class IDK_DECL idk_ut_TProxyObject : public idk_ut_Object
{
	IDK_UT_REFCOUNTED_IMPL();

private:
	T* m_impl;

protected:
	/**
	 Protected constructor.
	 Any subclasses must have a constructer which receives an implementation
	 object and passes it to this constructor.
	 */
	idk_ut_TProxyObject(T* impl) : m_impl(impl) {}

public:
	~idk_ut_TProxyObject() {}

	T* getImpl() { return m_impl; }
	const T* getImpl() const { return m_impl; }

	/**
	 Increments the reference counter of the implementation in a multithread-safe way. 
	 */
	virtual void safeRefUp();

	/**
	 Decrements the reference counter of the implementation in a multithread-safe way. 
	 */
	virtual void safeRefDown();

	/**
	 Increments the reference counter of the implementation in a multithread-unsafe way. 
	 */
	virtual void unsafeRefUp();

	/**
	 Decrements the reference counter of the implementation in a multithread-unsafe way. 
	 */
	virtual void unsafeRefDown();

private:
	// forbid to copy
	idk_ut_TProxyObject(const idk_ut_TProxyObject<T>&);
	idk_ut_TProxyObject& operator=(const idk_ut_TProxyObject<T>&);
};

/**
 Generates necessary functions to retrieve the implementation from the
 API class, and vice versa.
 <p>You put this macro in the header file of the implementation class,
 then an inline function 'fs_impl()' and 'fs_api()' will be generated.
 You can retrieve the implementation from a proxy by calling fs_impl(),
 and vice versa by calling fs_api().
 @param PROXYTYPE The name of the proxy, namely API class.
 @param IMPLTYPE The name of the implementation class.
 @see idk_ut_ProxyObject
 */
#define IDK_UT_PROXYOBJECT_CONVERT_DECL(PROXYTYPE, IMPLTYPE) \
inline IMPLTYPE* fs_impl(PROXYTYPE* obj) { \
	return (IMPLTYPE*)(obj ? obj->getImpl() : NULL); \
} \
inline const IMPLTYPE* fs_impl(const PROXYTYPE* obj) { \
	return (IMPLTYPE*)(obj ? obj->getImpl() : NULL); \
} \
inline PROXYTYPE* fs_api(IMPLTYPE* obj) { \
	return obj ? obj->getAPI() : NULL; \
} \
inline const PROXYTYPE* fs_api(const IMPLTYPE* obj) { \
	return obj ? obj->getAPI() : NULL; \
} \
inline IMPLTYPE* fs_impl(const idk_ut_TSharedPtr<PROXYTYPE>& obj) { \
	return (IMPLTYPE*)(obj ? obj->getImpl() : NULL); \
} \
inline PROXYTYPE* fs_api(const idk_ut_TSharedPtr<IMPLTYPE>& obj) { \
	return obj ? obj->getAPI() : NULL; \
} \
inline void idk_ut_TProxyObject<IMPLTYPE>::safeRefUp() { \
	m_impl->getRefCounter()->safeRefUp(); \
} \
inline void idk_ut_TProxyObject<IMPLTYPE>::safeRefDown() { \
	m_impl->getRefCounter()->safeRefDown(); \
} \
inline void idk_ut_TProxyObject<IMPLTYPE>::unsafeRefUp() { \
	m_impl->getRefCounter()->unsafeRefUp(); \
} \
inline void idk_ut_TProxyObject<IMPLTYPE>::unsafeRefDown() { \
	m_impl->getRefCounter()->unsafeRefDown(); \
}


/**
 Embeds a proxy inside the definition of the implementation class.
 <p>You put this macro inside the definition of the implementation class,
 then a member variable 'm_api' of the proxy type is generated.
 You must set the address of the implementation object by passing 'this' to
 the constructor of this variable in the constructor of the implementation
 class.
 @param PROXYTYPE The name of the proxy, namely API class.
 @see idk_ut_ProxyObject
 */
#define IDK_UT_PROXYOBJECT_EMBED(PROXYTYPE) \
private: PROXYTYPE m_api; \
public: PROXYTYPE* getAPI() { return &m_api; } \
public: const PROXYTYPE* getAPI() const { return &m_api; }

#endif
