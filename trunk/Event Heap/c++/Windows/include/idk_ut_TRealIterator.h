/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TRealIterator.h,v 1.2 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TREALITERATOR_H_
#define _IDK_UT_TREALITERATOR_H_

#include <idk_ut_Types.h>
#include <idk_ut_ITIterator.h>

/** @file
 The definition of idk_ut_TRealIterator class.
 */

/**
 An abstract class mixing idk_ut_ITIterator with idk_ut_RealObject.
 Inheriting this abstract class is an easy way to make your specific
 iterator implementation.
 Note that this class is only for convenience of implementing iterators,
 but not for defining a new public operations,
 so there is no appropreate case to use pointer to this class
 instead of idk_ut_ITIterator class.
 */
template <class T>
class IDK_DECL idk_ut_TRealIterator
: public idk_ut_RealObject, public idk_ut_ITIterator<T> {
	IDK_UT_REFCOUNTED_IMPL();

public:
	/** Smartpointer type to this class */
	typedef idk_ut_TSharedPtr<idk_ut_TRealIterator<T> > Ptr;

public:
	~idk_ut_TRealIterator() {}
};

#endif
