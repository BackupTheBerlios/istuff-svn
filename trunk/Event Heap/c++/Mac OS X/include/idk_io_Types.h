/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io_Types.h,v 1.4 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_IO_TYPES_H_
#define _IDK_IO_TYPES_H_

/** @file
 Declaration of typenames of the idk_io package.
 */

// directly dependent packages
#include <idk_ut_Types.h>

// declaration of typenames
class idk_io_IByteInStream;
IDK_UT_SHAREDPTR_DECL(idk_io_IByteInStream);

class idk_io_IByteOutStream;
IDK_UT_SHAREDPTR_DECL(idk_io_IByteOutStream);

class idk_io_ByteInStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteInStream);

class idk_io_ByteOutStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteOutStream);

class idk_io_FileInStream;
IDK_UT_SHAREDPTR_DECL(idk_io_FileInStream);

class idk_io_FileOutStream;
IDK_UT_SHAREDPTR_DECL(idk_io_FileOutStream);

class idk_io_ByteBufferInStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteBufferInStream);

class idk_io_ByteBufferOutStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteBufferOutStream);

class idk_io_ByteArrayInStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteArrayInStream);

class idk_io_ByteArrayOutStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteArrayOutStream);

class idk_io_ByteLoggingInStream;
IDK_UT_SHAREDPTR_DECL(idk_io_ByteLoggingInStream);

#endif
