/* Copyright 2003 MakingThings LLC. */

/** \file TeleoMioPwm.h
    Device Wrapper API.
    Contains the structures, definitions and functions for a 
    set of functions that wrap TeleoDevice entities providing
    a very Teleo Module-like interface.
    
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_MIO_PWM_H_
#define _TELEO_MIO_PWM_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Multi IO PWM output
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
} TMioPwm;

/** Create a TMioPwm.
    \param tdm TeleoDeviceManager
    \param address module address (or 0 if don't care)
    \param pwmDeviceIndex Pwm device on the MultiIO (0 - 1)
    \param bound is the module specified already bound?
    \param tmpwm a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TMioPwm_Create( TeleoDeviceManager* tdm, cchar* address, uint8 pwmDeviceIndex, bool* bound, TMioPwm** tmpwm );

/** Gets the current bound state
    \param tmpwm TMioPwm
    \param bound pointer to the bound variable
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_boundGet( TMioPwm* tmpwm, bool* bound );

/** Set the callback for bound updates
    \param tmpwm TMioPwm
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioPwm_boundCallbackSet( TMioPwm* tmpwm, TeleoError (*boundUpdate)( TMioPwm* tmpwm, bool bound ) );

/** Gets the Duty value on the specified TMioPwm.
    \param tmpwm TMioPwm
    \param duty desired duty cycle pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_dutyGet( TMioPwm* tmpwm, float* duty );

/** Sets the Duty value on the specified TMioPwm.
    \param tmpwm TMioPwm
    \param duty new duty value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_dutySet( TMioPwm* tmpwm, float duty );

/** Set the callback for duty updates
    \param tmpwm TMioPwm
    \param dutyUpdate dutyUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioPwm_dutyCallbackSet( TMioPwm* tmpwm, TeleoError (*dutyUpdate)( TMioPwm* tmpwm, float duty ) );

/** Gets the Maximum Duty value on the specified TMioPwm.
    \param tmpwm TMioPwm
    \param dutyMax desired maximum duty cycle pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_dutyMaxGet( TMioPwm* tmpwm, float* dutyMax );

/** Sets the Maximum Duty value on the specified TMioPwm.
    \param tmpwm TMioPwm
    \param dutyMax new dutyMax value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_dutyMaxSet( TMioPwm* tmpwm, float dutyMax );

/** Set the callback for Maximum Duty updates
    \param tmpwm TMioPwm
    \param dutyMaxUpdate dutyMaxUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioPwm_dutyMaxCallbackSet( TMioPwm* tmpwm, TeleoError (*dutyMaxUpdate)( TMioPwm* tmpwm, float dutyMax ) );

/** Gets the Enable value on the specified TMioPwm.
    \param tmpwm TMioPwm
    \param enable enable value pointer
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_enableGet( TMioPwm* tmpwm, bool* enable );

/** Sets the Enable value on the specified TMioPwm.
    \param tmpwm TMioPwm reference returned from TMioPwm_create( )
    \param enable new enable value
    \return TELEO_OK or an error (see TeleoError.h)
  */
TeleoError TMioPwm_enableSet( TMioPwm* tmpwm, bool enable );

/** Set the callback for enable updates
    \param tmpwm TMioPwm
    \param enableUpdate enableUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TMioPwm_enableCallbackSet( TMioPwm* tmpwm, TeleoError (*enableUpdate)( TMioPwm* tmpwm, bool enable ) );

#ifdef __cplusplus
}
#endif
  
#endif
