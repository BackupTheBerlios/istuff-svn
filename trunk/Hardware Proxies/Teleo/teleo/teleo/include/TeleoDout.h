/* Copyright 2003 MakingThings LLC. */

/** \file TeleoDout.h
    TeleoDout API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo Digital Out to provide a convenient programmatical
    interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.

: set tabstop=2 shiftwidth=2
 */

#ifndef _TELEO_DOUT_H_
#define _TELEO_DOUT_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Dout Controller
//

// TODO:
// Need to add the code that resends all the relevant stuff on a reboot

/**
  TeleoDout reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TDout;

/** Create a TDout.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param doutDeviceIndex which dout device on the Dout Controller
    \param bound is the module specified already bound? FIXME optional
    \param dout a variable to hold the new device
    \return TELEO_OK (0) or an error value
  */
TeleoError TDout_Create( TeleoDeviceManager* tdm, 
  		                   cchar* address, 
  			                 uint8 doutDeviceIndex, 
  			                 bool* bound,
                         TDout** dout );

/** Gets the current bound state
    \param dout TDOut Object
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TDout_boundGet( TDout* dout, bool* bound );

/** Set the callback for bound updates
    \param dout TDOut Object
		\param boundUpdate bound callback function
		\return TELEO_OK or appropriate error code
 */
TeleoError TDout_boundCallbackSet( 
		         TDout* dout, 
		         TeleoError (*boundUpdate)( TDout* dout, bool bound ) );

/** Gets the current value
    \param dout TDOut Object
    \param value pointer to the value 
    \return TELEO_OK or appropriate error code
  */
TeleoError TDout_valueGet( TDout* dout, bool* value );

/** Sets the value on the specified TDout.
    \param dout TDout reference returned from TDout_create( )
    \param value new value
    \return TELEO_OK or appropriate error code
  */
TeleoError TDout_valueSet( TDout* dout, bool value );

#ifdef __cplusplus
}
#endif
  
#endif
