/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_LogUtil.h,v 1.6 2003/08/05 06:46:45 tomoto Exp $ */

#ifndef _IDK_UT_LOGUTIL_H_
#define _IDK_UT_LOGUTIL_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_LogUtil class.
 */

/**
 This utility class provides functions to operate the log facility.
 */
class IDK_DECL idk_ut_LogUtil {
public:
	/**
	 Writes a message to the log facility.
	 The same with warn(WARN_CRITICAL, msg).
	 */
	static void log(const char* msg);

	/**
	 Warning level.
	 */
	enum WarningLevel {
		WARN_NONE = 0,
		WARN_CRITICAL,
		WARN_IMPORTANT,
		WARN_NOTICE,
		WARN_CHATTY,
		WARN_DEBUG,
		WARN_PACKET_DEBUG,
		WARN_VERBOSE_DEBUG,
		WARN_LEVEL_MAX
	};

	/**
	 Writes a warning message to the log facility.
	 */
	static void warn(WarningLevel level, const char* msg);

	/**
	 Sets the warning level.
	 WARN_CRITICAL in default.
	 */
	static void setWarningLevel(WarningLevel level);

	static WarningLevel getWarningLevel();

	/**
	 Sets the warning level by string.
	 <p>Example:</p>
	 <pre>
	 idk_ut_LogUtil::setWarningLevelByString(getenv("WARN_LEVEL"));
	 </pre>

	 @param level The string representation of the warning level,
	 which shoule be either "VERBOSE_DEBUG", "DEBUG", "CHATTY",
	 "NOTICE", "IMPORTANT", or "CRITICAL".
	 NULL can be accepted but no effect.

	 @throw idk_ut_BadParameterException Invalid string.
	 */
	static void setWarningLevelByString(const char* level);

	/**
	 Sets the logger to process log/warn requests.
	 The default logger writes messages to the stderr.
	 */
	static void setLogger(const idk_ut_ILoggerPtr& loggerPtr);

	static idk_ut_ILoggerPtr createStdioLogger(FILE* file);
#ifdef WINDOWS
	static idk_ut_ILoggerPtr createWinDebugLogger();
#endif
#ifdef UNIX
	/**
	 @todo not implemented yet
	 */
	static idk_ut_ILoggerPtr createSyslogLogger();
#endif
};

#endif
