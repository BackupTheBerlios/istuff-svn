/* Copyright 2003 MakingThings LLC. */

/** \file stepper.c
     Example of two devices interacting together
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "TeleoMioAin.h"
#include "TeleoStepperLow.h"
#include "TeleoEasy.h"
  
// local function for callbacks
TeleoError valueUpdate ( TMioAin* tmain, float value );
TeleoError stepRateUpdate ( TStepLow* tStepLow, float rate );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices
TMioAin* knob;
TStepLow* stepper;

int main( int argc, char* argv[] ) 
{
  cchar* devicePath;
  
  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  if ( TeleoEasy_Init( devicePath, TI_USB, &teleoDeviceManager ) != TELEO_OK )
    exit( 1 );

  // create the two devices we'll be using
  if ( TMioAin_Create( teleoDeviceManager, NULL, 0, NULL, &knob ) )
  {
	  printf("TMioAin_Create() failed\n");
    exit( 1 );
	}
  if ( TStepLow_Create( teleoDeviceManager, NULL, NULL, &stepper ) )
  {
	  printf("TStepLow_Create() failed\n");
	  //printf("TStepLow_Create() failed, retval %d\n", teleoError);
    exit( 1 );
	}
  
  // set both callbacks to the same function
  TMioAin_valueCallbackSet( knob, valueUpdate );
  TStepLow_stepRateCallbackSet( stepper, stepRateUpdate );

  // Start the device system up
  TeleoEasy_Start();

  printf( "Knob output will be set to stepper\n" );

  // Wait around until something kills us.
  TeleoEasy_Continue();

  return TELEO_OK;
}

TeleoError valueUpdate ( TMioAin* tmain, float value )
{
    TStepLow_stepRateSet( stepper, (int16 )value );

  return TELEO_OK;
}

TeleoError stepRateUpdate ( TStepLow* tStepLow, float rate )
{
  return TELEO_OK;
}
