/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_IFieldIterator.h,v 1.2 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_IFIELDITERATOR_H_
#define _EH2_IFIELDITERATOR_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <idk_ut_ITIterator.h>

/** @file
 Definition of eh2_IFieldIterator and eh2_IConstFieldIterator class.
 @internal This header belongs to the eh2i_ev package.
 */

/**
 Provides mutable iterator on fields in an event.
 @see eh2_Event::getFieldIterator()
 */
class eh2_IFieldIterator : public idk_ut_ITIterator<eh2_Field*> {
public:
	/** Returns non-zero if there are any fields left to be iterated. */
	virtual int hasNext() = 0;

	/** Returns the next field. */
	virtual eh2_Field* next() = 0;
};

/**
 Provides constant iterator on fields in an event.
 @see eh2_Event::getConstFieldIterator()
 */
class eh2_IConstFieldIterator : public idk_ut_ITIterator<const eh2_Field*> {
public:
	/** Returns non-zero if there are any fields left to be iterated. */
	virtual int hasNext() = 0;

	/** Returns the next field. */
	virtual const eh2_Field* next() = 0;
};

#endif
