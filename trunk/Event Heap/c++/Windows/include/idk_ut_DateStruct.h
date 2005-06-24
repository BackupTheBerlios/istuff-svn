/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_DateStruct.h,v 1.2 2003/06/02 08:03:40 tomoto Exp $ */

#ifndef _IDK_UT_DATESTRUCT_H_
#define _IDK_UT_DATESTRUCT_H_

#include <idk_ut_Types.h>

class IDK_DECL idk_ut_DateStruct {
public:
	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;
	int m_milliSecond;

	~idk_ut_DateStruct();
	idk_ut_DateStruct();
	idk_ut_DateStruct(const idk_ut_DateStruct& other);
	idk_ut_DateStruct& operator=(const idk_ut_DateStruct& other);
	void setDateTime(int y, int mo, int d, int h, int min, int s, int ms = 0);
	void setDatePart(int y, int m, int d);
	void setTimePart(int h, int m, int s, int ms = 0);
};

#endif
