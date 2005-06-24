/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Types.h,v 1.5 2003/06/02 08:02:06 tomoto Exp $ */

#ifndef _EH2_TYPES_H_
#define _EH2_TYPES_H_

/** @file
 Declaration of type names for ceheap2.
 */

#include <eh2_Base.h>

class eh2_EventHeap;
IDK_UT_SHAREDPTR_DECL(eh2_EventHeap);

class eh2_Connection;
IDK_UT_SHAREDPTR_DECL(eh2_Connection);

class eh2_EventHeapFactory;
IDK_UT_SHAREDPTR_DECL(eh2_EventHeapFactory);

class eh2_EventRegistration;
IDK_UT_SHAREDPTR_DECL(eh2_EventRegistration);

class eh2_ConnectErrorHandler;
IDK_UT_SHAREDPTR_DECL(eh2_ConnectErrorHandler);

class eh2_ConnectErrorHandlerFactory;
IDK_UT_SHAREDPTR_DECL(eh2_ConnectErrorHandlerFactory);

class eh2_ErrorContext;
IDK_UT_SHAREDPTR_DECL(eh2_ErrorContext);

class eh2_Event;
IDK_UT_SHAREDPTR_DECL(eh2_Event);

class eh2_EventCollection;
IDK_UT_SHAREDPTR_DECL(eh2_EventCollection);

class eh2_IFieldIterator;
IDK_UT_SHAREDPTR_DECL(eh2_IFieldIterator);

class eh2_IConstFieldIterator;
IDK_UT_SHAREDPTR_DECL(eh2_IConstFieldIterator);

class eh2_Field;
IDK_UT_SHAREDPTR_DECL(eh2_Field);

class eh2_FieldValue;
IDK_UT_SHAREDPTR_DECL(eh2_FieldValue);

class eh2_FieldType;
IDK_UT_SHAREDPTR_DECL(eh2_FieldType);

class eh2_Tracer;
IDK_UT_SHAREDPTR_DECL(eh2_Tracer);

class eh2_EventToXML;
IDK_UT_SHAREDPTR_DECL(eh2_EventToXML);

#endif
