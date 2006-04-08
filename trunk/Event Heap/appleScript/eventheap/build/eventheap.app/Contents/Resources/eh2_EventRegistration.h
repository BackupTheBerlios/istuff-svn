/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventRegistration.h,v 1.4 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_EVENTREGISTRATION_H_
#define _EH2_EVENTREGISTRATION_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_EventRegistration class.
 @internal This header belongs to the eh2i_cl component.
 */

class eh2i_cl_EventRegistration; // impl

/**
 Receives the notification from the server as the result of
 query registration (such as registerForAll or registerForEvents operation).

 <p>An instance of this class is returned each time when the application
 called registerForAll() or registerForEvents() method of eh2_EventHeap class.
 The application can wait for the result of the registered query
 notified by the server on waitForResult() method of this returned object.
 The registered query is available while this object is alive and will be
 deregistered when the object is abandoned.
 Never destruct the eh2_EventHeap object which created this object
 while the object is still alive.

 <p>If you want to process the notifications asynchronously,
 you need to launch another thread.
 */
class EH2_DECL eh2_EventRegistration :
public idk_ut_TProxyObject<eh2i_cl_EventRegistration>
{
private:
	friend class eh2i_cl_EventRegistration;
	eh2_EventRegistration(eh2i_cl_EventRegistration* impl);

public:
	~eh2_EventRegistration();

	/**
	 Waits for the notification from the server.
	 @param matchedTemplateEvents
	 [out] If an event collection object is passed to this argument,
	 the eh2_EventRegistration object will set the template events
	 which matched to the returned event into this collection.
	 You can pass NULL if you don't need it.
	 @return Event notified by the server.
	 @throw idk_th_MonitorTimedoutException
	 Reached to timeout set by eh2_EventHeap::setTimeout().
	 @throw idk_th_InterruptedException Interrupted by deregister().
	 */
	eh2_EventPtr waitForResult(
		eh2_EventCollection* matchedTemplateEvents
		);

	/**
	 Explicitly deregisters the query.
	 This method explicitly deregisters the query registered with the server.
     If there's another thread blocked in waitForResult() of the object,
	 it returns immediately by throwing idk_th_InterruptedException.
	 Do not call waitForResult() after this method was called.
	 */
	void deregister();
};

#endif
