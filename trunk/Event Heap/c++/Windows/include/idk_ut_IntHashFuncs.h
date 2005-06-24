/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_IntHashFuncs.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_INTHASHFUNCS_H_
#define _IDK_UT_INTHASHFUNCS_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_IntHashFunc, idk_ut_IntEqualsFunc, 
 idk_ut_PtrHashFunc, idk_ut_PtrEqualsFunc class which can be
 used as template parameters of hash table class.
 @see idk_ut_TFakeHashTable
 */

/**
 Hash function for integer value.
 @see idk_ut_TFakeHashTable, idk_ut_IntEqualsFunc, IDK_UT_INT_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_IntHashFunc {
public:
	/**
	 Returns the hash value of the integer value.
	 */
	int operator()(int value) const;
};

/**
 Equals function for interger value.
 @see idk_ut_TFakeHashTable, idk_ut_IntHashFunc, IDK_UT_INT_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_IntEqualsFunc {
public:
	/**
	 Returns true if the passed values are equivalent.
	 */
	int operator()(int lh, int rh) const {
		return lh == rh;
	}
};

/**
 Hash function for generic pointer value.
 Note that this function care about only the pointer value,
 but the value of the pointee object.
 If you are interested in the value of the object,
 you should use idk_ut_TObjectHashFunc instead.
 @see idk_ut_TFakeHashTable, idk_ut_PtrEqualsFunc, IDK_UT_PTR_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_PtrHashFunc {
public:
	/**
	 Returns the hash value of the passed pointer.
	 */
	int operator()(void* value) const;
};

/**
 Equals function for generic pointer value.
 Note that this function care about only the pointer value,
 but the value of the pointee object.
 If you are interested in the value of the object,
 you should use idk_ut_TObjectEqualsFunc instead.
 @see idk_ut_TFakeHashTable, idk_ut_PtrHashFunc, IDK_UT_PTR_FAKEHASHTABLE()
 */
class IDK_DECL idk_ut_PtrEqualsFunc {
public:
	/**
	 Returns true if the passed pointers are equivalent.
	 */
	int operator()(void* lh, void* rh) const {
		return lh == rh;
	}
};

#endif
