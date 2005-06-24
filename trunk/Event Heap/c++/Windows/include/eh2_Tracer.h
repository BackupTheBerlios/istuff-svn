/* Copyright  (c) 2003 The Board of Trustees of The Leland Stanford Junior
 * University. All Rights Reserved.
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

/* $Id: eh2_Tracer.h,v 1.5 2003/06/02 08:02:05 tomoto Exp $ */

#ifndef _EH2_TRACER_H_
#define _EH2_TRACER_H_

#include <eh2_Base.h>
#include <eh2_Types.h>
#include <eh2_TracerConsts.h>
#include <idk_io_IByteOutStream.h>

/** @file
 Definition of eh2_Tracer class.
 @internal This header belongs to the eh2i_cl package.
 */

class eh2i_cl_Tracer; // impl

/**
 Tracer to gather information of execution of ceheap2.
 In the current implementation, only "logging" tracer is provided.
 <i>Hopefully we can provide additional variations of tracer in the future.
 (e.g. specialized tracer for performance measurement)</i>
 */
class EH2_DECL eh2_Tracer
: public idk_ut_TProxyObject<eh2i_cl_Tracer>,
  public eh2_TracerConsts
{
private:
	friend class eh2i_cl_Tracer;
	eh2_Tracer(eh2i_cl_Tracer* impl);

public:
	~eh2_Tracer();

	/**
	 Sets a tracer.
	 */
	static void cs_setTracer(const eh2_TracerPtr& tracerPtr);

	/**
	 Closes the tracer.
	 */
	static void cs_closeTracer();

	/**
	 Creates the default "logging" tracer.
	 @param osPtr Output stream to write the log.
	 The ownership is taken over by the tracer object.
	 @param modeMask Logical-or'ed values of eh2_TracerConsts::TraceModeMask
	 to specify what kind of information is logged.
	 @param linesBufSize Number of log items buffered.
	 The default value is 100.
	 If you want to use the log to analyze a system crash,
	 you should set this to 1 to keep the log always updated.
	 */
	static eh2_TracerPtr cs_create(
		const idk_io_IByteOutStreamPtr& osPtr, 
		int modeMask = TMM_ALL,
		int linesBufSize = 1
		);

};

#endif
