/* Copyright 2003 MakingThings LLC. */

/** \file TeleoMioPwm.h
    Device Wrapper API.
    Contains the structures, definitions and functions for a 
    set of functions that wrap TeleoDevice entities providing
    a very Teleo Module-like interface.
    
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_INTRO_PWM_H_
#define _TELEO_INTRO_PWM_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Intro IO PWM output
//

/**
  TeleoMioPwm reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TIntroPwm;

/** Create a TIntroPwm.
    \param tdm TeleoDeviceManager
    \param address module address (or 0 if don't care)
    \param pwmDeviceIndex Pwm device on the MultiIO (0 - 1)
    \param bound is the module specified already bound?
    \param tmpwm a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TIntroPwm_Create( TeleoDeviceManager* tdm, cchar* address, uint8 pwmDeviceIndex, bool* bound, TIntroPwm** tmpwm );

/** Gets the current bound state
    \param tmpwm TIntroPwm
    \param bound pointer to the bound variable
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_boundGet( TIntroPwm* tmpwm, bool* bound );

/** Set the callback for bound updates
    \param tmpwm TIntroPwm
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroPwm_boundCallbackSet( TIntroPwm* tmpwm, TeleoError (*boundUpdate)( TIntroPwm* tmpwm, bool bound ) );

/** Gets the Duty value on the specified TIntroPwm.
    \param tmpwm TIntroPwm
    \param duty desired duty cycle pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_dutyGet( TIntroPwm* tmpwm, float* duty );

/** Sets the Duty value on the specified TIntroPwm.
    \param tmpwm TIntroPwm
    \param duty new duty value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_dutySet( TIntroPwm* tmpwm, float duty );

/** Set the callback for duty updates
    \param tmpwm TIntroPwm
    \param dutyUpdate dutyUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroPwm_dutyCallbackSet( TIntroPwm* tmpwm, TeleoError (*dutyUpdate)( TIntroPwm* tmpwm, float duty ) );

/** Gets the Maximum Duty value on the specified TIntroPwm.
    \param tmpwm TIntroPwm
    \param dutyMax desired maximum duty cycle pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_dutyMaxGet( TIntroPwm* tmpwm, float* dutyMax );

/** Sets the Maximum Duty value on the specified TIntroPwm.
    \param tmpwm TIntroPwm
    \param dutyMax new dutyMax value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_dutyMaxSet( TIntroPwm* tmpwm, float dutyMax );

/** Gets the Enable value on the specified TIntroPwm.
    \param tmpwm TIntroPwm
    \param enable enable value pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_enableGet( TIntroPwm* tmpwm, bool* enable );

/** Sets the Enable value on the specified TIntroPwm.
    \param tmpwm TIntroPwm reference returned from TIntroPwm_create( )
    \param enable new enable value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TIntroPwm_enableSet( TIntroPwm* tmpwm, bool enable );

/** Set the callback for enable updates
    \param tmpwm TIntroPwm
    \param enableUpdate enableUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TIntroPwm_enableCallbackSet( TIntroPwm* tmpwm, TeleoError (*enableUpdate)( TIntroPwm* tmpwm, bool enable ) );

#ifdef __cplusplus
}
#endif
  
#endif
