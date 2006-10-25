/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventHeap.h,v 1.9 2003/06/02 08:02:04 tomoto Exp $ */

#ifndef _EH2_EVENTHEAP_H_
#define _EH2_EVENTHEAP_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_EventHeap class.
 @internal This header belongs to the eh2i_cl component.
 */

class eh2i_cl_EventHeap; // impl

/**
 An Event Heap client.

 <p>This class maintains all the states for an Event Heap client
 instance and provides applications with entry points to invoke
 the server.  An application should obtain this object
 from eh2_EventHeapFactory to peform as an independent
 Event Heap client.
 (This document does not describe about details of
  each Event Heap operation itself.
  Please see other document such as Java API documentation or
  generic Event Heap specification)

 <p>Although limiting an Event Heap client object to be called by only
 one thread could be a good way of keeping your application simple,
 you may also have multiple threads to use one client object.
 Note that there are several rules to observe when you call an
 Event Heap object under multiple threads.
 <ol>
  <li>You must request multithread-safe version of client object
      when creating one.
  <li>When you call any sequenced event operation
      (i.e. getEvent, waitForEvent, etc.),
      you must make sure no other sequenced event operation
	  on the same event type is in progress at the same time.
	  <i>I assume this restriction is acceptable, but we might have to
	  consider relaxing this restriction if users want.
	  I just haven't seen any model so far which I can prove
	  reasonable and general enough to define this behavior.</i>
  <li>You must not call setPerson(), setGroup(), or setTimeout()
      while another thread is calling the client object.
	  <i>We can allow this operation by introducing another lock,
	  but I think there's no point to do so.</i>
 </ol>

 <p>A note about resource sharing: Network connections are shared
 among the client objects born by the same factory.
 However many client objects you create, they uses only one
 network connection as long as the connecting server is the same.

 <p>Query registration functions are provided as well as the original
 Java API, but in a different style.  It is not callback model, but
 only returns an object to wait for the notifications from the server.
 It is up to the application to chose either the same thread or another
 thread to process the notifications.
 <i>I chose this model because of its primitiveness.
 I was not sure whether the callback model, where the client launches
 the worker thread in the background, works well in any usecase.
 For example, how about under the wrapper for another language?
 I assumed more primitive model where the application can put
 everything under its control should come at first.
 Fortunately, launching a thread is very easy by using the IDK,
 so users would be able to implement similar thing to callback.
 However, I don't deny callback model at all, but only delayed to
 provide it for now.  It would be also easy for us to provide
 callback model API on the top of this primitive model.
 </i>
 */
class EH2_DECL eh2_EventHeap :
public idk_ut_TProxyObject<eh2i_cl_EventHeap>
{
private:
	friend class eh2i_cl_EventHeap;
	eh2_EventHeap(eh2i_cl_EventHeap* impl);

public:
	~eh2_EventHeap();

	/**
	 Releases resources used by the object.
	 You cannot use this object after this method was called.
	 */
	void release();

	/**
	 Returns true if the object was already released.
	 */
	int isReleased();

	/**
	 Sets the 'person' infromation to the Event Heap.
	 When you share one Event Heap object among multiple threads,
	 you should set this information in advance of multithread calls.
	 The effect is undefined when this method is called
	 while another thread is using the Event Heap object.

     @param person Person information of this object.  May be NULL.
	 */
	void setPerson(const char* person);

	/**
	 Sets the 'group' infromation to the Event Heap.
	 When you share one Event Heap object among multiple threads,
	 you should set this information in advance of multithread calls.
	 The effect is undefined when this method is called
	 while another thread is using the Event Heap object.

     @param group Group information of this object.  May be NULL.
	 */
	void setGroup(const char* group);

	/**
	 Sets the current setting of timeout.
	 When you share one Event Heap object among multiple threads,
	 you should set this information in advance of multithread calls.
	 The effect is undefined when this method is called
	 while another thread is using the Event Heap object.

	 @param timeout The maximum time to wait for the server response
	 in milliseconds.  Zero means infinite.
	 Note: although the data type of the parameter is idk_long,
	 actually the implementation treats as integer --
	 only lower 32 bits is effective.
	 */
	void setTimeout(idk_long timeout);

	/**
	 Returns the 'person' information of this Event Heap.
	 */
	const char* getPerson() const;

	/**
	 Returns the 'group' information of this Event Heap.
	 */
	const char* getGroup() const;

	/**
	 Returns the maximum time to wait for the response from the server.
	 */
	idk_long getTimeout() const;

	/**
	 Returns the source name of this Event Heap.
	 */
	const char* getSource() const;

	/**
	 Returns the session ID of this Event Heap.
	 */
	int getSessionID() const;

	/**
	 Returns the pointer to the factory which created this Event Heap.
	 */
	const eh2_EventHeapFactory* getFactory() const;

	/**
	 Returns the pointer to the factory which created this Event Heap.
	 */
	eh2_EventHeapFactory* getFactory();

	/**
	 Returns the pointer to the connection which created this Event Heap.
	 */
	eh2_Connection* getConnection();

	//
	// event heap operations
	// note that events for input parameters are non-const since it would
	// be modified by autosetting.
	// the caller is responsible to own the parameter objects.
	//

	/**
	 Executes getEvent operation with single template.

	 @param templateEvent A template event.
	 It will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @return A matched event returned from the server,
	 or NULL if there's no matched event.
	 The caller must take over the ownership of the returned event.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_EventHeapException Another sequenced-event
	 operation is in progress on this object by another thread.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventPtr getEvent(
		eh2_Event* templateEvent
		);

	/**
	 Executes getEvent operation with multiple templates.

	 @param templateEvents A collection of template events.
	 The events will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.
	 @param matchedTemplateEvents
	 [out] If a collection object is passed to this argument,
	 the Event Heap object will set the template events
	 which matched to the returned event into this collection.
	 You can pass NULL if you don't need it.
	 
	 @return A matched event returned from the server,
	 or NULL if there's no matched event.
	 The caller must take over the ownership of the returned event.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_EventHeapException Another sequenced-event
	 operation is in progress on this object by another thread.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventPtr getEvent(
		eh2_EventCollection* templateEvents,
		eh2_EventCollection* matchedTemplateEvents
		);

	/**
	 Executes removeEvent operation with single template.
	 See getEvent(eh2_Event*) for more detail specification.
	 */
	eh2_EventPtr removeEvent(
		eh2_Event* templateEvent
		);

	/**
	 Executes removeEvent operation with multiple templates.
	 See getEvent(eh2_EventCollection*, eh2_EventCollection*)
	 for more detail specification.
	 */
	eh2_EventPtr removeEvent(
		eh2_EventCollection* templateEvents,
		eh2_EventCollection* matchedTemplateEvents
		);

	/**
	 Executes waitForEvent operation with single template.

	 @param templateEvent A template event.
	 It will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @return A matched event returned from the server.  Never be NULL.
	 The caller must take over the ownership of the returned event.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_EventHeapException Another sequenced-event
	 operation is in progress on this object by another thread.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventPtr waitForEvent(
		eh2_Event* templateEvent
		);

	/**
	 Executes waitForEvent operation with multiple templates.

	 @param templateEvents A collection of template events.
	 The events will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.
	 @param matchedTemplateEvents
	 [out] If a collection object is passed to this argument,
	 the Event Heap object will set the template events
	 which matched to the returned event into this collection.
	 You can pass NULL if you don't need it.
	 
	 @return A matched event returned from the server.  Never be NULL.
	 The caller must take over the ownership of the returned event.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_EventHeapException Another sequenced-event
	 operation is in progress on this object by another thread.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventPtr waitForEvent(
		eh2_EventCollection* templateEvents,
		eh2_EventCollection* matchedTemplateEvents
		);

	/**
	 Executes waitToRemoveEvent operation with single template.
	 See waitForEvent(eh2_Event*) for more detail specification.
	 */
	eh2_EventPtr waitToRemoveEvent(
		eh2_Event* templateEvent
		);

	/**
	 Executes waitToRemoveEvent operation with multiple templates.
	 See waitForEvent(eh2_EventCollection*, eh2_EventCollection*)
	 for more detail specification.
	 */
	eh2_EventPtr waitToRemoveEvent(
		eh2_EventCollection* templateEvents,
		eh2_EventCollection* matchedTemplateEvents
		);

	/**
	 Executes snoopEvents operation with single template.

	 @param templateEvent A template event.
	 It will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @return A collection of matched events returned from the server,
	 or NULL if there's no matched events.
	 The caller must take over the ownership of the returned collection.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventCollectionPtr snoopEvents(
		eh2_Event* templateEvent
		);

	/**
	 Executes snoopEvents operation with multiple templates.

	 @param templateEvents A collection of template events.
	 The events will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @return A collection of matched events returned from the server,
	 or NULL if there's no matched events.
	 The caller must take over the ownership of the returned collection.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventCollectionPtr snoopEvents(
		eh2_EventCollection* templateEvents
		);

	/**
	 Executes getAll operation.

	 @return A collection of events returned from the server,
	 or NULL if there's no events.
	 The caller must take over the ownership of the returned collection.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	eh2_EventCollectionPtr getAll();

	/**
	 Executes putEvent operation.

	 @param event Event to be posted.
	 It will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	void putEvent(eh2_Event* event);

	/**
	 Executes putEvent operation and returns immediately
	 without awaiting the response from the server.

	 <p>The request will be queued inside the Event Heap client object
	 and sent asynchronously.
	 Applications should keep the size of the queue reasonablly small.
	 If the application is continuing to put requests into the queue
	 although the network is slow or even the connection is temporarily lost,
	 the size of the queue will increase unexpectedly and
	 it may result intensive impact on the system in various ways.
	 (e.g. memory usage, latency, network bandwidth etc.)
	 Applications can check the count of unsent requests in the queue by
	 eh2_Connection::getBacklogCount(),
	 or monitor the status of the connection by using eh2_ConnectErrorHandler.

	 @param event Event to be posted.
	 It will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	void putEventAsync(eh2_Event* event);

	/**
	 Executes deleteEvent operation.

	 @param event Event to be deleted,
	 It must be an event which was retrieved from the Event Heap.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 @throws eh2_SerializationException Failed to serialize or deserialize an event.
	 */
	void deleteEvent(eh2_Event* event);

	/**
	 Executes clear operation.

	 @throws idk_th_MonitorTimedoutException Reached to timeout.
	 */
	void clear();

	/**
	 Executes registerForAll opertaion and returns eh2_EventRegistration
	 object to receive the notification.

	 @return eh2_EventRegistration object to receive the notification.
	 The query will be deregistered when this object is destructed.

	 @throws eh2_SerializationException Failed to serialize or deserialize an event.

	 @see eh2_EventRegistration
	 */
	eh2_EventRegistrationPtr registerForAll();
	
	/**
	 Executes registerForAll opertaion and returns eh2_EventRegistration
	 object to receive the notification.

	 @param templateEvents A collection of template events.
	 The events will be modified by autoset values supplied by the client object.
	 The ownership is not transferred, so the caller is responsible
	 to keep this object alive during this operation.

	 @return eh2_EventRegistration object to receive the notification.
	 The query will be deregistered when this object is destructed.

	 @throws eh2_SerializationException Failed to serialize or deserialize an event.

	 @see eh2_EventRegistration
	 */
	eh2_EventRegistrationPtr registerForEvents(
		eh2_EventCollection* templateEvents
		);

};

#endif
