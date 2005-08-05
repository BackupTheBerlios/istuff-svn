/* Copyright 2003 MakingThings LLC. */
/*
: set tabstop=2 shiftwidth=2
*/

/** \file TeleoMotor.h
    TeleoMotor API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo Motor to provide a convenient programmatical
    interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.

 */

#ifndef _TELEO_MOTOR_H_
#define _TELEO_MOTOR_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Motor Controller
//

/**
  TeleoMotor reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TMotor;

/** Create a Dual 2Amp TMotor.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param motorDeviceIndex 2Amp motor device on the Dual 2Amp Motor Controller
    \param bound is the module specified already bound?
    \param tMotor a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TMotor_Dual2ACreate( TeleoDeviceManager* tdm, 
               		              cchar* address, 
                                uint8 motorDeviceIndex, 
                                bool* bound,
                                TMotor** tMotor );

/** Create a 10Amp TMotor.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param bound is the module specified already bound?
    \param tMotor a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TMotor_10ACreate( TeleoDeviceManager* tdm, 
		                      cchar* address, 
			                    bool* bound,
                          TMotor** tMotor );

/** Gets the current bound state
    \param tMotor Teleo Motor Device
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_boundGet( TMotor* tMotor, bool* bound );

/** Set the callback for bound updates
    \param tMotor Teleo Motor Device
		\param boundUpdate bound callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_boundCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*boundUpdate)( TMotor* tMotor, bool bound ) );

/** Gets the current Speed value.
    \param tMotor Teleo Motor Device
    \param speed pointer to the speed 
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_speedGet( TMotor* tMotor, float* speed );

/** Sets the Speed value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param speed new speed value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_speedSet( TMotor* tMotor, float speed );

/** Set the callback for speed updates
    \param tMotor Teleo Motor Device
		\param speedUpdate speed update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_speedCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*speedUpdate)( TMotor* tMotor, float speed ) );

/** Gets the current Speed Max value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param speedMax pointer to the speedMax 
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_speedMaxGet( TMotor* tMotor, float* speedMax );

/** Sets the Speed Max value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param speedMax new speedMax value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_speedMaxSet( TMotor* tMotor, float speedMax );

/** Set the callback for current updates
    \param tMotor Teleo Motor Device
		\param speedMaxUpdate current update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_speedMaxCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*speedMaxUpdate)( TMotor* tMotor, float speedMax ) );

/** Gets the current Brake On value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param brakeOn pointer to the brakeOn value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_brakeOnGet( TMotor* tMotor, bool* brakeOn );

/** Sets the Brake On value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param brakeOn new brakeOn value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_brakeOnSet( TMotor* tMotor, bool brakeOn );

/** Set the callback for current updates
    \param tMotor Teleo Motor Device
		\param brakeOnUpdate Brake On update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_brakeOnCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*brakeOnUpdate)( TMotor* tMotor, bool brakeOn ) );

/** Gets the current On value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param on pointer to the on value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_onGet( TMotor* tMotor, bool* on );

/** Sets the On value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param on new on value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_onSet( TMotor* tMotor, bool on );

/** Set the callback for current updates
    \param tMotor Teleo Motor Device
		\param onUpdate On update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_onCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*onUpdate)( TMotor* tMotor, bool on ) );

/** Gets the current Invert value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param invert pointer to the invert value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_invertGet( TMotor* tMotor, bool* invert );

/** Sets the Invert value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param invert new invert value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_invertSet( TMotor* tMotor, bool invert );

/** Set the callback for invert updates
    \param tMotor Teleo Motor Device
		\param invertUpdate invert update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_invertCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*invertUpdate)( TMotor* tMotor, bool invert ) );

/** Gets the Current Sample Rate in ms
    \param tMotor Teleo Motor Device
    \param curSampleRate pointer to current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_curSampleRateGet( TMotor* tMotor, int16* curSampleRate );

/** Sets the Current Sample Rate in ms
    \param tMotor Teleo Motor Device
    \param curSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_curSampleRateSet( TMotor* tMotor, int16 curSampleRate );

/** Set the callback for current sample rate updates
    \param tMotor Teleo Motor Device
		\param curSampleRateUpdate curSampleRate update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_curSampleRateCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*curSampleRateUpdate)( TMotor* tMotor, int16 curSampleRate ) );

/** Gets the current value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param current current value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_currentGet( TMotor* tMotor, int16* current );

/** Set the callback for current updates
    \param tMotor Teleo Motor Device
		\param currentUpdate current update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_currentCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*currentUpdate)( TMotor* tMotor, int16 current ) );

/** Gets the currentMax value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param currentMax currentMax value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_currentMaxGet( TMotor* tMotor, int16* currentMax );

/** Sets the currentMax value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param currentMax new currentMax value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_currentMaxSet( TMotor* tMotor, int16 currentMax );

/** Set the callback for currentMax updates
    \param tMotor Teleo Motor Device
		\param currentMaxUpdate currentMax update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_currentMaxCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*currentMaxUpdate)( TMotor* tMotor, int16 currentMax ) );

/** Gets the limitA value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param limitA limitA value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_limitAGet( TMotor* tMotor, bool* limitA );

/** Set the callback for bound updates
    \param tMotor Teleo Motor Device
		\param limitAUpdate limitA callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_limitACallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*limitAUpdate)( TMotor* tMotor, bool limitA ) );

/** Gets the limitB value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param limitB limitB value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_limitBGet( TMotor* tMotor, bool* limitB );

/** Set the callback for bound updates
    \param tMotor Teleo Motor Device
		\param limitBUpdate limitB callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_limitBCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*limitBUpdate)( TMotor* tMotor, bool limitB ) );

/** Gets the limitsOn value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param limitsOn limitsOn value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_limitsOnGet( TMotor* tMotor, bool* limitsOn );

/** Sets the limitsOn value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param limitsOn new limitsOn value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_limitsOnSet( TMotor* tMotor, bool limitsOn );

/** Set the callback for limitsOn updates
    \param tMotor Teleo Motor Device
		\param limitsOnUpdate limitsOn update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_limitsOnCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*limitsOnUpdate)( TMotor* tMotor, bool limitsOn ) );

/** Gets the current position value on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param position pointer to the position 
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_positionGet( TMotor* tMotor, float* position );

/** Set the callback for position updates
    \param tMotor Teleo Motor Device
		\param positionUpdate positioin callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_positionCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*positionUpdate)( TMotor* tMotor, float position ) );

/** Gets the Minimum value for the position on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param positionMin position minimum value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_positionMinGet( TMotor* tMotor, float* positionMin );

/** Sets the Minimum value for the position on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param positionMin new position minimum value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_positionMinSet( TMotor* tMotor, float positionMin );

/** Set the callback for positionMin updates
    \param tMotor Teleo Motor Device
		\param positionMinUpdate positionMin update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_positionMinCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*positionMinUpdate)( TMotor* tMotor, float positionMin ) );

/** Gets the Max value for the position on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param positionMax position maximum value pointer
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_positionMaxGet( TMotor* tMotor, float* positionMax );

/** Sets the Maximum value for the position on the specified TMotor.
    \param tMotor Teleo Motor Device
    \param positionMax new position maximum value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_positionMaxSet( TMotor* tMotor, float positionMax );

/** Set the callback for positionMax updates
    \param tMotor Teleo Motor Device
		\param positionMaxUpdate positionMax update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_positionMaxCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*positionMaxUpdate)( TMotor* tMotor, float positionMax ) );

/** Gets the Position Sample Rate in ms
    \param tMotor Teleo Motor Device
    \param posSampleRate pointer to position sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_posSampleRateGet( TMotor* tMotor, int16* posSampleRate );

/** Sets the Position Sample Rate in ms
    \param tMotor Teleo Motor Device
    \param posSampleRate new current sample rate value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_posSampleRateSet( TMotor* tMotor, int16 posSampleRate );

/** Set the callback for posSampleRate updates
    \param tMotor Teleo Motor Device
		\param posSampleRateUpdate posSampleRate update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_posSampleRateCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*posSampleRateUpdate)( TMotor* tMotor, int16 posSampleRate ) );

/** Gets the Position Resolution in bits
    \param tMotor Teleo Motor Device
    \param posResolution pointer to position resolution value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_posResolutionGet( TMotor* tMotor, int8* posResolution );

/** Sets the Position Resolution in bits
    \param tMotor Teleo Motor Device
    \param posResolution new position resolution value
    \return TELEO_OK or appropriate error code
  */
TeleoError TMotor_posResolutionSet( TMotor* tMotor, int8 posResolution );

/** Set the callback for posResolution updates
    \param tMotor Teleo Motor Device
		\param posResolutionUpdate posResolution update callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TMotor_posResolutionCallbackSet( 
		         TMotor* tMotor, 
		         TeleoError (*posResolutionUpdate)( TMotor* tMotor, int8 posResolution ) );

#ifdef __cplusplus
}
#endif
  
#endif
