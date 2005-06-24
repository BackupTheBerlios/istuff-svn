/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_FileUtil.h,v 1.4 2003/06/06 23:03:43 tomoto Exp $ */

#ifndef _IDK_IO_FILEUTIL_H_
#define _IDK_IO_FILEUTIL_H_

#include <idk_io_Types.h>

/** @file
 Definition of idk_io_FileUtil class.
 */

/**
 Provides functions to operate files.
 @todo To IDK developers: Feel free to add necessary functions.
 */
class IDK_DECL idk_io_FileUtil {
public:
	/**
	 Split a path name into two parts -- directory and file name.
	 @param fullPath Parh name to split.
	 @param pDirPart [out] String object to receive the directory part.
	 The result includes the trailing path separator.
	 May be null if you don't want it.
	 @param pFileNamePart [out] String object to receive the file name part.
	 May be null if you don't want it.
	 */
	static void splitPath(
		const char* fullPath,
		idk_string* pDirPart,
		idk_string* pFileNamePart
		);

	/**
	 Add a path separator to the passed string, if necessary.
	 @param pPath [in, out]
	 */
	static void addPathSeparator(idk_string* pPath);

	/**
	 Primary path separator character on this platform.
	 */
	static char pathSeparator;

	/**
	 All acceptable path separator characters on this platform.
	 */
	static const char* pathSeparators;
};

#endif
