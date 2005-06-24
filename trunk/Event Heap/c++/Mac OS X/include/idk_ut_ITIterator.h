/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_ITIterator.h,v 1.3 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_ITITERATOR_H_
#define _IDK_UT_ITITERATOR_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_ITIterator class.
 */

/**
 Interface of iterator.
 This is a reference-counted interface, so you can hold an instance by a
 shared-smartpointer.
 */
template <class T>
class IDK_DECL idk_ut_ITIterator {
	IDK_UT_REFCOUNTED_DECL();

public:
	typedef idk_ut_TSharedPtr<idk_ut_ITIterator<T> > Ptr;

public:
	virtual ~idk_ut_ITIterator() {}

	/**
	 Returns non-zero if there are any elements left to be iterated.
	 */
	virtual int hasNext() = 0;

	/**
	 Returns the next element.
	 */
	virtual T next() = 0;
};

#endif
