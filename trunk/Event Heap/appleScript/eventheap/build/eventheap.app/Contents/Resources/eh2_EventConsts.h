/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_EventConsts.h,v 1.3 2003/06/02 08:02:04 tomoto Exp $ */

#ifndef _EH2_EVENTCONSTS_H_
#define _EH2_EVENTCONSTS_H_

/** @file
 Definition of eh2_EventConsts class.
 @internal This header belongs to the eh2i_ev component.
 */

#include <eh2_Base.h>

/**
 Constant values related to event.
 */
class EH2_DECL eh2_EventConsts {
public:
	/**
	 Value type of field value.
	 (Note that 'value type of field value' is different from 'data type of field'
	  which is represented by eh2_FieldType.)
	 */
	enum FieldValueType {
		/** Actual value */
		FVT_ACTUAL = 0,
		/** Formal value */
		FVT_FORMAL = 1,
		/** Virtual value */
		FVT_VIRTUAL = 2,
		/** Autoset value */
		FVT_AUTOSET = 3,
		/** Autoset value which can be overriden by users */
		FVT_AUTOSET_OVERRIDEABLE = 4
	};

	//
	// Standard Field Names
	//

	/** Field name of EventType */
	static const char* const FN_EVENTTYPE;
	/** Field name of TimeToLive */
	static const char* const FN_TIMETOLIVE;
	/** Field name of Target */
	static const char* const FN_TARGET;
	/** Field name of Soruce */
	static const char* const FN_SOURCE;
	/** Field name of SoruceApplication */
	static const char* const FN_SOURCEAPPLICATION;
	/** Field name of TargetApplication */
	static const char* const FN_TARGETAPPLICATION;
	/** Field name of SourceDevice */
	static const char* const FN_SOURCEDEVICE;
	/** Field name of TargetDevice */
	static const char* const FN_TARGETDEVICE;
	/** Field name of SourcePerson */
	static const char* const FN_SOURCEPERSON;
	/** Field name of TargetPerson */
	static const char* const FN_TARGETPERSON;
	/** Field name of SourceGroup */
	static const char* const FN_SOURCEGROUP;
	/** Field name of TargetGroup */
	static const char* const FN_TARGETGROUP;
	/** Field name of SessionId */
	static const char* const FN_SESSIONID;
	/** Field name of SequenceNum */
	static const char* const FN_SEQUENCENUM;
	/** Field name of EventHeapVersion */
	static const char* const FN_EVENTHEAPVERSION;

	//
	// Special Field Values
	//

	/** Field value representing INVALID_EVENT type. */
	static const char* const FV_INVALID_EVENT;
	/** Field value representing the default TTL. */
	static int FV_DEFAULT_TTL;
};

#endif
