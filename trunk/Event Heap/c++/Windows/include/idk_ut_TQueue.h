/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_TQueue.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TQUEUE_H_
#define _IDK_UT_TQUEUE_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_TQueue class.
 */

/**
 Provides an implementation of FIFO queue.
 This class is value-semantics.
 */
template<class T>
class IDK_DECL idk_ut_TQueue { // value semantics
private:
	IDK_UT_LIST(T) m_values;
	int m_maxSize;

public:
	~idk_ut_TQueue() {}

	/**
	 Creates an object.
	 @param maxSize Maximum size of the queue.
	 When zero is specified, the queue has infinite size.
	 */
	idk_ut_TQueue(int maxSize = 0) : m_maxSize(maxSize) {}

	/**
	 Returns non-zero if the queue is full.
	 */
	int isFull() const { return (m_maxSize > 0 && m_values.size() == m_maxSize); }

	/**
	 Returns non-zero if the queue is empty.
	 */
	int isEmpty() const { return (m_values.size() == 0); }

	/**
	 Puts an item into the queue.
	 You should make sure that the queue is not full before this operation,
	 or you may have an assartion failure.
	 */
	void put(const T& value) {
		IDK_UT_ASSERT(! isFull());
		m_values.push_back(value);
	}

	/**
	 Gets an item from the queue.
	 You should make sure that the queue is not empty before this operation,
	 or you may have an assartion failure.
	 */
	T get() {
		IDK_UT_ASSERT(! isEmpty());
		T value = m_values.front();
		m_values.pop_front();
		return value;
	}

	/**
	 Returns the number of items in the queue.
	 */
	int size() const {
		return m_values.size();
	}
	
	/**
	 Returns the maximum size of the queue.
	 @return Maximum size of the queue.  Zero when infinite.
	 */
	int getMaxSize() const {
		return m_maxSize;
	}

	/**
	 Clears the queue.
	 */
	void clear() {
		m_values.clear();
	}
};

#endif
