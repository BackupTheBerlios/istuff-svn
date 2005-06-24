/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Base.h,v 1.14 2003/07/01 07:32:10 tomoto Exp $ */

#ifndef _EH2_BASE_H_
#define _EH2_BASE_H_

#include <idk_ut_Types.h>

/** @file
 Fundamental definitions for ceheap2.
 <p>Users do not have to include this file explicitly.
 <p>To ceheap2 developers: This file must be included at first among
 all ceheap header files.  To observe this constraint,
 all API header files should include this file at the beginning.
 Note that there is another rule for implementation headers.
 @internal This header belongs to the eh2i_ut component.
*/

/** @def EH2_DECL
 Declares a symbol which belongs to the ceheap2 library.
 */
#ifdef EH2_SOURCE
# define EH2_DECL IDK_DLLEXPORT
#else
# define EH2_DECL IDK_DLLIMPORT
#endif

// To embed the API version into each obj module.
// This might be helpful to check the consistensy between your already
// compiled application and the ceheap2 library installed on your system.
// Syntax:
//   EH2_API_VERSION:<major version>.<minor version>.<revision>
// Applications need not to be recompiled as long as the <major version>
// and the <minor version> is the same.
static const char* fs_eh2APIVersion = "EH2_API_VERSION:0.4.1";

#endif
