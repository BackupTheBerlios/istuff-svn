/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk.h,v 1.5 2003/06/02 08:03:39 tomoto Exp $ */

#ifndef _IDK_H_
#define _IDK_H_

#include <idk_ut_Base.h>

/** @file
 This file includes all definitions of the root package of the IDK
 and provides automatic initialization capability.
 <p>This package includes initialization and finalization functions.
 See idk_ut.h, idk_th.h, idk_io.h, idk_ne.h, idk_xm.h for other functions.
 <p>Also, this file provides automatic initialization capability.
 By including this file in your source code, the IDK library should be
 initialized and finalized automatically.
 It is enough to include this file at least one of your source code
 unless you call the IDK in any static initializers.
 Otherwise, you should include this file in each source file
 which defines such static variables.
 You can disable this automatic initialization by defining preprocessor
 macro IDK_UT_NOAUTOINIT.
 */

/**
 Initializes the IDK.
 <p>You must call this function before you use any features of the IDK.
 The beginning of the main function is supposed to be a good place to
 call this.
 (If you want to use the IDK in static initializers, you have to make
 sure this function is called at first before the main function.)
 <p>You can call this function more than once (the successing calls
 have no effect), but you need to call idk_finalize() as the same times.
 Do not call this under multiple threads simultaneously.

 @deprecated Use automatic initialization instead.
 */
void IDK_DECL idk_init();

/**
 Finalizes the IDK.
 <p>You have to call this function after you finished using the IDK.
 This function must be called exactly as the same times as idk_init()
 was called, and the last call will cause the actual finalization.
 Do not call this under multiple threads simultaneously.

 @deprecated Use automatic initialization instead.
 */
void IDK_DECL idk_finalize();

class IDK_DECL idk_Initializer {
public:
	~idk_Initializer();
	idk_Initializer();
};

#ifndef IDK_UT_NOAUTOINIT
static idk_Initializer fs_initializer;
#endif

#endif
