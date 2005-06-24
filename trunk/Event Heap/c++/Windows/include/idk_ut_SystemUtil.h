/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_SystemUtil.h,v 1.6 2003/06/06 18:05:05 tomoto Exp $ */

#ifndef _IDK_UT_SYSTEMUTIL_H_
#define _IDK_UT_SYSTEMUTIL_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_SystemUtil class.
 */

/**
 Provides wrapper functions to do platform dependent operations.
 @todo Implementatino for other platform than Win32.
 */
class IDK_DECL idk_ut_SystemUtil {
public:
	/**
	 Increments a variable as an atomic operation.
	 @param pValue [out] A variable to be incremented.
	 @return the result of operation.
	 */
	static idk_ut_LockedCounter interlockedIncrement(idk_ut_LockedCounter* pValue);

	/**
	 Decrements a variable as an atomic operation.
	 @param pValue [out] A variable to be incremented.
	 @return the result of operation.
	 */
	static idk_ut_LockedCounter interlockedDecrement(idk_ut_LockedCounter* pValue);

	/**
	 Gets the name of the executable file currently executing.
	 */
	static idk_string getExeFileName();

	/**
	 Generates a pseudo-random number in range of [0,1) double.
	 @see srand()
	 */
	static double random();

	/**
     Generates a pseudo-random number in range of 32bit integer.
	 @see srand()
	 */
	static int randomInt();

	/**
	 Initializes the seed of the pseudo-random number generation
	 by the current time.
	 This function initializes the seed of pseudo-random number generation
	 by using the result of getCurrentTimeMillis().
	 This function is called automatically when you call idk_init().
	 @see random(), randomInt(), getCurrentTimeMillis(), idk_init()
	 */
	static void srand();

	/**
	 Sleeps for the specified milliseconds.
	 @param msecs The time to sleep in milliseconds.
	 */
	static void sleep(int msecs);

	/**
	 Returns the elapsed time since 00:00:00 Jan 1, 1970 UTC in milliseconds.
	 */
	static idk_long getCurrentTimeMillis();

	/**
	 Sets the current local date and time to the passed idk_ut_DateStruct.

	 @param pDate [out] Pointer to the idk_ut_DateStruct object to set
	 the result.
	 */
	static void getCurrentDateTime(idk_ut_DateStruct* pDate);
	
	/**
	 Gets the error message for the last system error.

	 @param pResult [out]
	 @return Non-zero for success, Zero for no message found.
	 */
	static int getLastErrorMessage(idk_string* pResult);

	/**
	 Gets the error message for the given system error.

	 @param code The platform dependent system error code
	 (i.e. GetLastError() on Win32, errno on Unix)
	 which can be obtained by getLastErrorCode().
	 @param pResult [out]
	 @return Non-zero for success, Zero for no message found.
	 */
	static int getErrorMessage(int code, idk_string* pResult);

	/**
	 Gets the platform-dependent error code of the last system error.
	 @return Platform dependent system error code,
	 i.e. GetLastError() on Win32, errno on Unix.
	 */
	static int getLastErrorCode();
};

#endif
