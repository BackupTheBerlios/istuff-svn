/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_th_MonitorTimedoutException.h,v 1.3 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_TH_MONITORTIMEDOUTEXCEPTION_H_
#define _IDK_TH_MONITORTIMEDOUTEXCEPTION_H_

#include <idk_ut_Types.h>
#include <idk_ut_Exception.h>

/** @file
 Definition of idk_th_MonitorTimedoutException class.
 */

/**
 Thrown when the timeout was reached while waiting for a notification on a monitor.
 */
class IDK_DECL idk_th_MonitorTimedoutException : public idk_ut_Exception {
	IDK_UT_EXCEPTION_DECL(idk_th_MonitorTimedoutException, idk_ut_Exception);
};

#endif
