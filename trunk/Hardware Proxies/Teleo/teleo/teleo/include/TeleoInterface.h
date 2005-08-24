/* Copyright 2003 MakingThings LLC. */

/** \file TeleoInterface.h
    Generic Low Level IO interface.
    
    Provides the implementation for opening, reading, writing, 
    and closing interfaces of different types
    
    Designed to be linked with the version of TeleoInterfaceXXX.c
    that is appropriate for the target OS.    
 */

#ifndef TELEOINTERFACE_H_
#define TELEOINTERFACE_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoError.h"
#include "TeleoTypes.h"

/** Teleo Interface.
    The public structure used for 
    communication with the Interface
    Internally it is cast into the actual structure
    used by the Interface - implementation.
  */
typedef struct 
{
  uint8 tag;
} TeleoInterface;

typedef enum { TI_USB, TI_USB0, TI_USB1, TI_USB2, TI_USB3, 
               TI_SERIAL, TI_SERIAL0, TI_SERIAL1, TI_SERIAL2, TI_SERIAL3,  
               TI_NETWORK } TI_InterfaceType;

/** Creates and initializes the interface structure.
    Does not open the device, since there maybe be configuration to be done first.
    The name may be omitted.  If this happens, the default name for the supplied interface type 
    will be used.
    \param name the device pathname or URI (optional)
    \param interfaceType the type of interface
    \param ti place to return the new interface
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_Create( cchar* name, TI_InterfaceType interfaceType, TeleoInterface** ti );

/** Destroys the interface
    \param teleoInterface the interface structure
  */
TeleoError TI_destroy( TeleoInterface* teleoInterface );

/** Allows the user to retrieve the interface name
    \param teleoInterface the interface structure
    \param name pointer to the name pointer 
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_nameGet( TeleoInterface* teleoInterface, cchar** name );

/** Allows the user to get the short name - i.e. "ser", "usb", "net", etc.
    \param teleoInterface the interface structure
    \param type the type text pointer
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_typeGet( TeleoInterface* teleoInterface, cchar** type );

/** Control whether the interface does blocking IO or not
    \param teleoInterface the interface structure
    \param blocking yes or no
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_blockingSet( TeleoInterface* teleoInterface, bool blocking );

/** Open the port                       
    \param teleoInterface the interface structure
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_open( TeleoInterface* teleoInterface );

/** Close the port
    \param teleoInterface the interface structure
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_close( TeleoInterface* teleoInterface );

/** Get characters.  
    Currently only permits a single character at a time.
    \param teleoInterface the interface structure
    \param cp pointer to the character
    \param count number of characters to get
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_get( TeleoInterface* teleoInterface, uint8* cp, int count );

/** Put characters
    \param teleoInterface the interface structure
    \param cp pointer to the character
    \param count number of characters to put
    \return TELEO_OK (0) or appropriate error
  */
TeleoError TI_put( TeleoInterface* teleoInterface, uint8* cp, int count );

/** Sleep for the specified ms
    \param ms number of milliseconds
  */
TeleoError TI_SleepMs( long ms );

#ifdef __cplusplus
}
#endif

#endif // TELEOCONTROLLERINTERFACE_H_
