/* Copyright 2003 MakingThings LLC. */

/** \file TeleoModule.h
     Sets up the Teleo SDK and provides a TeleoModuleManager.
     Provides functions for the connection of all the 
     layers of the SDK.  Used in several example
     apps.
     
     Designed to be linked with the version of TeleoModuleXXX.c
     that is appropriate for the target OS.
     
     Provides a TeleoDeviceManager* from which it is
     possible to create devices, or device wrappers.
 */

#ifndef _TELEOMODULE_H_
#define _TELEOMODULE_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoInterface.h"
#include "TeleoModuleManager.h"

/** Start the system up with the specified interface
  \param interfaceName the device name - can be NULL for default
  \param interfaceType the interface type (i.e. TI_USB, TI_SERIAL, etc.)
  \param tmm return variable for the new Module Manager
  \return TELEO_OK (0) or appropriate error
 */
TeleoError TeleoModule_Init( cchar* interfaceName, TI_InterfaceType interfaceType, TeleoModuleManager** tmm );

/** Ends it all
 */
TeleoError TeleoModule_End( );

/** Starts the timer and input threads 
 */
void TeleoModule_Start();

/** Causes the current thread to pause waiting for the others to finish 
 */
void TeleoModule_Continue();

/** Locks access to the library
  */
void TeleoModule_Lock();

/** Locks access to the library
  */
void TeleoModule_Unlock();


#ifdef __cplusplus
}
#endif
  
#endif
