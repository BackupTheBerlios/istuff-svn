/* Copyright 2003 MakingThings LLC. */

/*
 : set tabstop=2 shiftwidth=2
*/

/** \file TeleoStepper.h
    TeleoStepper API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo Stepper to provide a convenient programmatical
    interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.

: set tabstop=2 shiftwidth=2
 */

#ifndef _TELEO_STEPPER_H_
#define _TELEO_STEPPER_H_

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
} TStepper;

TeleoError TStepper_Create( TeleoDeviceManager* tdm, 
		                        cchar* address, 
			                      bool* bound,
                            TStepper** tStepper );

/** Gets the current bound state
    \param tStepper Teleo Stepper Device
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_boundGet( TStepper* tStepper, bool* bound );

/** Set the callback for bound updates
    \param tStepper Teleo Stepper Device
		\param boundUpdate bound callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_boundCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*boundUpdate)( TStepper* tStepper, bool bound ) );

/** Gets the current direction value.
    \param tStepper Teleo Stepper Device
    \param direction pointer to the direction 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_directionGet( TStepper* tStepper, bool* direction );

/** Sets the direction value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param direction new direction value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_directionSet( TStepper* tStepper, bool direction );

/** Set the callback for direction updates
    \param tStepper Teleo Stepper Device
    \param directionUpdate direction update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_directionCallbackSet( TStepper* tStepper, TeleoError (*directionUpdate)( TStepper* tStepper, bool direction ) );

/** Gets the current step rate value.
    \param tStepper Teleo Stepper Device
    \param rate pointer to the step rate 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_rateGet( TStepper* tStepper, int16* rate );

/** Sets the rate step value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param rate new step rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_rateSet( TStepper* tStepper, int16 rate );

/** Set the callback for step rate updates
    \param tStepper Teleo Stepper Device
    \param rateUpdate step rate update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_rateCallbackSet( TStepper* tStepper, TeleoError (*rateUpdate)( TStepper* tStepper, int16 rate ) );

/** Gets the current On value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param on pointer to the on value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_onGet( TStepper* tStepper, bool* on );

/** Sets the On value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param on new on value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_onSet( TStepper* tStepper, bool on );

/** Set the callback for on updates
    \param tStepper Teleo Stepper Device
    \param onUpdate on update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_onCallbackSet( TStepper* tStepper, TeleoError (*onUpdate)( TStepper* tStepper, bool on ) );

/** Gets the limitA value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param limitA limitA value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_limitAGet( TStepper* tStepper, bool* limitA );

/** Set the callback for limitA updates
    \param tStepper Teleo Stepper Device
		\param limitAUpdate limitA callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_limitACallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*limitAUpdate)( TStepper* tStepper, bool limitA ) );

/** Gets the limitB value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param limitB limitB value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_limitBGet( TStepper* tStepper, bool* limitB );

/** Set the callback for limitB updates
    \param tStepper Teleo Stepper Device
		\param limitBUpdate limitB callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_limitBCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*limitBUpdate)( TStepper* tStepper, bool limitB ) );

/** Gets the limitsOn value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param limitsOn limitsOn value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_limitsOnGet( TStepper* tStepper, bool* limitsOn );

/** Sets the limitsOn value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param limitsOn new limitsOn value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_limitsOnSet( TStepper* tStepper, bool limitsOn );

/** Set the callback for limits on updates
    \param tStepper Teleo Stepper Device
		\param limitsOnUpdate limit on callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_limitsOnCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*limitsOnUpdate)( TStepper* tStepper, bool limitsOn ) );

/** Gets the current step position value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param position pointer to the step position 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_positionGet( TStepper* tStepper, float* position );

/** Set the callback for step position updates
    \param tStepper Teleo Stepper Device
		\param positionUpdate positioin callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_positionCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*positionUpdate)( TStepper* tStepper, float position ) );

/** Gets the Position Sample Rate in ms
    \param tStepper Teleo Stepper Device
    \param posSampleRate pointer to position sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_posSampleRateGet( TStepper* tStepper, int16* posSampleRate );

/** Sets the Position Sample Rate in ms
    \param tStepper Teleo Stepper Device
    \param posSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_posSampleRateSet( TStepper* tStepper, int16 posSampleRate );

/** Set the callback for position sample rateupdates
    \param tStepper Teleo Stepper Device
		\param posSampleRateUpdate position sample rate update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_posSampleRateCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*posSampleRateUpdate)( TStepper* tStepper, int16 posSampleRate ) );

/** Gets the step position target
    \param tStepper Teleo Stepper Device
    \param positionTarget pointer to step position target value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_positionTargetGet( TStepper* tStepper, int16* positionTarget );

/** Sets the Position Sample Rate in ms
    \param tStepper Teleo Stepper Device
    \param positionTarget new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_positionTargetSet( TStepper* tStepper, int16 positionTarget );

/** Set the callback for positionTargetle rateupdates
    \param tStepper Teleo Stepper Device
		\param positionTargetUpdate positionTarget update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_positionTargetCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*positionTargetUpdate)( TStepper* tStepper, int16 positionTarget ) );

/** Gets the current maximum step rate value.
    \param tStepper Teleo Stepper Device
    \param rateMax pointer to the maximum step rate 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_rateMaxGet( TStepper* tStepper, int16* rateMax );

/** Sets the maximum step rate value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param rateMax new maximum step rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_rateMaxSet( TStepper* tStepper, int16 rateMax );

/** Set the callback for rateMax updates
    \param tStepper Teleo Stepper Device
    \param rateMaxUpdate rateMax update callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_rateMaxCallbackSet( TStepper* tStepper, TeleoError (*rateMaxUpdate)( TStepper* tStepper, int16 rateMax ) );

/** Gets the current acceleration value.
    \param tStepper Teleo Stepper Device
    \param acceleration pointer to the acceleration 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_accelerationGet( TStepper* tStepper, int16* acceleration );

/** Sets the acceleration value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param acceleration new acceleration value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_accelerationSet( TStepper* tStepper, int16 acceleration );

/** Set the callback for acceleration updates
    \param tStepper Teleo Stepper Device
    \param accelerationUpdate acceleration callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_accelerationCallbackSet( TStepper* tStepper, TeleoError (*accelerationUpdate)( TStepper* tStepper, int16 acceleration ) );

/** Gets the current power value.
    \param tStepper Teleo Stepper Device
    \param power pointer to the power 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_powerGet( TStepper* tStepper, int16* power );

/** Sets the power value on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param power new power value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_powerSet( TStepper* tStepper, int16 power );

/** Set the callback for power updates
    \param tStepper Teleo Stepper Device
    \param powerUpdate power callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_powerCallbackSet( TStepper* tStepper, TeleoError (*powerUpdate)( TStepper* tStepper, int16 power ) );

/** Gets the current busy value.
    \param tStepper Teleo Stepper Device
    \param busy pointer to the busy 
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_busyGet( TStepper* tStepper, bool* busy );

/** Set the callback for busy updates
    \param tStepper Teleo Stepper Device
    \param busyUpdate busy callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_busyCallbackSet( TStepper* tStepper, TeleoError (*busyUpdate)( TStepper* tStepper, bool busy ) );

/** Gets the Current Sample Rate in ms
    \param tStepper Teleo Stepper Device
    \param curSampleRate pointer to current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_curSampleRateGet( TStepper* tStepper, int16* curSampleRate );

/** Sets the Current Sample Rate in ms
    \param tStepper Teleo Stepper Device
    \param curSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_curSampleRateSet( TStepper* tStepper, int16 curSampleRate );

/** Set the callback for current sample rate updates
    \param tStepper Teleo Stepper Device
    \param curSampleRateUpdate current sample rate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TStepper_curSampleRateCallbackSet( TStepper* tStepper, TeleoError (*curSampleRateUpdate)( TStepper* tStepper, int16 curSampleRate ) );

/** Gets the current on the specified TStepper.
    \param tStepper Teleo Stepper Device
    \param current current value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TStepper_currentGet( TStepper* tStepper, int16* current );

/** Set the callback for current updates
    \param tStepper Teleo Stepper Device
		\param currentUpdate current update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TStepper_currentCallbackSet( 
		         TStepper* tStepper, 
		         TeleoError (*currentUpdate)( TStepper* tStepper, int16 current ) );

#ifdef __cplusplus
}
#endif
  
#endif
