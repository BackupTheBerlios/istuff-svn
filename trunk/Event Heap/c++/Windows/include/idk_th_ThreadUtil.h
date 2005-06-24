/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_ThreadUtil.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_THREADUTIL_H_
#define _IDK_TH_THREADUTIL_H_

#include <idk_th_Types.h>

/** @file
 Definition of idk_th_ThreadUtil class.
 */

/**
 Provides basic types and utility functions to manipulate threads.
 */
class IDK_DECL idk_th_ThreadUtil
{
public:

	/**
	 Platform dependent type for thread ID,
	 which identifies a specific thread.
	 */
#ifdef WINDOWS
	typedef DWORD tid_t;
#elif defined(unix)
	typedef pthread_t tid_t;
#else
#error unsupported platform
#endif

	/**
	 Platform dependent type for thread handle,
	 which is used to manipulate a thread.
	 <p><i>On Win32, this is different from thread ID.
	 On other platform, maybe we can use the same value with thread ID.
	 </i>
	 */
#ifdef WINDOWS
	typedef HANDLE thread_t; // thread ID
#elif defined(unix)
	typedef pthread_t thread_t;
#else
#error unsupported platform
#endif

	/**
	 The value of thread_t representing nothing.
	 */
	static const thread_t INVALID_THREAD;
	
	/**
	 The value of tid_t representing nothing.
	 */
	static const tid_t INVALID_TID;

	/**
	 Returns the thread ID of the current thread.
	 */
	static tid_t getCurrentThreadID();
};

#endif
