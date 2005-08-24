/* Copyright 2003 MakingThings LLC. */

/** \file TeleoIntroDin.h
    Device Wrapper API.
    Contains the structures, definitions and functions for a 
    set of functions that wrap TeleoDevice entities providing
    a very Teleo Module-like interface.
    
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_INTRO_DIN_H_
#define _TELEO_INTRO_DIN_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Intro IO Digital In
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
} TIntroDin;

/** Create a TIntroDin.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param dinDeviceIndex Din device on the MultiIO (0 - 3)
    \param bound is the module specified already bound?
    \param tmdin a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TIntroDin_Create( TeleoDeviceManager* tdm, cchar* address, uint8 dinDeviceIndex, bool* bound, TIntroDin** tmdin );

/** Gets the current bound state
    \param tmdin TIntroDin reference returned from TIntroDin_create( )
    \param bound pointer to the bound variable
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroDin_boundGet( TIntroDin* tmdin, bool* bound );

/** Set the callback for bound updates
    \param tmdin TIntroDin
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroDin_boundCallbackSet( TIntroDin* tmdin, TeleoError (*boundUpdate)( TIntroDin* tmdin, bool bound ) );

/** Gets the current ain value.
    \param tmdin TIntroDin reference returned from TIntroDin_create( )
    \param value pointer to the value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroDin_valueGet( TIntroDin* tmdin, bool* value );

/** Set the callback for value updates
    \param tmdin TIntroDin
    \param valueUpdate valueUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroDin_valueCallbackSet( TIntroDin* tmdin, TeleoError (*valueUpdate)( TIntroDin* tmdin, bool value ) );

/** Gets the current invert value.
    \param tmdin TIntroDin reference returned from TIntroDin_create( )
    \param invert pointer to the invert value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroDin_invertGet( TIntroDin* tmdin, bool* invert );

/** Sets the current invert value.
    \param tmdin TIntroDin reference returned from TIntroDin_create( )
    \param invert the new invert value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroDin_invertSet( TIntroDin* tmdin, bool invert );

/** Set the callback for invert updates
    \param tmdin TIntroDin
    \param invertUpdate invertUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroDin_invertCallbackSet( TIntroDin* tmdin, TeleoError (*invertUpdate)( TIntroDin* tmdin, bool invert ) );

/** Gets the Sample Period in ms
    \param tmdin TIntroDin reference returned from TIntroDin_create( )
    \param samplePeriod sample rate in ms.
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroDin_samplePeriodGet( TIntroDin* tmdin, int16* samplePeriod );

/** Sets the current sample rate value
    \param tmdin TIntroDin reference returned from TIntroDin_create( )
    \param samplePeriod the new sample rate
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroDin_samplePeriodSet( TIntroDin* tmdin, int16 samplePeriod );

/** Set the callback for samplePeriod updates
    \param tmdin TIntroDin
    \param samplePeriodUpdate samplePeriodUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroDin_samplePeriodCallbackSet( TIntroDin* tmdin, TeleoError (*samplePeriodUpdate)( TIntroDin* tmdin, int16 samplePeriod ) );


#ifdef __cplusplus
}
#endif
  
#endif
