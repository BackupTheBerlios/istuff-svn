/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventHeapProtocolException.h,v 1.2 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_EVENTHEAPPROTOCOLEXCEPTION_H_
#define _EH2_EVENTHEAPPROTOCOLEXCEPTION_H_

/** @file
 Definition of eh2_EventHeapProtocolException class.
 @internal This header belongs to the eh2i_cl component.
 */

#include <eh2_Base.h>
#include <eh2_EventHeapException.h>

/**
 Thrown when an protocol error occured.
 In the current implementation, this exception is thrown when
 protocol version mismatch was detected during connecting to the server.
 */
class EH2_DECL eh2_EventHeapProtocolException : public eh2_EventHeapException {
	IDK_UT_EXCEPTION_DECL(eh2_EventHeapProtocolException, eh2_EventHeapException);
};

#endif
