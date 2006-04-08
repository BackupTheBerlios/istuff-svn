/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_SerializationException.h,v 1.2 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_SERIALIZATIONEXCEPTION_H_
#define _EH2_SERIALIZATIONEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_Exception.h>

/** @file
 Definition of eh2_SerializationException.
 @internal belongs to eh2i_wb,
 */

/**
 Thrown to indicate errors during serialization or deserialization of
 the Event Heap wire bundle.
 */
class EH2_DECL eh2_SerializationException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(eh2_SerializationException, idk_ut_Exception);
};

#endif
