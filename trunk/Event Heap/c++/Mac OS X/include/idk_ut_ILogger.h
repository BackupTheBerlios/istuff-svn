/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_ILogger.h,v 1.2 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_ILOGGER_H_
#define _IDK_UT_ILOGGER_H_

#include <idk_ut_Types.h>
#include <idk_ut_LogUtil.h>

/** @file
 The definition of idk_ut_Logger class.
 */

/**
 This class defines the interface to the log facility.
 <p>Example:
 <pre>
 class MyLogger : public idk_ut_ILogger, public idk_ut_RealObject {
   IDK_UT_REFCOUNTED_IMPL();
 public:
   virtual void log(
     const char* msg, idk_ut_LogUtil::WarningLevel level
     )
   {
     fputs(msg, stdout);
   }
 };
 </pre>
 <p>Logger has responsibility to mutex shared resources if necessary.
 */
class IDK_DECL idk_ut_ILogger {
	IDK_UT_REFCOUNTED_DECL();

public:
	virtual ~idk_ut_ILogger() {}

	/**
	 Logs message.
	 Design this method as safe as possible.
	 Do not raise any exceptions or use assertion.
	 @param msg Message to be logged.  Never be NULL.
	 @param level Warning level specified by the application.
	 The logger need not check the level with the current warning level
	 setting.  This is only an information.
	 */
	virtual void log(
		const char* msg,
		idk_ut_LogUtil::WarningLevel level
		) = 0;
};

#endif
