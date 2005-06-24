/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_StrUtil.h,v 1.8 2003/06/24 08:26:40 tomoto Exp $ */

#ifndef _IDK_UT_STRUTIL_H_
#define _IDK_UT_STRUTIL_H_

#include <idk_ut_Types.h>
#include <stdarg.h>

/** @file
 The definition of idk_ut_StrUtil class.
 */

/**
 Utility functions to operate string data.
 <p><i>To IDK developers: Feel free to add necessary methods.</i>
 */
class IDK_DECL idk_ut_StrUtil {
public:
	/**
	 Duplicates a char array.
	 <p>The caller is responsible to delete[] the returned value.
	 Not recommended to use unless absolutely necessary.
	 */
	static char* strdup(const char* value);

	/**
	 Compares string in as the same way as strcmp, but accepts NULL and
	 regards it as less than any other values.
	 */
	static int strcmpNullable(const char* lh, const char* rh);

	/**
	 Converts an integer value to a string.
	 @param pResult [out] A string object to receive the result.
	 @param value An integer value.
	 */
	static void intToStr(idk_string* pResult, int value) {
		pResult->erase(); appendIntToStr(pResult, value);
	}

	/**
	 Converts an integer value to a string and append to the given string.
	 @param pResult [out] A string object to be appended.
	 @param value An integer value.
	 */
	static void appendIntToStr(idk_string* pResult, int value);

	/**
	 Converts an idk_long value to a string.
	 @param pResult [out] A string object to receive the result.
	 @param value An idk_long value.
	 */
	static void longToStr(idk_string* pResult, idk_long value) {
		pResult->erase(); appendLongToStr(pResult, value);
	}

	/**
	 Converts an idk_long value to a string and append to the given string.
	 @param pResult [out] A string object to be appended.
	 @param value An idk_long value.
	 */
	static void appendLongToStr(idk_string* pResult, idk_long value);
	
	/**
	 Similar to vsprintf, but assigns the result to an idk_string.
	 @param pResult [out] A string object to receive the result.
	 */
	static void vstrprintf(idk_string* pResult, const char* format, va_list ap);

	/**
	 Similar to sprintf, but assigns the result to an idk_string.
	 @param pResult [out] A string object to receive the result.
	 */
	static void strprintf(idk_string* pResult, const char* format, ...);

	/**
	 Similar to sprintf, but returns the result as an idk_string.
	 */
	static idk_string strprintf(const char* format, ...);

	/**
	 Deletes whitespace characters at the head and the tail of the string.
	 */
	static idk_string trim(const char* value);

};

#endif
