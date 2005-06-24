/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Consts.h,v 1.3 2003/06/02 08:02:03 tomoto Exp $ */

#ifndef _EH2_CONSTS_H_
#define _EH2_CONSTS_H_

#include <eh2_Base.h>
#include <eh2_EventConsts.h>
#include <eh2_TracerConsts.h>

/** @file
 Definition of eh2_Consts class.
 @internal This header belongs to the eh2i_cl component.
 */

/**
 This class provides all constant values defined by ceheap2.
 See eh2_EventConsts and eh2_TracerConsts for the actual definitions.
 By inheriting this, you can omit prefix <code>eh2_Consts::</code>
 when you use any of these constants in your class.
 @see eh2_EventConsts, eh2_TracerConsts
 */
class EH2_DECL eh2_Consts
: public eh2_EventConsts, public eh2_TracerConsts
{
};

#endif
