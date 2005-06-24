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

#ifndef _TELEO_AIN_H_
#define _TELEO_AIN_H_

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
} TAin;

/** Create a TAin.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param ainDeviceIndex Ain device on the MultiIO (0 - 3)
    \param bound is the module specified already bound?
    \param ta a variable to hold the new device
    \return a reference to the object (or NULL if there was something wrong)
  */
TeleoError TAin_Create( TeleoDeviceManager* tdm, cchar* address, uint8 ainDeviceIndex, bool* bound, TAin** ta );

/** Gets the current bound state
    \param ta TAin
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TAin_boundGet( TAin* ta, bool* bound );

/** Set the callback for bound updates
    \param ta TAin
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TAin_boundCallbackSet( TAin* ta, TeleoError (*boundUpdate)( TAin* ta, bool bound ) );

/** Gets the current ain value.
    \param ta TAin
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TAin_valueGet( TAin* ta, int16* value );

/** Set the callback for value updates
    \param ta TAin
    \param valueUpdate valueUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TAin_valueCallbackSet( TAin* ta, TeleoError (*valueUpdate)( TAin* ta, int16 value ) );

/** Gets the Sample Period in ms
    \param ta TAin reference returned from TAin_create( )
    \param rate sample period pointer.
    \return TELEO_OK or appropriate error code
  */
TeleoError TAin_samplePeriodGet( TAin* ta, int16* period );

/** Sets the Sample Period in ms
    \param ta TAin reference returned from TAin_create( )
    \param rate sample period in ms.
    \return TELEO_OK or appropriate error code
  */
TeleoError TAin_samplePeriodSet( TAin* ta, int16 period );

/** Set the callback for sampleRate updates
    \param ta TAin
    \param samplePeriodUpdate samplePeriodUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TAin_samplePeriodCallbackSet( TAin* ta, TeleoError (*samplePeriodUpdate)( TAin* ta, int16 samplePeriod ) );

/** Gets the resolution in number of bits
    \param ta TAin reference returned from TAin_create( )
    \param resolution resolution pointer.
    \return TELEO_OK or appropriate error code
  */
TeleoError TAin_resolutionGet( TAin* ta, int8* resolution );

/** Sets the resolution in number of bits
    \param ta TAin reference returned from TAin_create( )
    \param resolution resolution in bits
    \return TELEO_OK or appropriate error code
  */
TeleoError TAin_resolutionSet( TAin* ta, int8 resolution );

/** Set the callback for resolution updates
    \param ta TAin
    \param resolutionUpdate resolutionUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TAin_resolutionCallbackSet( TAin* ta, TeleoError (*resolutionUpdate)( TAin* ta, int8 resolution ) );

#ifdef __cplusplus
}
#endif
  
#endif
