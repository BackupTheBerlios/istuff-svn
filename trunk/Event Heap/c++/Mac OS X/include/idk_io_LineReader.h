/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_LineReader.h,v 1.1 2003/05/08 04:10:54 tomoto Exp $ */

#ifndef _IDK_IO_LINEREADER_H_
#define _IDK_IO_LINEREADER_H_

#include <idk_io_Types.h>

/** @file
 Definition of idk_io_LineReader class.
 */

/**
 This class provides the function to read a stream by each line,
 normalizing the new line characters.
 */
class IDK_DECL idk_io_LineReader : public idk_ut_RealObject {
private:
	idk_io_IByteInStream* m_stream;
	int m_suspendedChar;

public:
	~idk_io_LineReader();
	idk_io_LineReader(idk_io_IByteInStream* stream);

	/**
	 Reads a line from the stream and store it to the passed string object.

	 @param pResult An out parameter to store the line.
	 @return The number of bytes read from the stream.
	 @throws idk_io_IOException
	 */
	int readLine(idk_string* pResult);
};

IDK_UT_SHAREDPTR_DECL(idk_io_LineReader);

#endif
