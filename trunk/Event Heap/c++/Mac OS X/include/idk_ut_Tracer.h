/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: idk_ut_Tracer.h,v 1.4 2003/06/02 08:03:41 tomoto Exp $ */

#ifndef _IDK_UT_TRACER_H_
#define _IDK_UT_TRACER_H_

#include <idk_ut_Types.h>

/** @file
 The definition of idk_ut_Tracer class.
 */

/**
 Interface of tracer which handles events occured in an execution of a program.
 By implementing this interface and registering its instance with cs_setTracer(),
 you can gather various information about program execution for any purpose, e.g.
 logging or performance measuring.
 @todo The current interface provides only minumum event handlers.
 */
class IDK_DECL idk_ut_Tracer : public idk_ut_RealObject {
public:
	~idk_ut_Tracer();

	/**
	 Closes the tracer.
	 The implementation should gracefully finalize itself.
	 */
	virtual void closeTracer() = 0;

	/**
	 Flushes the tracer.
	 If the implementation has buffered events waiting for being processed,
	 it should process them immediately.
	 */
	virtual void flushTracer() = 0;

	/**
	 Called when a system call starts.
	 @param name Name of the system call.
	 */
	virtual void startSystemCall(const char* name) = 0;

	/**
	 Called when a system call ended.
	 @param result Status code (errno) of the system call.
	 */
	virtual void endSystemCall(int result) = 0;

	/**
	 Called when a system call ended.
	 @param result Return value of the system call.
	 */
	virtual void endSystemCall(void* result); // default implementation is provided

public:
	/**
	 Sets an instance of tracer as the current tracer.
	 The previous tracer will be discarded, if any.
	 @param tracerPtr Tracer to be used.
	 May pass NULL to simply cancel the previous tracer.
	 */
	static void cs_setTracer(const idk_ut_TracerPtr& tracerPtr);

	/** Calls closeTracer of the current tracer. */
	static void cs_close();

	/** Calls flushTracer of the current tracer. */
	static void cs_flush();

	/** Calls startSystemCall of the current tracer. */
	static void cs_startSystemCall(const char* name);

	/** Calls endSystemCall of the current tracer. */
	static void cs_endSystemCall(int result);

	/** Calls endSystemCall of the current tracer. */
	static void cs_endSystemCall(void* result);

};

IDK_UT_SHAREDPTR_DECL(idk_ut_Tracer);

#endif
