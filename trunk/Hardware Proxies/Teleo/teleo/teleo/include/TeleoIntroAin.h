/* Copyright 2003 MakingThings LLC. */

/*
 : set tabstop=2 shiftwidth=2
*/

/** \file TeleoAin.h
    TeleoAin API.
    
    Contains the structures, definitions and functions that 
    wrap devices on the Teleo Analog In Module to provide a 
    convenient programmatical interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_INTRO_AIN_H_
#define _TELEO_INTRO_AIN_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Analog In
//

/**
  TeleoMioAin reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TIntroAin;

/** Create a TIntroAin.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param ainDeviceIndex Ain device on the MultiIO (0 - 3)
    \param bound is the module specified already bound?
    \param ta a variable to hold the new device
    \return a reference to the object (or NULL if there was something wrong)
  */
TeleoError TIntroAin_Create( TeleoDeviceManager* tdm, cchar* address, uint8 ainDeviceIndex, bool* bound, TIntroAin** ta );

/** Gets the current bound state
    \param ta TIntroAin
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TIntroAin_boundGet( TIntroAin* ta, bool* bound );

/** Set the callback for bound updates
    \param ta TIntroAin
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroAin_boundCallbackSet( TIntroAin* ta, TeleoError (*boundUpdate)( TIntroAin* ta, bool bound ) );

/** Gets the current ain value.
    \param ta TIntroAin
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TIntroAin_valueGet( TIntroAin* ta, int16* value );

/** Set the callback for value updates
    \param ta TIntroAin
    \param valueUpdate valueUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroAin_valueCallbackSet( TIntroAin* ta, TeleoError (*valueUpdate)( TIntroAin* ta, int16 value ) );

/** Gets the Sample Period in ms
    \param ta TIntroAin reference returned from TIntroAin_create( )
    \param rate sample period pointer.
    \return TELEO_OK or appropriate error code
  */
TeleoError TIntroAin_samplePeriodGet( TIntroAin* ta, int16* period );

/** Sets the Sample Period in ms
    \param ta TIntroAin reference returned from TIntroAin_create( )
    \param rate sample period in ms.
    \return TELEO_OK or appropriate error code
  */
TeleoError TIntroAin_samplePeriodSet( TIntroAin* ta, int16 period );

/** Set the callback for sampleRate updates
    \param ta TIntroAin
    \param samplePeriodUpdate samplePeriodUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroAin_samplePeriodCallbackSet( TIntroAin* ta, TeleoError (*samplePeriodUpdate)( TIntroAin* ta, int16 samplePeriod ) );

/** Gets the resolution in number of bits
    \param ta TIntroAin reference returned from TIntroAin_create( )
    \param resolution resolution pointer.
    \return TELEO_OK or appropriate error code
  */
TeleoError TIntroAin_resolutionGet( TIntroAin* ta, int8* resolution );

/** Sets the resolution in number of bits
    \param ta TIntroAin reference returned from TIntroAin_create( )
    \param resolution resolution in bits
    \return TELEO_OK or appropriate error code
  */
TeleoError TIntroAin_resolutionSet( TIntroAin* ta, int8 resolution );

/** Set the callback for resolution updates
    \param ta TIntroAin
    \param resolutionUpdate resolutionUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroAin_resolutionCallbackSet( TIntroAin* ta, TeleoError (*resolutionUpdate)( TIntroAin* ta, int8 resolution ) );

#ifdef __cplusplus
}
#endif
  
#endif
