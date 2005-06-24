/* Copyright 2003 MakingThings LLC. */

/*
 : set tabstop=2 shiftwidth=2
*/

/** \file TeleoStepperLow.h
    TeleoStepper API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo Stepper to provide a convenient programmatical
    interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.

: set tabstop=2 shiftwidth=2
 */

#ifndef _TELEO_STEPPER_LOW_H_
#define _TELEO_STEPPER_LOW_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Stepper Controller
//

/**
  TeleoStepper reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TStepLow;

TeleoError TStepLow_Create( TeleoDeviceManager* tdm, 
		                        cchar* address, 
			                      bool* bound,
                            TStepLow** tStepLow );

/** Gets the current bound state
    \param tStepLow Teleo Stepper Device
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_boundGet( TStepLow* tStepLow, bool* bound );

/** Set the callback for bound updates
    \param tStepLow Teleo Stepper Device
		\param boundUpdate bound callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_boundCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*boundUpdate)( TStepLow* tStepLow, bool bound ) );

/** Gets the current direction value.
    \param tStepLow Teleo Stepper Device
    \param direction pointer to the direction 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepDirectionGet( TStepLow* tStepLow, bool* direction );

/** Sets the direction value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param direction new direction value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepDirectionSet( TStepLow* tStepLow, bool direction );

/** Set the callback for direction updates
    \param tStepLow Teleo Stepper Device
    \param directionUpdate direction update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_stepDirectionCallbackSet( TStepLow* tStepLow, TeleoError (*stepDirectionUpdate)( TStepLow* tStepLow, bool stepDirection ) );

/** Gets the current rate value.
    \param tStepLow Teleo Stepper Device
    \param rate pointer to the rate 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepRateGet( TStepLow* tStepLow, float* stepRate );

/** Sets the rate value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param rate new rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepRateSet( TStepLow* tStepLow, float stepRate );

/** Set the callback for rate updates
    \param tStepLow Teleo Stepper Device
    \param rateUpdate rate update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_stepRateCallbackSet( TStepLow* tStepLow, TeleoError (*rateUpdate)( TStepLow* tStepLow, float rate ) );

/** Gets the current On value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param on pointer to the on value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_enableGet( TStepLow* tStepLow, bool* enable );

/** Sets the On value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param on new on value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_enableSet( TStepLow* tStepLow, bool enable );

/** Set the callback for on updates
    \param tStepLow Teleo Stepper Device
    \param onUpdate on update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_enableCallbackSet( TStepLow* tStepLow, TeleoError (*enableUpdate)( TStepLow* tStepLow, bool enable ) );

/** Gets the current rate value.
    \param tStepLow Teleo Stepper Device
    \param rate pointer to the rate 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepSizeGet( TStepLow* tStepLow, int8* stepSize );

/** Sets the rate value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param rate new rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepSizeSet( TStepLow* tStepLow, int8 stepSize );

/** Set the callback for rate updates
    \param tStepLow Teleo Stepper Device
    \param rateUpdate rate update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_stepSizeCallbackSet( TStepLow* tStepLow, TeleoError (*stepSizeUpdate)( TStepLow* tStepLow, int8 stepSize ) );

/** Gets the current position value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param position pointer to the position 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepPositionCurrentGet( TStepLow* tStepLow, long* stepPositionCurrent );

/** Set the callback for position updates
    \param tStepLow Teleo Stepper Device
		\param positionUpdate positioin callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_stepPositionCurrentCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*stepPositionCurrentUpdate)( TStepLow* tStepLow, long stepPositionCurrent ) );

/** Gets the current power value.
    \param tStepLow Teleo Stepper Device
    \param power pointer to the power 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_motorCurrentMaxGet( TStepLow* tStepLow, int16* motorCurrentMax );

/** Sets the power value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param power new power value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_motorCurrentMaxSet( TStepLow* tStepLow, int16 motorCurrentMax );

/** Set the callback for power updates
    \param tStepLow Teleo Stepper Device
    \param powerUpdate power callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_motorCurrentMaxCallbackSet( TStepLow* tStepLow, TeleoError (*motorCurrentMaxUpdate)( TStepLow* tStepLow, int16 power ) );

/** Gets the Position Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param posSampleRate pointer to position sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepPositionSamplePeriodGet( TStepLow* tStepLow, int16* stepPositionSamplePeriod );

/** Sets the Position Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param posSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepPositionSamplePeriodSet( TStepLow* tStepLow, int16 stepPositionSamplePeriod );

/** Set the callback for position sample rateupdates
    \param tStepLow Teleo Stepper Device
		\param posSampleRateUpdate position sample rate update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_stepPositionSamplePeriodCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*stepPositionSamplePeriodUpdate)( TStepLow* tStepLow, int16 stepPositionSamplePeriod ) );

/** Gets the limitsOn value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param limitsOn limitsOn value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_limitsOnGet( TStepLow* tStepLow, bool* limitsOn );

/** Sets the limitsOn value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param limitsOn new limitsOn value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_limitsOnSet( TStepLow* tStepLow, bool limitsOn );

/** Set the callback for limits on updates
    \param tStepLow Teleo Stepper Device
		\param limitsOnUpdate limit on callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_limitsOnCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*limitsOnUpdate)( TStepLow* tStepLow, bool limitsOn ) );

/** Gets the position target
    \param tStepLow Teleo Stepper Device
    \param positionTarget pointer to position target value
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_positionTargetGet( TStepLow* tStepLow, int16* positionTarget );

/** Sets the Position Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param positionTarget new current sample rate value
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_positionTargetSet( TStepLow* tStepLow, int16 positionTarget );

/** Set the callback for positionTargetle rateupdates
    \param tStepLow Teleo Stepper Device
		\param positionTargetUpdate positionTarget update callback function
		\return TELEO_OK or appropriate error code
 */
//TeleoError TStepLow_positionTargetCallbackSet( 
//		         TStepLow* tStepLow, 
//		         TeleoError (*positionTargetUpdate)( TStepLow* tStepLow, int16 positionTarget ) );

/** Gets the current maximum rate value.
    \param tStepLow Teleo Stepper Device
    \param rateMax pointer to the maximum rate 
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_rateMaxGet( TStepLow* tStepLow, int16* rateMax );

/** Sets the maximum rate value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param rateMax new maximum rate value
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_rateMaxSet( TStepLow* tStepLow, int16 rateMax );

/** Set the callback for rateMax updates
    \param tStepLow Teleo Stepper Device
    \param rateMaxUpdate rateMax update callback function 
    \return TELEO_OK or appropriate error code
 */
//TeleoError TStepLow_rateMaxCallbackSet( TStepLow* tStepLow, TeleoError (*rateMaxUpdate)( TStepLow* tStepLow, int16 rateMax ) );

/** Gets the current acceleration value.
    \param tStepLow Teleo Stepper Device
    \param acceleration pointer to the acceleration 
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_accelerationGet( TStepLow* tStepLow, int16* acceleration );

/** Sets the acceleration value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param acceleration new acceleration value
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_accelerationSet( TStepLow* tStepLow, int16 acceleration );

/** Set the callback for acceleration updates
    \param tStepLow Teleo Stepper Device
    \param accelerationUpdate acceleration callback function 
    \return TELEO_OK or appropriate error code
 */
//TeleoError TStepLow_accelerationCallbackSet( TStepLow* tStepLow, TeleoError (*accelerationUpdate)( TStepLow* tStepLow, int16 acceleration ) );

/** Gets the current busy value.
    \param tStepLow Teleo Stepper Device
    \param busy pointer to the busy 
    \return TELEO_OK or appropriate error code
  */
//TeleoError TStepLow_busyGet( TStepLow* tStepLow, bool* busy );

/** Set the callback for busy updates
    \param tStepLow Teleo Stepper Device
    \param busyUpdate busy callback function 
    \return TELEO_OK or appropriate error code
 */
//TeleoError TStepLow_busyCallbackSet( TStepLow* tStepLow, TeleoError (*busyUpdate)( TStepLow* tStepLow, bool busy ) );

/** Gets the Analog Position Resolution
    \param tStepLow Teleo Stepper Device
    \param curSampleRate pointer to current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_analogPositionResolutionGet( TStepLow* tStepLow, uint8* resolution );

/** Sets the Analog Position Resolution 
    \param tStepLow Teleo Stepper Device
    \param curSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_analogPositionResolutionSet( TStepLow* tStepLow, uint8 resolution );

/** Set the callback for current sample rate updates
    \param tStepLow Teleo Stepper Device
    \param curSampleRateUpdate current sample rate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_analogPositionResolutionCallbackSet( TStepLow* tStepLow, TeleoError (*analogPositionResolution)( TStepLow* tStepLow, uint8 resolution ) );

/** Gets the Current Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param curSampleRate pointer to current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_motorCurrentSamplePeriodGet( TStepLow* tStepLow, int16* motorCurrentSampleRate );

/** Sets the Current Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param curSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_motorCurrentSamplePeriodSet( TStepLow* tStepLow, int16 motorCurrentSampleRate );

/** Set the callback for current sample rate updates
    \param tStepLow Teleo Stepper Device
    \param curSampleRateUpdate current sample rate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_motorCurrentSampleRateCallbackSet( TStepLow* tStepLow, TeleoError (*motorCurrentSampleRateUpdate)( TStepLow* tStepLow, int16 motorCurrentSampleRate ) );

/** Gets the Current Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param curSampleRate pointer to current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_analogPositionSamplePeriodGet( TStepLow* tStepLow, int16* analogPositionSampleRate );

/** Sets the Current Sample Rate in ms
    \param tStepLow Teleo Stepper Device
    \param curSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_analogPositionSamplePeriodSet( TStepLow* tStepLow, int16 analogPositionSampleRate );

/** Set the callback for current sample rate updates
    \param tStepLow Teleo Stepper Device
    \param curSampleRateUpdate current sample rate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_analogPositionSampleRateCallbackSet( TStepLow* tStepLow, TeleoError (*analogPositionSampleRateUpdate)( TStepLow* tStepLow, int16 analogPositionSampleRate ) );

/** Gets the current on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param current current value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_stepPositionCurrentGet( TStepLow* tStepLow, long* stepPositionCurrent );

/** Set the callback for current updates
    \param tStepLow Teleo Stepper Device
		\param currentUpdate current update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_stepPositionCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*stepPositionCurrentUpdate)( TStepLow* tStepLow, long stepPositionCurrent ) );

/** Gets the current on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param current current value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_analogPositionCurrentGet( TStepLow* tStepLow, int16* analogPosition );

/** Set the callback for current updates
    \param tStepLow Teleo Stepper Device
		\param currentUpdate current update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_analogPositionCurrentCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*analogPositionCurrentUpdate)( TStepLow* tStepLow, int16 analogPositionCurrent ) );

/** Gets the current on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param current current value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_motorCurrentGet( TStepLow* tStepLow, int16* motorCurrent );

/** Set the callback for current updates
    \param tStepLow Teleo Stepper Device
		\param currentUpdate current update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_motorCurrentCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*motorCurrentUpdate)( TStepLow* tStepLow, int16 motorCurrent ) );

/** Gets the limitA value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param limitA limitA value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_limitAGet( TStepLow* tStepLow, bool* limitA );

/** Set the callback for bound updates
    \param tStepLow Teleo Stepper Device
		\param limitAUpdate limitA callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_limitACallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*limitAUpdate)( TStepLow* tStepLow, bool limitA ) );

/** Gets the limitB value on the specified TStepLow.
    \param tStepLow Teleo Stepper Device
    \param limitB limitB value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepLow_limitBGet( TStepLow* tStepLow, bool* limitB );

/** Set the callback for bound updates
    \param tStepLow Teleo Stepper Device
		\param limitBUpdate limitB callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepLow_limitBCallbackSet( 
		         TStepLow* tStepLow, 
		         TeleoError (*limitBUpdate)( TStepLow* tStepLow, bool limitB ) );


#ifdef __cplusplus
}
#endif

#endif
