/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_SinglePooledThread.h,v 1.1 2003/06/22 09:25:13 tomoto Exp $ */

#ifndef _IDK_TH_SINGLEPOOLEDTHREAD_H_
#define _IDK_TH_SINGLEPOOLEDTHREAD_H_

#include <idk_th_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_th_Thread.h>

/** @file
 Definition of idk_th_SinglePooledThread class.
 */

class idki_th_SinglePooledThreadData;
IDK_UT_SHAREDPTR_DECL(idki_th_SinglePooledThreadData);

/**
 Provides a function that reuse a thread.
 <p>Unlike idk_th_Thread, this class launches a new thread
 only at the first call of start() and reuse the same thread
 at the further calls of start().
 <p>You cannot call start() while the thread is working.
 */

class IDK_DECL idk_th_SinglePooledThread : protected idk_th_Thread
{
	IDK_UT_REFCOUNTED_IMPL();
	IDK_UT_BRIDGEOBJECT_DECL(idki_th_SinglePooledThreadData);

public:
	~idk_th_SinglePooledThread();

	/**
	 Creates an object.
	 @param name Name of the thread.
	 */
	idk_th_SinglePooledThread(const char* name = NULL);

	/**
	 Creates an object and set an IRunnable.
	 @param runnablePtr idk_th_IRunnable object to be executed.
	 The thread object takes over the ownership.
	 @param name Name of the thread.
	 */
	idk_th_SinglePooledThread(
		const idk_th_IRunnablePtr& runnablePtr,
		const char* name = NULL
		);

	/**
	 Invokes run() of this object or the IRunnable object passed
	 to the constructor in another thread.
	 <p>The thread is newly launched at the first call.
	 When run() returned, the thread does not exit but falls asleep
	 to wait for next call of start().
	 @see run(), idk_th_IRunnable::run()
	 */
	void start();

	/**
	 Ends the thread.
	 <p>If the thread is sleeping, ends it immediately.
	 If the thread is working, calls interrupt() to stop the execution of run()
	 and ends the thread after run() returned.
	 You can relaunch the thread by calling start() again.
	 Do not use interrupt() to stop the thread.
	 */
	void stop();

	/**
	 Returns non-zero if the thread is active and working (i.e. not sleeping).
	 <p>Note that this is different from idk_th_Thread::isActive()
	 because the thread itself is active even while sleeping.
	 */
	int isActive() const;

	/**
	 Returns underlying thread object.
	 */
	idk_th_Thread* getThread();

	/**
	 Executed in the new thread.
	 Executed when start() is called, as long as no idk_th_IRunnable was
	 passed to the constructor.  You should override this method when
	 your class inherit this class.
	 @see start()
	 */
	virtual void run();

	/**
	 For internal use.
	 */
	virtual void runWrapper();

};

#endif
