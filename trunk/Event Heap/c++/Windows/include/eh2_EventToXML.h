/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventToXML.h,v 1.4 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_EVENTTOXML_H_
#define _EH2_EVENTTOXML_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <idk_io_IByteOutStream.h>
#include <idk_xm_XmlWriter.h>

/** @file
 Definition of eh2_EventToXML class.
 @internal This header belongs to the eh2i_ev package.
 */

class eh2i_ev_EventToXML; // impl

/**
 Formats events in an XML format.
 This class would be convenient for debugging.
 */
class EH2_DECL eh2_EventToXML :
public idk_ut_TProxyObject<eh2i_ev_EventToXML>
{
private:
	friend class eh2i_ev_EventToXML;
	eh2_EventToXML(eh2i_ev_EventToXML* impl);

public:
	~eh2_EventToXML();

	/**
	 Formats an event in an XML format and writes to the given output stream.
	 */
	void convert(
		idk_io_IByteOutStream* os,
		const eh2_Event* event
		);

	/**
	 Formats events in an XML format and writes to the given output stream.
	 */
	void convert(
		idk_io_IByteOutStream* os,
		const eh2_EventCollection* events
		);

	/**
	 Formats an event in an XML format through the given XML writer.
	 This method would be convenient if you want to embed the event
	 as a part of your XML document.
	 */
	void convert(
		idk_xm_XmlWriter* xmlWriter,
		const eh2_Event* event
		);

	/**
	 Formats events in an XML format through the given XML writer.
	 This method would be convenient if you want to embed the events
	 as a part of your XML document.
	 */
	void convert(
		idk_xm_XmlWriter* xmlWriter,
		const eh2_EventCollection* events
		);

public:
	/**
	 Creates an instance of this class.
	 */
	static eh2_EventToXMLPtr cs_create();
};

#endif
