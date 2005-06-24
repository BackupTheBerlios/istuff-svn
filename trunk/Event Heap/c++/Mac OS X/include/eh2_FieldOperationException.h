/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_FieldOperationException.h,v 1.2 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_FIELDOPERATIONEXCEPTION_H_
#define _EH2_FIELDOPERATIONEXCEPTION_H_

/** @file
 Definition of eh2_FieldOperationException class.
 @internal This header belongs to the eh2i_ev component.
 */

#include <eh2_Base.h>
#include <eh2_EventHeapException.h>

/**
 Thrown when a field operation failed because type mismatch occured,
 there's no such field, etc.
 */
class EH2_DECL eh2_FieldOperationException : public eh2_EventHeapException {
	IDK_UT_EXCEPTION_DECL(eh2_FieldOperationException, eh2_EventHeapException);
};

#endif
