/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_io.h,v 1.6 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_IO_H_
#define _IDK_IO_H_

/** @file
 This file includes all definitions of the idk_io package.
 The idk_io package provides I/O functions.
 */

// Interfaces
#include <idk_io_IByteInStream.h>
#include <idk_io_IByteOutStream.h>

// Classes
#include <idk_io_RealByteInStream.h>
#include <idk_io_RealByteOutStream.h>
#include <idk_io_ByteArrayInStream.h>
#include <idk_io_ByteArrayOutStream.h>
#include <idk_io_ByteBufferInStream.h>
#include <idk_io_ByteBufferOutStream.h>
#include <idk_io_ByteLoggingInStream.h>
#include <idk_io_FileInStream.h>
#include <idk_io_FileOutStream.h>
#include <idk_io_LineReader.h>

// Utilities
#include <idk_io_FileUtil.h>

// Exceptions
#include <idk_io_IOException.h>
#include <idk_io_EOFException.h>
#include <idk_io_InterruptedIOException.h>
#include <idk_io_TimedoutIOException.h>
#include <idk_io_FileNotFoundException.h>

#endif
