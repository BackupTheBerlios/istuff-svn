/* Copyright 2003 MakingThings LLC. */

/** \file TeleoMioDin.h
    Device Wrapper API.
    Contains the structures, definitions and functions for a 
    set of functions that wrap TeleoDevice entities providing
    a very Teleo Module-like interface.
    
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_MIO_DIN_H_
#define _TELEO_MIO_DIN_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Multi IO Digital In
//

/**
  TeleoMioDin reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TMioDin;

/** Create a TMioDin.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param dinDeviceIndex Din device on the MultiIO (0 - 3)
    \param bound is the module specified already bound?
    \param tmdin a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TMioDin_Create( TeleoDeviceManager* tdm, cchar* address, uint8 dinDeviceIndex, bool* bound, TMioDin** tmdin );

/** Gets the current bound state
    \param tmdin TMioDin reference returned from TMioDin_create( )
    \param bound pointer to the bound variable
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDin_boundGet( TMioDin* tmdin, bool* bound );

/** Set the callback for bound updates
    \param tmdin TMioDin
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioDin_boundCallbackSet( TMioDin* tmdin, TeleoError (*boundUpdate)( TMioDin* tmdin, bool bound ) );

/** Gets the current ain value.
    \param tmdin TMioDin reference returned from TMioDin_create( )
    \param value pointer to the value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDin_valueGet( TMioDin* tmdin, bool* value );

/** Set the callback for value updates
    \param tmdin TMioDin
    \param valueUpdate valueUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioDin_valueCallbackSet( TMioDin* tmdin, TeleoError (*valueUpdate)( TMioDin* tmdin, bool value ) );

/** Gets the current invert value.
    \param tmdin TMioDin reference returned from TMioDin_create( )
    \param invert pointer to the invert value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDin_invertGet( TMioDin* tmdin, bool* invert );

/** Sets the current invert value.
    \param tmdin TMioDin reference returned from TMioDin_create( )
    \param invert the new invert value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDin_invertSet( TMioDin* tmdin, bool invert );

/** Set the callback for invert updates
    \param tmdin TMioDin
    \param invertUpdate invertUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioDin_invertCallbackSet( TMioDin* tmdin, TeleoError (*invertUpdate)( TMioDin* tmdin, bool invert ) );

/** Gets the Sample Rate in ms
    \param tmdin TMioDin reference returned from TMioDin_create( )
    \param sampleRate sample rate in ms.
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDin_sampleRateGet( TMioDin* tmdin, int16* sampleRate );

/** Sets the current sample rate value
    \param tmdin TMioDin reference returned from TMioDin_create( )
    \param sampleRate the new sample rate
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioDin_sampleRateSet( TMioDin* tmdin, int16 sampleRate );

/** Set the callback for sampleRate updates
    \param tmdin TMioDin
    \param sampleRateUpdate sampleRateUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioDin_sampleRateCallbackSet( TMioDin* tmdin, TeleoError (*sampleRateUpdate)( TMioDin* tmdin, int16 sampleRate ) );


#ifdef __cplusplus
}
#endif
  
#endif
