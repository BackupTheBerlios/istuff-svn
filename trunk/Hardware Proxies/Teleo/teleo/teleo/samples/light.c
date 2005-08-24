/* Copyright 2003 MakingThings LLC. */

/** \file light.c
     Example of three devices interacting together
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "TeleoMioDin.h"
#include "TeleoMioPwm.h"
#include "TeleoEasy.h"
  
// local function for callbacks
TeleoError valueUpdate ( TMioDin* tmdin, bool value );
TeleoError dutyUpdate ( TMioPwm* tmpwm, float value );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices
TMioDin* button1;
TMioDin* button2;
TMioPwm* light;

// Light Value
int8 lightValue;

int main( int argc, char* argv[] ) 
{
  cchar* devicePath;
  
  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  if ( TeleoEasy_Init( devicePath, TI_USB, &teleoDeviceManager ) != TELEO_OK )
    exit( 1 );

  // create the three devices we'll be using
  TMioDin_Create( teleoDeviceManager, NULL, 0, NULL, &button1 );
  TMioDin_Create( teleoDeviceManager, NULL, 1, NULL, &button2 );
  TMioPwm_Create( teleoDeviceManager, NULL, 0, NULL, &light );
  
  // make sure everything got initiallized properly
  if ( !button1 || !button2 || !light )
    exit( 1 );
  
  // set both callbacks to the same function
  TMioDin_valueCallbackSet( button1, valueUpdate );
  TMioDin_valueCallbackSet( button2, valueUpdate );
  TMioPwm_dutyCallbackSet( light, dutyUpdate);

  // Initial light illumination
  lightValue = 0;
  
  // Start the device system up
  TeleoEasy_Start();

  printf( "Light Buttons Running\n" );

  // Wait around until something kills us.
  TeleoEasy_Continue();

  return TELEO_OK;
}

TeleoError valueUpdate ( TMioDin* tmdin, bool value )
{
  if ( value )
  {
    if ( tmdin == button1 && lightValue >= 10 )
      lightValue -= 10;
    if ( tmdin == button2 && lightValue <= 90 )
      lightValue += 10;
    
    TMioPwm_dutySet( light, lightValue );

    printf( "  %d\n", lightValue );
  }
  return TELEO_OK;
}

TeleoError dutyUpdate ( TMioPwm* tmpwm, float value )
{
	printf("pwm duty update, value %f\n", value);
  return TELEO_OK;
}
