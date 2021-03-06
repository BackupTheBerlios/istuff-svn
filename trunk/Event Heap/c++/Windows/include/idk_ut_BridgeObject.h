/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_BridgeObject.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_BRIDGEOBJECT_H_
#define _IDK_UT_BRIDGEOBJECT_H_

#include <idk_ut_Types.h>

/** @file
 Provides a set of macros to define/implement a bridge class.
 <p>A 'bridge' is one of the ways of insulation.  Insulation is a technique to
 avoid exposing implementation-related data structures on the API headers
 of your library so that the user applications do not need to be recompiled
 even if the implementation of the library has been changed.
 Applecation programmers need not care about this, but generally
 middleware programmers should.
 <p>A bridge is formed by a pair of an API class and an implementation class.
 On the API class, you will put only one member variable which points to the
 implementation class and API functions which are published to the users,
 while the implementation class has all messy stuff necessary for the
 implementation.  The API class delegates all the API function calls to the
 implementation class.
 <p>This header file provides macros which help you with defining and
 implementing a bridge.
 <p>Example:
 <pre>
   //
   // MyClass.h -- This is the API class to be published to the users.
   //

   #include <idk_ut_BridgeObject.h>

   class MyClassImpl; // declare the implementation class name.
                      // never include the entire class definition!
   class MyClass {
     IDK_UT_BRIDGEOBJECT_DECL(MyClassImpl);
       // declare necessary members to form a bridge.
       // do not put any other member variables on this class.
   public:
     // API functions here.
     MyClass();
     void func();
   };
 </pre>
 <pre>
   //
   // MyClassImpl.h -- This is a secret implementation class.
   //

   class MyClassImpl : public idk_ut_Object {
   private:
     // Implementation-related member variables here.
     // brabrabra
   public:
     // The implementation of API functions here.
     void func();

     // Any other implementation-related functions here.
     // brabrabra
   };
 </pre>
 <pre>
   //
   // MyClass.cpp
   //

   #include <MyClass.h>

   IDK_UT_BRIDGEOBJECT_CONVERT_DECL(MyClass, MyClassImpl);

   MyClass::MyClass() {
     // create the implementaion when constructed.
     // m_implPtr is generated by macro IDK_UT_BRIDGEOBJECT_DECL().
     m_implPtr = new MyClassImpl();
   }

   void MyClass::func() {
     // get the implementation and delegate to it.
     // fs_impl() is generated by macro IDK_UT_BRIDGEOBJECT_CONVERT_DECL().
     fs_impl(this)->func();
   }
 </pre>
 <pre>
   //
   // MyClassImpl.cpp
   //

   #include <MyClassImpl.h>

   void MyClassImpl::func() {
     // the implementation comes here.
   }
 </pre>
 */

/**
 Generates necessary members for the API class of a bridge.
 <p>You put this macro inside the API class definition, then a member
 variable 'm_implPtr' whose type is smartpointer to the impl class
 will be generated.  You need to assign an instance of the impl class
 to m_implPtr when the API class is constructed.
 <p>Note that you have to specify the type of the impl class to this macro.
 It means you have to declare the name of the impl class, but not the class
 definition itself, in advance.  If you hate this, it is also your option
 to specify any acceptable parent class of the implementation class.
 For example, if your implementation class inherits idk_ut_Object class,
 you can specify idk_ut_Object instead of the actual implementation class.
 The cost you would pay by doing this is a bit dangerous downcast in your
 delegation code, but generally it would be negligible since the actual type
 should be obvious and the downcast is encapsulated inside another macro.

 @param IMPLCLASS The name of the implementation class or a parent class
 of the implementation class.
 */
#define IDK_UT_BRIDGEOBJECT_DECL(IMPLTYPE) \
private: idk_ut_TSharedPtr<IMPLTYPE> m_implPtr; \
public: IMPLTYPE* getImpl() { return m_implPtr; } \
public: const IMPLTYPE* getImpl() const { return m_implPtr; }

/**
 Generates necessary functions to retrieve the implementation from the
 API class.
 <p>You put this macro in the source (.cpp) of the API class,
 then an inline function 'fs_impl()' will be generated.
 You can retrieve the implementation by calling fs_impl(this) from
 inside the member function of the API class.
 <p>fs_impl() automatically downcasts m_implPtr to the actual impl class
 when m_implPtr is type of a parent class of the impl class.

 @param BRIDGETYPE The name of the API class.
 @param IMPLTYPE The name of the implementation class.  You should specify
 the actual class even if you passed a parent class of it to
 IDK_UT_BRIDGEOBJECT_DECL() macro in the API class definition.
 */
#define IDK_UT_BRIDGEOBJECT_CONVERT_DECL(BRIDGETYPE, IMPLTYPE) \
inline IMPLTYPE* fs_impl(BRIDGETYPE* obj) { \
	return (IMPLTYPE*)(obj ? obj->getImpl() : NULL); \
} \
inline const IMPLTYPE* fs_impl(const BRIDGETYPE* obj) { \
	return (IMPLTYPE*)(obj ? obj->getImpl() : NULL); \
}

#endif
