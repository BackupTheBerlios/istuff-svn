/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_xm_XmlWriter.h,v 1.6 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_XM_XMLWRITER_H_
#define _IDK_XM_XMLWRITER_H_

#include <idk_xm_Types.h>
#include <idk_io_IByteOutStream.h>

/** @file
 Definition of idk_xm_XmlWriter class.
 */

class idki_xm_XmlWriter; // impl

/**
 Provides functionality to write an XML document to an output stream.
 */
class IDK_DECL idk_xm_XmlWriter :
public idk_ut_TProxyObject<idki_xm_XmlWriter>
{
private:
	friend class idki_xm_XmlWriter;
	idk_xm_XmlWriter(idki_xm_XmlWriter* impl);

public:
	
	~idk_xm_XmlWriter();

	/**
	 Sets the output stream to write the XML document.
	 */
	void setStream(idk_io_IByteOutStream* stream);

	/**
	 Gets the output stream currently set to this writer.
	 */
	idk_io_IByteOutStream* getStream();

	/**
	 Writes the head part of a tag which starts an element -- 
	 '</code>&lt;<i>elementName<i><code>'.
	 You should complete the element by calling startElementPost()
	 after you wrote attributes subsequently.
	 */
	void startElementPre(const char* elementName);
	
	/**
	 Writes an attribute -- 
	 '<code> <i>attrName</i>="<i>attrValue</i>"</code>'.
	 You can call this as the times as you need
	 between startElementPre() and startElementPost().
	 Special characters in the value will be escaped.
	 */
	void attribute(const char* attrName, const char* attrValue);

	/**
	 Writes the tail part of a tag which starts an element -- 
	 '<code>&gt;</code>'.
	 Call this to complete the tag opened by startElementPre().
	 */
	void startElementPost();

	/**
	 Writes the tail part of a tag of an empty element -- 
	 '<code>/&gt;</code>'.
	 Call this to complete the tag opened by startElementPre()
	 as an empty element.
	 */
	void startElementPostForEmpty();

	/**
	 Writes a tag with no attributes which starts an element -- 
	 '</code>&lt;<i>elementName<i>&gt;<code>'.
	 This is the shortcut for startElementPre() and startElementPost().
	 */
	void startElement(const char* elementName);

	/**
	 Writes a tag which ends an element -- '</code>&lt;/<i>elementName<i>&gt;<code>'.
	 You do not have to specify the element name since the writer
	 remembers the one used at the start of the element.
	 */
	void endElement();

	/**
	 Writes a text as a part of the content of the current element.
	 Special characters in the value will be escaped.
	 */
	void text(const char* value);

	/**
	 Writes a binary data in a text format.
	 This method encodes the passed binary data in hexadecimal format
	 and write it as part of the content of the current element.
	 You must not embed binary data in an XML document directly.
	 @todo Should we provide some BASE64 encoding version?
	 */
	void binary(const idk_byte* buf, int size);

	/**
	 Writes an element which contents a text -- 
	 '</code>&lt;<i>elementName<i>&gt;<code><i>text</i></code>&lt;/<i>elementName<i>&gt;<code>'.
	 This is the shortcut for startElement() + text() + endElement().
	 */
	void textElement(const char* elementName, const char* value);

public:
	/**
	 Creates an object.
	 @param stream The output stream to write.
	 When you specified NULL, you must set any stream by setStream() later.
	 */
	static idk_xm_XmlWriterPtr
	cs_create(idk_io_IByteOutStream* stream = NULL);

};

IDK_UT_SHAREDPTR_DECL(idk_xm_XmlWriter);

#endif
