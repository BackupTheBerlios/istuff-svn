/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_TracerConsts.h,v 1.3 2003/06/02 08:02:06 tomoto Exp $ */

#ifndef _EH2_TRACERCONSTS_H_
#define _EH2_TRACERCONSTS_H_

#include <eh2_Base.h>
#include <eh2_Types.h>

/** @file
 Definition of eh2_TracerConsts class.
 @internal This header belongs to the eh2i_cl package.
 */

/**
 Constant values used by eh2_Tracer.
 */
class EH2_DECL eh2_TracerConsts {
public:
	/**
	 Flags to specify what kind of information is logged.
	 */
	enum TraceModeMask {
		/** All recognized information. */
		TMM_ALL = 0xffff,
		/** API call. */
		TMM_API = 0x0001,
		/** Errors. */
		TMM_ERROR = 0x0002,
		/** Other important checkpoints */
		TMM_OTHER = 0x0004,
		/** Systemcalls */
		TMM_SYSTEMCALL = 0x0008
	};
};

#endif
