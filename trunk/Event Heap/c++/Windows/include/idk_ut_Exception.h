/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_Exception.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_EXCEPTION_H_
#define _IDK_UT_EXCEPTION_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_Exception class.
 */

/**
 This is the base class of all exceptions.
 Each exception holds a message string which is created from
 the concrete exception class name and the given string,
 and optional nested exception.
 <p><i>I did not insulate this class.  I hope it will be alright.</i>
 */
class IDK_DECL idk_ut_Exception {
private:
	idk_string m_msg;

protected:
	/**
	 Constructor for subclasses.
	 @param className The name of the concrete class.
	 @param msg The message string.
	 */
	idk_ut_Exception(
		const char* className,
		const char* msg
		);

	/**
	 Constructor for subclasses.
	 @param className The name of the concrete class.
	 @param msg The message string.
	 @param ex The nested exception.
	 */
	idk_ut_Exception(
		const char* className,
		const char* msg,
		const idk_ut_Exception& ex
		);

public:
	virtual ~idk_ut_Exception();

	/**
	 Construct the object with a message string.
	 @param msg The message string.
	 */
	idk_ut_Exception(const char* msg = NULL);

	/**
	 Construct the object with a message string and a nested exception.
	 @param The message string.
	 @param ex The nested exception.  The message string of the nested
	 exception will become a part of the message string of the new
	 exception.
	 */
	idk_ut_Exception(const char* msg, const idk_ut_Exception& ex);

	/**
	 Copy constructor.
	 */
	idk_ut_Exception(const idk_ut_Exception& other);

	/**
	 Gets the message string.
	 */
	virtual const char* getMessage() const;

	/**
	 Gets the class name of the concrete exception class.
	 All subclasses must override this method to return its class name.
	 */
	virtual const char* getTypeName() const;

	/**
	 Clones the object.
	 This method is useful when you want to carry an exception out of
	 the catch clause.  Generally you can't use normal copy because of
	 the slicing issue.  Cloned object will be held by a pointer value,
	 so you will break the value-semantics-object rule when you use
	 this function.
	 All subclasses must override this method to create and return
	 a cloned object on the heap.
	 */
	virtual idk_ut_Exception* clone() const;

	/**
	 Throws the object itself.
	 This method is useful when you re-throw the cloned exception.
	 Generally you can't use 'throw ex' to re-throw because of the
	 slicing issue.
	 */
	virtual void raise() const;
	
};

/**
 Macro to declare the common methods for exception subclasses.
 <p>Use as the following exsample:
 <pre>
 class MyException : public idk_ut_Exception {
     IDK_UT_EXCEPTION_DECL(MyException, idk_ut_Exception);
 };
 </pre>
 <p>To generate the implementation of the declared methods, you can use
 IDK_UT_EXCEPTION_IMPL(CLASS, PARENTCLASS) macro provided by
 idk_ut_ExceptionUtil.h.
 Note that these macro may not work if you want to make an exception
 subclass which has its specific member variables.
 */
#define IDK_UT_EXCEPTION_DECL(CLASS, PARENTCLASS) \
protected: \
	CLASS(const char* className, const char* msg); \
	CLASS(const char* className, const char* msg, const idk_ut_Exception& ex); \
	\
public: \
	~CLASS(); \
	CLASS(const char* msg = NULL); \
	CLASS(const char* msg, const idk_ut_Exception& ex); \
	CLASS(const CLASS& other); \
	virtual const char* getTypeName() const; \
	virtual idk_ut_Exception* clone() const; \
	virtual void raise() const;

#endif
