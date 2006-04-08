/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventHeapException.h,v 1.5 2003/06/02 08:02:04 tomoto Exp $ */

#ifndef _EH2_EVENTHEAPEXCEPTION_H_
#define _EH2_EVENTHEAPEXCEPTION_H_

/** @file
 Definition of eh2_EventHeapException class.
 @internal This header belongs to the eh2i_ev component.
 */

#include <eh2_Base.h>
#include <idk_ut_Exception.h>

/**
 Thrown when an EventHeap-related error occured.
 */
class EH2_DECL eh2_EventHeapException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(eh2_EventHeapException, idk_ut_Exception);
};

#endif
