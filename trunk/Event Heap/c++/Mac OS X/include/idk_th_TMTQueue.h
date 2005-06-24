/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_TMTQueue.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_TMTQUEUE_H_
#define _IDK_TH_TMTQUEUE_H_

#include <idk_th_Types.h>
#include <idk_ut_TQueue.h>
#include <idk_th_Monitor.h>
#include <idk_th_Locker.h>

/** @file
 Definition of idk_th_TMTQueue, idk_th_MTQueueBase class.
 */

/**
 Parameter-independent part of idk_th_TMTQueue class.
 Usually users do not have to care of this class.
 */
class IDK_DECL idk_th_MTQueueBase {
protected:
	idk_th_MonitorPtr m_monitorPtr;
	int m_isClosed;

public:
	~idk_th_MTQueueBase();

	idk_th_MTQueueBase(int maxSize = 0);

	void closeQueueBase();

protected:
	void putPre(int timeout);
	void putPost(int stateChanged);
	void getPre(int timeout);
	void getPost(int stateChanged);

	virtual int isFull() = 0;
	virtual int isEmpty() = 0;

};

/**
 Queue for interthread communication.
 This class provides a queue through which multiple threads can
 send and receive data items.
 */
template <class T>
class IDK_DECL idk_th_TMTQueue
: public idk_ut_RealObject, protected idk_th_MTQueueBase
{
public:
	typedef idk_ut_TSharedPtr<idk_th_TMTQueue<T> > Ptr;

private:
	idk_ut_TQueue<T> m_queue;

protected:
	virtual int isFull() { return m_queue.isFull(); }
	virtual int isEmpty() { return m_queue.isEmpty(); }

public:
	~idk_th_TMTQueue() { closeQueue(); }

	/**
	 Creates an object.
	 @param maxSize The maximum size of the queue.  Zero means infinite.
	 */
	idk_th_TMTQueue(int maxSize = 0)
		: idk_th_MTQueueBase(maxSize), m_queue(maxSize) {}

	/**
	 Tries to put an item into the queue.
	 If the queue is full, wait for one slot to become available.

	 @param value Value to put.
	 @param timeout The maximum time to wait in milliseconds.

	 @throws idk_th_InterruptedException
	 closeQueue was called or the thread was interrupted while waiting.
	 <i>The latter is not implemented yet.</i>
	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 */
	void put(const T& value, int timeout = 0) {
		idk_th_Locker locker(m_monitorPtr); // sync this block
		putPre(timeout);
		int stateChanged = m_queue.isEmpty();
		m_queue.put(value);
		putPost(stateChanged);
	}

	/**
	 Tries to get an item from the queue.
	 If no item exists, wait for one to become available.

	 @param timeout The maximum time to wait in milliseconds.

	 @throws idk_th_InterruptedException
	 closeQueue was called or the thread was interrupted while waiting.
	 <i>The latter is not implemented yet.</i>
	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 */
	T get(int timeout = 0) {
		idk_th_Locker locker(m_monitorPtr); // sync this block
		getPre(timeout);
		int stateChanged = m_queue.isFull();
		T result = m_queue.get();
		getPost(stateChanged);
		return result;
	}

	/**
	 Clears the queue.
	 */
	void clear() {
		idk_th_Locker locker(m_monitorPtr); // sync this block
		m_queue.clear();
	}

	/**
	 Gets the lockable for the queue.
	 You may share this lockable to lock related resources to the queue.
	 */
	idk_th_ILockable* getLockable() { return m_monitorPtr; }

	/**
	 Closes the queue.
	 Once the queue was closed, the queue operations (i.e. put() and get())
	 currently being blocked raise idk_th_InterruptedException
	 immediately, and any subsequent queue operations results
	 the same exceptions also.
	 Note that get() operation works normally as far as there are
	 items in the queue left even after the queue was closed.
	 */
	void closeQueue() { closeQueueBase(); }

	/**
	 Returns the size of the queue
	 */
	int size() { return m_queue.size(); }

};

#endif
