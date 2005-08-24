/* Copyright 2003 MakingThings LLC. */

/** \file light.c
     Example of three devices interacting together
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "TeleoIntroAin.h"
#include "TeleoIntroDin.h"
#include "TeleoIntroDout.h"
#include "TeleoIntroPwm.h"
#include "TeleoEasy.h"
  
// local function for callbacks
TeleoError potValueUpdate ( TIntroAin* tiain, int16 value );
TeleoError valueUpdate ( TIntroDin* tmdin, bool value );
TeleoError dutyUpdate ( TIntroPwm* tmpwm, float value );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices

TIntroAin* pot;
TIntroDin* button1;
TIntroDin* button2;
TIntroPwm* light;
TIntroDout* lightLimit1;
TIntroDout* lightLimit2;

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
  TIntroAin_Create( teleoDeviceManager, NULL, 0, NULL, &pot );
  TIntroDin_Create( teleoDeviceManager, NULL, 0, NULL, &button1 );
  TIntroDin_Create( teleoDeviceManager, NULL, 1, NULL, &button2 );
  TIntroPwm_Create( teleoDeviceManager, NULL, 0, NULL, &light );
  TIntroDout_Create( teleoDeviceManager, NULL, 0, NULL, &lightLimit1 );
  TIntroDout_Create( teleoDeviceManager, NULL, 1, NULL, &lightLimit2 );
  
  // make sure everything got initiallized properly
  if ( !pot || !button1 || !button2 || !light || !lightLimit1 || !lightLimit2 )
    exit( 1 );
  
  // set both DIN callbacks to the same function
  TIntroDin_valueCallbackSet( button1, valueUpdate );
  TIntroDin_valueCallbackSet( button2, valueUpdate );

  TIntroAin_valueCallbackSet( pot, potValueUpdate );

  // Initial light illumination
  lightValue = 0;
  TIntroDout_valueSet( lightLimit1, ( lightValue == 0 ) );
  TIntroDout_valueSet( lightLimit2, ( lightValue == 100 ) ); 
  
  TIntroAin_resolutionSet( pot, 7 );
  TIntroAin_samplePeriodSet( pot, 1 );

  // Start the device system up
  TeleoEasy_Start();

  printf( "Light Buttons Running\n" );

  // Wait around until something kills us.
  TeleoEasy_Continue();

  return TELEO_OK;
}

TeleoError valueUpdate ( TIntroDin* tidin, bool value )
{
  if ( value )
  {
    if ( tidin == button1 && lightValue >= 10 )
      lightValue -= 10;
    
    TIntroDout_valueSet( lightLimit1, ( lightValue == 0 ) );

    if ( tidin == button2 && lightValue <= 90 )
      lightValue += 10;
    
    TIntroDout_valueSet( lightLimit2, ( lightValue == 100 ) );

    TIntroPwm_dutySet( light, lightValue );

    printf( "  %d\n", lightValue );
  }
  return TELEO_OK;
}

TeleoError potValueUpdate ( TIntroAin* tiAin, int16 value )
{

  printf( "  Pot Value Update: %d", value );

  if ( value < 0 )
    value = 0;
  if ( value > 100 )
    value = 100;

  lightValue = (int)value;
  
  TIntroDout_valueSet( lightLimit1, ( lightValue == 0 ) );
  TIntroDout_valueSet( lightLimit2, ( lightValue == 100 ) );

  TIntroPwm_dutySet( light, lightValue );

  printf( "  Set %d\n", lightValue );
  return TELEO_OK;
}

TeleoError dutyUpdate ( TIntroPwm* tmpwm, float value )
{
	printf("pwm duty update, value %f\n", value);
  return TELEO_OK;
}
