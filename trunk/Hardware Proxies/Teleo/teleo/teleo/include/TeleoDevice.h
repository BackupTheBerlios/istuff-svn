/* Copyright 2003 MakingThings LLC. */

/** \file TeleoDevice.h
     Sets up the Teleo SDK and provides a TeleoDeviceManager.
     Provides functions for the connection of all the 
     layers of the SDK.  Used in several example
     apps.
     
     Designed to be linked with the version of TeleoDeviceXXX.c
     that is appropriate for the target OS.
     
     Provides a TeleoDeviceManager* from which it is
     possible to create devices, or device wrappers.
     
     Note that code called in callbacks from the lower system
     levels will have been initiated in one of either the
     timer or input threads which are (conservatively) protected 
     by mutex locks.
     
     Code called in the main program thread is not thread safe, 
     so all calls into the Teleo SDK should be protected
     with TeleoDevice_LibraryLock( ) / Unlock( ) calls.
 */

#ifndef _TELEODEVICE_H_
#define _TELEODEVICE_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoInterface.h"
#include "TeleoDeviceManager.h"

/** Initializes the system
    \param interfaceName the device name - can be NULL for default
    \param interfaceTypeId the interface type (i.e. TI_USB, TI_SERIAL, etc.)
    \param tdm the Device Manager return value
    \return TELEO_OK (0) or appropriate error  */
TeleoError TeleoDevice_Init( cchar* interfaceName, TI_InterfaceType interfaceTypeId, TeleoDeviceManager** tdm );

/** Adds additional interfaces
    \param interfaceName the device name - can be NULL for default
    \param interfaceTypeId the interface type (i.e. TI_USB, TI_SERIAL, etc.)
  */
TeleoError TeleoDevice_InterfaceAdd( cchar* interfaceName, TI_InterfaceType interfaceTypeId );

/** Returns the Module Manager in case any lower level 
    calls need to be made
  */
TeleoModuleManager* TeleoDevice_TeleoModuleManagerGet( );

/** Starts the system
  */
void TeleoDevice_Start();

/** Waits for the library to exit
  */
void TeleoDevice_Continue();

/** Locks access to the library
  */
void TeleoDevice_LibraryLock();

/** Unlocks access to the library
  */
void TeleoDevice_LibraryUnlock();

#ifdef __cplusplus
}
#endif
  
#endif
