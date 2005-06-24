/* Copyright 2003 MakingThings LLC. */

/** \file button.c
     Example code illustrating getting a single bit in from a button
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "TeleoIntroDin.h"
#include "TeleoEasy.h"
  
// local function for callbacks
TeleoError valueUpdate ( TIntroDin* tmdin, bool value );
TeleoError invertUpdate ( TIntroDin* tmdin, bool invert );
TeleoError sampleUpdate ( TIntroDin* tmdin, int16 sample );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices
TIntroDin* button;

int main( int argc, char* argv[] ) 
{
  TeleoError teleoError;
  cchar* devicePath;
  
  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  if ( TeleoEasy_Init( devicePath, TI_USB, &teleoDeviceManager ) != TELEO_OK )
    exit( 1 );

  // create the device
  teleoError = TIntroDin_Create( teleoDeviceManager, 
                               NULL,     // no address specified - use any
                               0,        // use IntroDin 0
                               NULL,     // no need to know bound status
                               &button ); // the device
  if ( teleoError )
    exit( 1 );
  
  // set up callback: 
  // valueUpdate will be called whenever there's a new
  // value from the button.
  TIntroDin_valueCallbackSet( button, valueUpdate );
  // invertUpdate and sampleUpdate will be called in response
  // to a propertyRequest 
  TIntroDin_invertCallbackSet( button, invertUpdate );
  TIntroDin_samplePeriodCallbackSet( button, sampleUpdate );
  
  // Start the system up
  TeleoEasy_Start();

  printf( "Intro Simple Button Running\n" );

  // Wait until all threads die
  TeleoEasy_Continue();

  return TELEO_OK;
}

TeleoError valueUpdate ( TIntroDin* tmdin, bool value )
{
  // if the button is being pressed
  if ( value )
    printf( "Hello, button\n" );

  return TELEO_OK;
}

TeleoError invertUpdate ( TIntroDin* tmdin, bool invert )
{
  // printf( "invert has been updated to value %d\n", invert );
  return TELEO_OK;
}

TeleoError sampleUpdate ( TIntroDin* tmdin, int16 sample )
{
  // printf( "sample rate has been updated to value %d\n", sample );
  return TELEO_OK;
}
