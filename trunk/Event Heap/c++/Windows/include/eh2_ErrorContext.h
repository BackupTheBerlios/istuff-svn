/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_ErrorContext.h,v 1.5 2003/06/02 08:02:04 tomoto Exp $ */

#ifndef _EH2_ERRORCONTEXT_H_
#define _EH2_ERRORCONTEXT_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <idk_ne_SocketAddress.h>

/** @file
 Definition of eh2_ErrorContext class.
 @internal This header belongs to the eh2i_cl component.
 */

class eh2i_cl_ErrorContext; // impl

/**
 Provides the context information for eh2_ConnectErrorHandler.

 <p>The handler can know about the context (e.g. the current thread is
 background or not) by querying to this object.
 */
class EH2_DECL eh2_ErrorContext :
public idk_ut_TProxyObject<eh2i_cl_ErrorContext>
{
private:
	friend class eh2i_cl_ErrorContext;
	eh2_ErrorContext(eh2i_cl_ErrorContext* impl);

public:
	~eh2_ErrorContext();

	/**
	 Returns if the current thread is executed in background.
	 @return Non-zero if the current thread is in background
	 (i.e. receiver or sender thread).
	 Zero if otherwise (i.e. the caller's thread).
	 */
	int isBackgroundThread() const;

	/**
	 Returns the server's address of the connection.

	 <i>This method would be useful when an instance of the handler
	 is shared among two or more connections.
	 By the way, why not eh2_Connection object?  Because the handler 
	 may be called during the connection object is under constuction.
	 </i>
	 */
	const idk_ne_SocketAddress* getAddress() const;
};

#endif
