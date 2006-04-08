/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventCollection.h,v 1.4 2003/06/02 08:02:04 tomoto Exp $ */

#ifndef _EH2_EVENTCOLLECTION_H_
#define _EH2_EVENTCOLLECTION_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_EventCollection class.
 @internal This header belongs to the eh2i_ev component.
 */

class eh2i_ev_EventCollection; // impl

/**
 Collection of events.
 This collection holds events with ownership.
 @todo More fancy methods would be helpful. (e.g. remove)
 */
class EH2_DECL eh2_EventCollection :
public idk_ut_TProxyObject<eh2i_ev_EventCollection>
{
private:
	friend class eh2i_ev_EventCollection;
	eh2_EventCollection(eh2i_ev_EventCollection* impl);

public:
	~eh2_EventCollection();

	/**
	 Returns the number of events.
	 */
	int size() const;

	/**
	 Gets the const pointer to <i>i</i>th item.
	 */
	const eh2_Event* get(int i) const;

	/**
	 Gets the smartpointer to <i>i</i>th item.
	 You can keep the returned event either with or without ownership.
	 */
	eh2_EventPtr get(int i);

	/**
	 Adds an event to the collection.
	 The collection takes over the ownership of the passed event.
	 */
	void add(const eh2_EventPtr& eventPtr);

	/**
	 Clears the collection.
	 */
	void clear();

public:
	/**
	 Creates an object.
	 */
	static eh2_EventCollectionPtr cs_create();
};

#endif
