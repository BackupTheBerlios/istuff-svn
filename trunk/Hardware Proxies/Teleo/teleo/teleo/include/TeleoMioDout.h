/* Copyright 2003 MakingThings LLC. */

/** \file TeleoMioDout.h
    Device Wrapper API.
    Contains the structures, definitions and functions for a 
    set of functions that wrap TeleoDevice entities providing
    a very Teleo Module-like interface.
    
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_MIO_DOUT_H_
#define _TELEO_MIO_DOUT_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Multi IO Digital Out
//

/**
  TeleoMioDout reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TMioDout;

/** Create a TMioDout.
    \param tdm TeleoDeviceManager
    \param address module address (or 0 if don't care)
    \param pwmDeviceIndex Dout device on the MultiIO (0 - 1)
    \param bound is the module specified already bound?
    \param tmdout a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TMioDout_Create( TeleoDeviceManager* tdm, 
                   		     cchar* address, 
                   			   uint8 pwmDeviceIndex, 
                   			   bool* bound,
                           TMioDout** tmdout  );

/** Gets the current bound state
    \param tmdout TMioDout
    \param bound pointer to the bound variable
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDout_boundGet( TMioDout* tmdout, bool* bound );

/** Set the callback for bound updates
    \param tmdout TMioDout
    \param boundUpdate bound callback function
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioDout_boundCallbackSet( TMioDout* tmdout, TeleoError (*boundUpdate)(
			TMioDout* tmdout, bool bound ) );


/** Gets the value on the specified TMioDout.
    \param tmdout TMioDout
    \param value value pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDout_valueGet( TMioDout* tmdout, bool* value );

/** Sets the value on the specified TMioDout.
    \param tmdout TMioDout reference returned from TMioDout_create( )
    \param value new value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDout_valueSet( TMioDout* tmdout, bool value );

/** Set the callback for value updates
    \param tmdout TMioDout
    \param valueUpdate value Update callback function
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioDout_valueCallbackSet( TMioDout* tmdout, TeleoError (*valueUpdate)( TMioDout* tmdout, bool value ) );

#ifdef __cplusplus
}
#endif
  
#endif
