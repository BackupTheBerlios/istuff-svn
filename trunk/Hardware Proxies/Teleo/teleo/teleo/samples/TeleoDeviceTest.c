/* Copyright 2003 MakingThings LLC. */

/** \file TeleoDeviceTest.c
    Simple Device Manager Demonstration Program.
    Sets up a Device Manager and a Channel Manager.
    Reports modules, incoming messages, button presses, etc.
 */

#include <stdio.h>
#include <stdlib.h>

#include "TeleoEasy.h"

// 
// Locals
//

// TeleoDeviceManagerDevice Callbacks
TeleoError deviceBound( TDM_Device* tdmd, void* tdmdExt, bool bound );
TeleoError devicePropertyUpdate( TDM_Device* tdmd, void* tdmdExt, uint8 propertyIndex, TeleoData* data );

/// Reference to the Device Manager
TeleoDeviceManager* teleoDeviceManager;

// the devices
TDM_Device* device1;
TDM_Device* device2;
TDM_Device* device3;
TDM_Device* device4;
TDM_Device* device5;

int main( int argc, char* argv[] ) 
{
  bool bound;
  cchar* devicePath;
  
  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  if ( TeleoEasy_Init( devicePath, TI_USB, &teleoDeviceManager ) != TELEO_OK )
    exit( 1 );

  // Create all the devices - note none will be bound since
  // we haven't started the input thread yet.

  // Create device 1
  if ( TDM_deviceCreate( teleoDeviceManager, NULL, 0, NULL, "3", &bound, &device1 ) != TELEO_OK )
    exit( 1 );
  TDMD_boundCallbackSet( device1, deviceBound );
  TDMD_propertyUpdateCallbackSet( device1, devicePropertyUpdate );
  
  // Create device 2
  if ( TDM_deviceCreate( teleoDeviceManager, NULL, 1, NULL, "3", &bound, &device2 ) != TELEO_OK )
    exit( 1 );
  TDMD_boundCallbackSet( device2, deviceBound );
  TDMD_propertyUpdateCallbackSet( device2, devicePropertyUpdate );

   // Create device 3
  if ( TDM_deviceCreate( teleoDeviceManager, NULL, 4, NULL, "3", &bound, &device3 ) != TELEO_OK )
    exit( 1 );
  TDMD_boundCallbackSet( device3, deviceBound );
  TDMD_propertyUpdateCallbackSet( device3, devicePropertyUpdate );

  // Create device 4
  if ( TDM_deviceCreate( teleoDeviceManager, NULL, 8, NULL, "3", &bound, &device4 ) != TELEO_OK )
    exit( 1 );
  TDMD_boundCallbackSet( device4, deviceBound );
  TDMD_propertyUpdateCallbackSet( device4, devicePropertyUpdate );
  
  // Create device 5
  if ( TDM_deviceCreate( teleoDeviceManager, NULL, 12, NULL, "3", &bound, &device5 ) != TELEO_OK )
    exit( 1 );
  TDMD_boundCallbackSet( device5, deviceBound );
  TDMD_propertyUpdateCallbackSet( device5, devicePropertyUpdate );

  TeleoEasy_Start();

  TeleoEasy_Continue();

  return TELEO_OK;
}

// 
// Callbacks - will be called by the Device Manager
//

TeleoError deviceBound( TDM_Device *tdmd, void* tdmdExt, bool bound )
{
  printf( "TDS: Device %sound\n", ( bound ? "B" : "Unb" ) );

  TDM_monitorAll( teleoDeviceManager );

  return TELEO_OK;
}

TeleoError devicePropertyUpdate( TDM_Device *tdmd, void* tdmdExt, uint8 propertyIndex, TeleoData* data )
{
  char* d;
  char s[ 100 ];

  d = NULL;
  if ( tdmd == device1 )
    d = "Device1";
  if ( tdmd == device2 )
    d = "Device2";
  if ( tdmd == device3 )
    d = "Device3";
  if ( d == NULL )
    d = "??";

  TeleoData_readString ( data, s, 100 );
  printf( "TDS: %s Property Update %d:%s\n", d, propertyIndex, s );

  if ( tdmd == device3 )
    TDMD_propertySet( device4, 0, data );
  if ( tdmd == device1 )
    TDMD_propertySet( device5, 0, data );
  
  return TELEO_OK;
}
