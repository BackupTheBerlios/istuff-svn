/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_InterruptedException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_INTERRUPTEDEXCEPTION_H_
#define _IDK_TH_INTERRUPTEDEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_Exception.h>

/** @file
 Definition of idk_th_InterruptedException class.
 */

/**
 Should be thrown when a thread was interrupted during blocking operation
 like idk_th_Thread::join().
 @todo The 'real' mechanism to interrupt threads is not implemented yet,
 so this exception is not used as it's original meaning for now.
 */
class IDK_DECL idk_th_InterruptedException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(idk_th_InterruptedException, idk_ut_Exception);
};

#endif
