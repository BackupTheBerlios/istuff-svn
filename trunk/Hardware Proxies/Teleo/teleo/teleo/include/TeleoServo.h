/* Copyright 2003 MakingThings LLC. */

/** \file TeleoServo.h
    TeleoServo API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo Servo to provide a convenient programmatical
    interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.

: set tabstop=2 shiftwidth=2
 */

#ifndef _TELEO_SERVO_H_
#define _TELEO_SERVO_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Servo Controller
//

// TODO:
// Need to add the code that resends all the relevant stuff on a reboot

/**
  TServo reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TServo;

/** Create a TServo.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param servoDeviceIndex which servo device on the Servo Controller
    \param bound is the module specified already bound?
    \param servo a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TServo_Create( TeleoDeviceManager* tdm, 
    		                  cchar* address, 
    			                uint8 servoDeviceIndex, 
    			                bool* bound,
                          TServo** servo );

/** Gets the current bound state
    \param servo TServo reference returned from TServo_create( )
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_boundGet( TServo* servo, bool* bound );

/** Set the callback for bound updates
    \param servo TServo reference returned from TServo_create( )
		\param boundUpdate bound callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TServo_boundCallbackSet( 
		         TServo* servo, 
		         TeleoError (*boundUpdate)( TServo* servo, bool bound ) );

/** Gets the current Position value.
    \param servo TServo reference returned from TServo_create( )
    \param position pointer to the position 
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_positionGet( TServo* servo, float* position );

/** Sets the Position value on the specified TServo.
    \param servo TServo reference returned from TServo_create( )
    \param position new position value
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_positionSet( TServo* servo, float position );

/** Gets the current Position Min value.
    \param servo TServo reference returned from TServo_create( )
    \param positionMin pointer to the position minimum
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_positionMinGet( TServo* servo, float* positionMin );

/** Sets the Position Min value on the specified TServo.
    \param servo TServo reference returned from TServo_create( )
    \param positionMin new position value
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_positionMinSet( TServo* servo, float positionMin );

/** Gets the current Position Max value.
    \param servo TServo reference returned from TServo_create( )
    \param positionMax pointer to the position minimum
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_positionMaxGet( TServo* servo, float* positionMax );

/** Sets the Position Max value on the specified TServo.
    \param servo TServo reference returned from TServo_create( )
    \param positionMax new position value
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_positionMaxSet( TServo* servo, float positionMax );

/** Gets the current Enable value.
    \param servo TServo reference returned from TServo_create( )
    \param enable pointer to the enable
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_enableGet( TServo* servo, bool* enable );

/** Sets the Enable value on the specified TServo.
    \param servo TServo reference returned from TServo_create( )
    \param enable new enable value
    \return TELEO_OK or appropriate error code
  */
TeleoError TServo_enableSet( TServo* servo, bool enable );

#ifdef __cplusplus
}
#endif
  
#endif
