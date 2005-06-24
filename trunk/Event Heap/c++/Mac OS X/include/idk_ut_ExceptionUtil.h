/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_ExceptionUtil.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_EXCEPTIONUTIL_H_
#define _IDK_UT_EXCEPTIONUTIL_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_ExceptionUtil class and supporting macro for
 implementing exceptions.
 */

/**
 This utility class provides functions to throw exceptions or
 handle caught exceptions.
 */
class IDK_DECL idk_ut_ExceptionUtil {
public:
	/**
	 Logs that an exception caught in a destructor is suppressed.
	 You can call this when you suppress exceptions caught in
	 destructors to observe do-not-throw-exceptions-from-destructor
	 rule but the error should be notified to the operator.
	 You can pass the exception object which was caught to output
	 the content of the exception in the log message.
	 If you do not have the exception object (i.e. you caught
	 the exception by catch(...)), you can call the other version
	 logExceptionInDestructorSuppressed(const char*).
	 The message is logged by idk_ut_LogUtil::log() function.
	 @param className The class name to which the destructor belongs.
	 @param ex the exception object which is suppressed.
	 @see idk_ut_LogUtil::log()
	 */
	static void logExceptionInDestructorSuppressed(
		const char* className,
		idk_ut_Exception& ex
		);

	/**
	 Logs that an exception caught in a destructor is suppressed.
	 See the other version for details.
	 @see logExceptionInDestructorSuppressed(const char*, idk_ut_Exception&)
	 */
	static void logExceptionInDestructorSuppressed(
		const char* className
		);
};

/**
 Macro to generate an implementation of an exception in the standard way.
 Note that this may not work when you implement an exception which have
 its specific member variables.
 */
#define IDK_UT_EXCEPTION_IMPL(CLASS, PARENTCLASS) \
CLASS::~CLASS() {} \
CLASS::CLASS(const char* msg) : PARENTCLASS(#CLASS, msg) {} \
CLASS::CLASS(const char* msg, const idk_ut_Exception& ex) : PARENTCLASS(#CLASS, msg, ex) {} \
CLASS::CLASS(const char* className, const char* msg) : PARENTCLASS(className, msg) {} \
CLASS::CLASS(const char* className, const char* msg, const idk_ut_Exception& ex) : PARENTCLASS(className, msg, ex) {} \
CLASS::CLASS(const CLASS& other) : PARENTCLASS(other) {} \
const char* CLASS::getTypeName() const { return #CLASS; } \
idk_ut_Exception* CLASS::clone() const { return new CLASS(*this); } \
void CLASS::raise() const { throw *this; }

/**
 Macro to generate catch(...) clause only in release build.
 Using catch(...) can avoid crashes when an unexpected error occured,
 but it may also result losing information about what happened.
 By using this macro instead of putting catch(...) directly,
 the program become more easy-to-debug in debug build, 
 and more robust in release build.
 */
#ifndef NDEBUG
#define IDK_UT_CATCH_FINALLY(CODE) /*empty*/
#else
#define IDK_UT_CATCH_FINALLY(CODE) catch (...) { CODE }
#endif

#endif
