/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ne_URLStreamUtil.h,v 1.1 2003/06/02 04:10:46 tomoto Exp $ */

#ifndef _IDK_NE_URLSTREAMUTIL_H_
#define _IDK_NE_URLSTREAMUTIL_H_

#include <idk_ne_Types.h>

/** @file
 Definition of idk_ne_URLStreamUtil class.
 */

/**
 Provides functions to open a URL as an input stream.
 
 This utility class creates an opaque idk_io_IByteInStream object
 from a URL or a simple file name.
 On Win32, <tt>http:</tt>, <tt>ftp:</tt>, <tt>file:</tt>,
 and simple file names are supported.
 On other platforms, only simple file names are supported so far.

 <i>We chose this simple interface instead of something like
 URLInStream which could provide more control on the Internet
 stream.  We think it is good enough to satisfy apps just hoping
 to read files on Web servers.</i>
 */
class IDK_DECL idk_ne_URLStreamUtil {
public:

	/**
	 Creates an input stream from a URL.

	 In the current implementation, streams created by this class
	 only throws idk_io_IOException without no further error
	 classification.

	 @param url URL to open.
	 @throws idk_io_IOException Any errors occured on the Internet connection.
	 @throws idk_io_FileNotFoundException Local file does not exist.
	 @throws idk_ut_PermissionDeniedException Permission denied to access to the local file.
	 @throws idk_ut_OutOfResourceException Ran out of file descriptor.
	 */
	static idk_io_IByteInStreamPtr
	cs_createByUrl(const char* url);

	/**
	 Creates an input stream wrapped by idk_io_ByteBufferInStream from a URL.
	 @param url URL to open.
	 @param bufSize Size of the buffer.
	 @throws idk_io_IOException Any errors occured on the Internet connection.
	 @throws idk_io_FileNotFoundException Local file does not exist.
	 @throws idk_ut_PermissionDeniedException Permission denied to access to the local file.
	 @throws idk_ut_OutOfResourceException Ran out of file descriptor.
	 */
	static idk_io_IByteInStreamPtr
	cs_createBufferedByUrl(const char* url, int bufSize = 4096);
};

#endif
