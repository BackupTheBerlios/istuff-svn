/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_Thread.h,v 1.5 2003/06/22 09:24:08 tomoto Exp $ */

#ifndef _IDK_TH_THREAD_H_
#define _IDK_TH_THREAD_H_

#include <idk_th_Types.h>
#include <idk_ut_BridgeObject.h>
#include <idk_th_IRunnable.h>
#include <idk_th_ThreadUtil.h>
#include <idk_th_Lockable.h>

/** @file
 Definition of idk_th_Thread class.
 */

/**
 Provides a set of functions to launch and manipulate threads.
 <p>There are two ways to use this class.
 In one way, you will inherit this class and override run() method.
 In the other way, you will implement idk_th_IRunnable interface
 and pass it to an instance of this object.

 @todo Complete functionality of thread interruption.
 In current implementation, interrupt() only sets the flag which
 can be checked by checkInterrupted(), but blocking interthread
 synchronization (e.g. join()), and maybe blocking I/O, should
 be interrupted.  I have some idea about implementation of this,
 but it needs mucn more consideration to provide safe implementation
 as well as enough abstraction to hide underlying platform.
 */
class IDK_DECL idk_th_Thread
: public idk_ut_RealObject, public idk_th_IRunnable
{
	IDK_UT_REFCOUNTED_IMPL();
	IDK_UT_BRIDGEOBJECT_DECL(idk_ut_Object);

public:
	~idk_th_Thread();

	/**
	 Creates an object.
	 @param name Name of the thread.
	 */
	idk_th_Thread(const char* name = NULL);

	/**
	 Creates an object and set an IRunnable.
	 @param runnablePtr idk_th_IRunnable object to be executed.
	 The thread object takes over the ownership.
	 @param name Name of the thread.
	 */
	idk_th_Thread(
		const idk_th_IRunnablePtr& runnablePtr,
		const char* name = NULL
		);

	/**
	 Returns the name of the thread.
	 */
	const char* getThreadName() const;

	/**
	 Returns the thread handle of the thread.
	 The thread handle is a platform-dependent value used to manipulate
	 a thread.  Usually users do not need to use this.
	 @return The thread handle of the thread currently executed by the object,
	 or idk_th_ThreadUtil::INVALID_THREAD when the thread is inactive.
	 */
	idk_th_ThreadUtil::thread_t getThreadHandle();

	/**
	 Returns the thread ID of the thread.
	 @return The thread ID of the thread currently executed by the object,
	 or idk_th_ThreadUtil::INVALID_TID when the thread is inactive.
	 */
	idk_th_ThreadUtil::tid_t getThreadID();

	/**
	 Starts a new thread and invokes run() of this object or
	 IRunnable object passed to the constructor.
	 <p>The thread exits normally when run() method returns.
	 The thread should not be terminated by other platform-dependent ways.
	 Or, the behavior of the IDK's thread mechanism become undefined.
	 @see run(), idk_th_IRunnable::run()
	 */
	void start();

	/**
	 Returns non-zero if the thread is active.
	 */
	int isActive() const;

	/**
	 Waits for the end of the thread.
	 @throws idk_th_InterruptedException The thread was interrupted.
     <i>Not implemented yet</i>
	 @todo Timeout.  I suspended providing this capability because
	 I was not sure how to implement this on pthread.
	 @todo Interruption by interrupt().
	 */
	void join();

	/**
	 Interrupts the thread.
	 This method sets the interrupted state of the thread which can be
	 checked by checkInterrupted() method.
	 @see checkInterrupted()
	 @todo 'True' interruption mechanism.
	 */
	void interrupt();

	/**
	 Checks whether the thread was interrupted.
	 If the thread is in interrupted state, resets the state and returns true.
	 @see interrupt()
	 */
	int checkInterrupted();

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

	/**
	 Returns the thread object which created the current thread.
	 @return Thread object which created the current thread, 
	 or NULL is the current thread is not created by idk_th_Thread.
	 @todo It returns NULL in the main thread according to the spec,
	 but we could provide pseudo object corresponding to the main thread
	 if it is useful.
	 */
	static idk_th_Thread* cs_getCurrentThread();

	/**
	 Checks whether the current thread was interrupted.
	 If the current thread is not created by idk_th_Thread,
	 this function does nothing and returns 0.
	 */
	static int cs_checkInterrupted();

};

IDK_UT_SHAREDPTR_DECL(idk_th_Thread);

#endif
