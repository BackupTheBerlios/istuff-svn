/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_Types.h,v 1.7 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TYPES_H_
#define _IDK_UT_TYPES_H_

/** @file
 Declaration of typenames of idk_ut packages.
 <p>This file provides declaration of typenames of all reference-semantics
 classes (i.e. classes held by pointer variables).  Necessary declaration
 of smartpointers are also provided.  You can use these typenames to
 declare pointer variables without including entire class definition.
 This file provides not only these typenames but also the complete definition
 of object type, shared-smartpointer type, and exception type for user's
 convenience.  Template types are not included.

 <p><i>To IDK developers: Follow the rule described below (types-header-rule)
 when writing IDK header files.
 <ul>
  <li>Each package must have its own types header
  (e.g. idk_th_Types.h for idk_th package),
  which must include other types headers of directly dependent packages
  at the beginning, then provides typename declarations.
  The types header is important in the sence that it decides the
  dependency between packages.
  Be careful not to make mutual dependencies.
  <li>Other header files must include types header of its belonging package
  at first.
 </ul>
 </i>
 */

// include the types headers of directly dependent packages here.
// but this file does it in an exceptional way since it is the
// bottom of the dependency.
#include <idk_ut_Base.h>
#include <idk_ut_RealObject.h>
#include <idk_ut_TProxyObject.h>
#include <idk_ut_TSharedPtr.h>
#include <idk_ut_Exception.h>

// declaration of typenames
class idk_ut_Tracer;
IDK_UT_SHAREDPTR_DECL(idk_ut_Tracer);

class idk_ut_ByteArray;
IDK_UT_SHAREDPTR_DECL(idk_ut_ByteArray);

class idk_ut_DateStruct;
// no smart pointer for idk_ut_DateStruct

class idk_ut_ILogger;
IDK_UT_SHAREDPTR_DECL(idk_ut_ILogger);

#endif
