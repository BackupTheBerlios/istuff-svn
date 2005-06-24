/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_StringHashFuncs.h,v 1.3 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_STRINGHASHFUNCS_H_
#define _IDK_UT_STRINGHASHFUNCS_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_StringHashFunc, idk_ut_StringEqualsFunc, 
 idk_ut_StringRefHashFunc, idk_ut_StringPtrEqualsFunc class
 which can be used as template parameters of hash table class.
 @see idk_ut_TFakeHashTable
 */

/**
 Hash function for idk_string value.
 @see idk_ut_TFakeHashTable, idk_ut_StringEqualsFunc, IDK_UT_STRING_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_StringHashFunc {
public:
	int operator()(const idk_string& value) const;
};

/**
 Equals function for idk_string value.
 @see idk_ut_TFakeHashTable, idk_ut_StringHashunc, IDK_UT_STRING_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_StringEqualsFunc {
public:
	int operator()(const idk_string& lh, const idk_string& rh) const {
		return lh == rh;
	}
};

/**
 Hash function for const char* value.
 @see idk_ut_TFakeHashTable, idk_ut_StringRefEqualsFunc, IDK_UT_STRINGREF_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_StringRefHashFunc {
public:
	int operator()(const char* p) const;
};

/**
 Equals function for const char* value.
 @see idk_ut_TFakeHashTable, idk_ut_StringRefHashFunc, IDK_UT_STRINGREF_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_StringRefEqualsFunc {
public:
	int operator()(const char* lh, const char* rh) const {
		return strcmp(lh, rh) == 0;
	}
};

#endif
