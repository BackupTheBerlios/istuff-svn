/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_ObjectHashFuncs.h,v 1.3 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_OBJECTHASHFUNC_H_
#define _IDK_UT_OBJECTHASHFUNC_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_TObjectHashFunc, idk_ut_TObjectEqualsFunc 
 class which can be used as template parameters of hash table class.
 @see idk_ut_TFakeHashTable
 */

/**
 Hash function for any reference-semantics object.
 This function actually delegates the calculation of
 the hash value to the object itself. 
 @param PtrType The type of hash key which should be pointer or
 smartpointer to any class.  The pointed class must have method
 'int hashCode()' returning hash value of the object.
 @see idk_ut_TFakeHashTable, idk_ut_TObjectEqualsFunc, IDK_UT_OBJECT_FAKEHASHTABLE()
 */
template <class PtrType>
class IDK_DECL idk_ut_TObjectHashFunc {
public:
	int operator()(const PtrType& value) const {
		return value->hashCode();
	}
};

/**
 Equals function for any reference-semantics object.
 This function actually delegates the comarison to the object itself.
 @param PtrType The type of hash key which should be pointer or
 smartpointer to any class.  The pointed class must have method
 'int equals(other)' returning non-zero if the objects are identical.
 @see idk_ut_TFakeHashTable, idk_ut_TObjectHashFunc, IDK_UT_OBJECT_FAKEHASHTABLE()
 */
template <class PtrType>
class IDK_DECL idk_ut_TObjectEqualsFunc {
public:
	int operator()(const PtrType& lh, const PtrType& rh) const {
		return lh->equals(rh);
	}
};

#endif
