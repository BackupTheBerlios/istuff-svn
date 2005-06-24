/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2.h,v 1.5 2003/06/02 08:02:03 tomoto Exp $ */

#ifndef _EH2_H_
#define _EH2_H_

/** @file
 This file includes all definitions of the main package of ceheap2.
 @internal This header belongs to the eh2i_cl component.
 */

#include <eh2_Base.h>
#include <eh2_Consts.h>
#include <eh2_Event.h>
#include <eh2_EventCollection.h>
#include <eh2_EventHeap.h>
#include <eh2_Connection.h>
#include <eh2_EventHeapFactory.h>
#include <eh2_EventHeapException.h>
#include <eh2_EventHeapProtocolException.h>
#include <eh2_EventRegistration.h>
#include <eh2_ConnectErrorHandler.h>
#include <eh2_ErrorContext.h>
#include <eh2_EventToXML.h>
#include <eh2_Field.h>
#include <eh2_IFieldIterator.h>
#include <eh2_FieldType.h>
#include <eh2_FieldValue.h>
#include <eh2_Tracer.h>

/**
 Initializes the ceheap2.
 <p>You must call this function before you use any features of the ceheap2.
 The beginning of the main function is supposed to be a good place to
 call this.
 (If you want to use the ceheap2 in static initializers, you have to make
 sure this function is called at first before the main function.)
 <p>You can call this function more than once (the successing calls have
 no effect), but you need to call eh2_finalize() as the same times.

 @param appName Application name shared by Event Heap clients in this process.
 You can pass NULL to use the default value (i.e. the executable file name).
 @param deviceName Device name shared by Event Heap clients in this process.
 You can pass NULL to use the default value (i.e. the host name).
 */
void EH2_DECL eh2_init(const char* appName, const char* deviceName);

/**
 Finalizes the ceheap2.
 <p>You have to call this function after you finished using the ceheap2.
 This function must be called exactly as the same times as eh2_init()
 was called, and the last call will cause the actual finalization.
 <p>If your program exits without calling this function, it may crash
 because the static objects may be destructed in an arbitrary order.

 @todo automatic finalization to avoid crashing.
 */
void EH2_DECL eh2_finalize();

#endif
