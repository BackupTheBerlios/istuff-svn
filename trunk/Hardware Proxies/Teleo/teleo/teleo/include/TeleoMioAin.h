/* Copyright 2003 MakingThings LLC. */

/*
 : set tabstop=2 shiftwidth=2
*/

/** \file TeleoMioAin.h
    TeleoMioAin API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo MultiIO to provide a convenient programmatical
    interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_MIO_AIN_H_
#define _TELEO_MIO_AIN_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Multi IO Analog In
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
} TMioAin;

/** Create a TMioAin.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param ainDeviceIndex Ain device on the MultiIO (0 - 3)
    \param bound is the module specified already bound?
    \param tma a variable to hold the new device
    \return a reference to the object (or NULL if there was something wrong)
  */
TeleoError TMioAin_Create( TeleoDeviceManager* tdm, cchar* address, uint8 ainDeviceIndex, bool* bound, TMioAin** tma );

/** Gets the current bound state
    \param tma TMioAin
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_boundGet( TMioAin* tma, bool* bound );

/** Set the callback for bound updates
    \param tma TMioAin
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_boundCallbackSet( TMioAin* tma, TeleoError (*boundUpdate)( TMioAin* tma, bool bound ) );

/** Gets the current ain value.
    \param tma TMioAin
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_valueGet( TMioAin* tma, float* value );

/** Set the callback for value updates
    \param tma TMioAin
    \param valueUpdate valueUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_valueCallbackSet( TMioAin* tma, TeleoError (*valueUpdate)( TMioAin* tma, float value ) );

/** Gets the current in range value.
    \param tma TMioAin
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_inRangeGet( TMioAin* tma, bool* value );

/** Set the callback for value updates
    \param tma TMioAin
    \param inRangeUpdate inRangeUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_inRangeCallbackSet( TMioAin* tma, TeleoError (*inRangeUpdate)( TMioAin* tma, bool inRange ) );

/** Gets the Minimum value on the specified TMioAin.
    \param tma TMioAin
    \param min minimum value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_minGet( TMioAin* tma, float* min );

/** Sets the Minimum value on the specified TMioAin.
    \param tma TMioAin
    \param min new minimum value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_minSet( TMioAin* tma, float min );

/** Set the callback for min updates
    \param tma TMioAin
    \param minUpdate minUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_minCallbackSet( TMioAin* tma, TeleoError (*minUpdate)( TMioAin* tma, float min ) );

/** Gets the Max value on the specified TMioAin.
    \param tma TMioAin
    \param max maximum value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_maxGet( TMioAin* tma, float* max );

/** Sets the Maximum value on the specified TMioAin.
    \param tma TMioAin
    \param max new maximum value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_maxSet( TMioAin* tma, float max );

/** Set the callback for max updates
    \param tma TMioAin
    \param maxUpdate maxUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_maxCallbackSet( TMioAin* tma, TeleoError (*maxUpdate)( TMioAin* tma, float max ) );

/** Gets the Range Minimum value on the specified TMioAin.
    \param tma TMioAin
    \param rangeMin range minimum value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_rangeMinGet( TMioAin* tma, float* rangeMin );

/** Sets the Range Minimum value on the specified TMioAin.
    \param tma TMioAin reference returned from TMioAin_create( )
    \param rangeMin new range minimum value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_rangeMinSet( TMioAin* tma, float rangeMin );

/** Set the callback for rangeMin updates
    \param tma TMioAin
    \param rangeMinUpdate rangeMinUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_rangeMinCallbackSet( TMioAin* tma, TeleoError (*rangeMinUpdate)( TMioAin* tma, float rangeMin ) );

/** Gets the Range Maximum value on the specified TMioAin.
    \param tma TMioAin reference returned from TMioAin_create( )
    \param rangeMax range maximum value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_rangeMaxGet( TMioAin* tma, float* rangeMax );

/** Sets the Range Maximum value on the specified TMioAin.
    \param tma TMioAin reference returned from TMioAin_create( )
    \param rangeMax new range maximum value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_rangeMaxSet( TMioAin* tma, float rangeMax );

/** Set the callback for rangeMax updates
    \param tma TMioAin
    \param rangeMaxUpdate rangeMaxUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_rangeMaxCallbackSet( TMioAin* tma, TeleoError (*rangeMaxUpdate)( TMioAin* tma, float rangeMax ) );

/** Gets the Sample Rate in ms
    \param tma TMioAin reference returned from TMioAin_create( )
    \param rate sample rate pointer.
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_sampleRateGet( TMioAin* tma, int16* rate );

/** Sets the Sample Rate in ms
    \param tma TMioAin reference returned from TMioAin_create( )
    \param rate sample rate in ms.
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_sampleRateSet( TMioAin* tma, int16 rate );

/** Set the callback for sampleRate updates
    \param tma TMioAin
    \param sampleRateUpdate sampleRateUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_sampleRateCallbackSet( TMioAin* tma, TeleoError (*sampleRateUpdate)( TMioAin* tma, int16 sampleRate ) );

/** Gets the resolution in number of bits
    \param tma TMioAin reference returned from TMioAin_create( )
    \param resolution resolution pointer.
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_resolutionGet( TMioAin* tma, int8* resolution );

/** Sets the resolution in number of bits
    \param tma TMioAin reference returned from TMioAin_create( )
    \param resolution resolution in bits
    \return TELEO_OK or appropriate error code
  */
TeleoError TMioAin_resolutionSet( TMioAin* tma, int8 resolution );

/** Set the callback for resolution updates
    \param tma TMioAin
    \param resolutionUpdate resolutionUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioAin_resolutionCallbackSet( TMioAin* tma, TeleoError (*resolutionUpdate)( TMioAin* tma, int8 resolution ) );

#ifdef __cplusplus
}
#endif
  
#endif
