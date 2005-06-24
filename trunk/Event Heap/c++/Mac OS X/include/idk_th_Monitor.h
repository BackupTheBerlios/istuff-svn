/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_Monitor.h,v 1.5 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_MONITOR_H_
#define _IDK_TH_MONITOR_H_

#include <idk_th_Types.h>
#include <idk_th_Lockable.h>

/** @file
 Definition of idk_th_Monitor class.
 */

/**
 This class provides an inter-thread event notification mechanism.
 <p>A monitor provides a way in which a thread can wait for an event notification
 from another thread.
 There are three types of monitor:
 A single-notification monitor signals an event notification
 to one of the threads currently waiting for an event.
 An all-notification monitor signals an event notification
 to all the threads currently waiting for an event.
 A manual monitor has a state which turns on when an event notification occurs
 and can be turned off explicitly.
 <p>A thread  must own a lock of the monitor when it calls notify(), resetNotify() or wait().
 */
class IDK_DECL idk_th_Monitor : public idk_ut_RealObject, public idk_th_ILockable {
	IDK_UT_REFCOUNTED_IMPL();

public:
	~idk_th_Monitor();

	/**
	 Notifies an event.
	 <p>For a single-notification monitor, it wakes one of the threads
	 currently being blocked in wait() method.
	 For a all-notifiration monitor, it wakes all the threads
	 currently being blocked in wait() method.
	 For a manual monitor, it turns its state on and wakes all the threads
	 being blocked in wait() method.
	 <p>The caller must own a lock of the monitor before calling this method.
	 */
	virtual void notify() = 0;

	/**
	 Resets the state of a manual monitor.
     If the monitor is not manual or is not turned on, this method has no effect.
	 The caller must own a lock of the monitor before calling this method.
	 */
	virtual void resetNotify() = 0;

	/**
	 Waits for an event.
	 <p>This method waits for an event notification on this monitor.
	 The caller must own a lock of the monitor before calling this method -- 
	 the lock will be released before waiting and obtained again when waking up.
	 If the monitor is manual and its state is on, this method returns immediately.
	 <p>If there was no event notification before the specified time elapsed,
	 this method raises idk_th_MonitorTimedoutException.
	 @param timeout The maximum time to wait in milliseconds.  Zero means infinite.
	 @throws idk_th_MonitorTimedoutException Reached to the timeout.
	 @throws idk_th_InterruptedException The thread was interrupted.
	 <i>Not implemented yet.</i>
	 @todo Interruption by idk_th_Thread::interrupt().
	 */
	virtual void wait(idk_long timeout = 0) = 0;

public:
	/**
	 Creates a single-notification monitor.
	 */
	static idk_th_MonitorPtr cs_createSingleNotify();

	/**
	 Creates a all-notification monitor.
	 */
	static idk_th_MonitorPtr cs_createAllNotify();

	/**
	 Creates a manual monitor.
	 */
	static idk_th_MonitorPtr cs_createManual();

protected:
	/**
	 Constants represents type of monitor.
	 <p><i>To IDK developers:
	 cs_createXxx methods creates an instance of the platform-dependent subclass
	 passing one of these values.
	 </i>
	 */
	enum MonitorMode {
		MM_UNKNOWN = 0,
		MM_SINGLESIGNAL = 1,
		MM_ALLSIGNAL = 2,
		MM_MANUAL = 3
	};
};

IDK_UT_SHAREDPTR_DECL(idk_th_Monitor);

#endif
