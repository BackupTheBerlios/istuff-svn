/* Copyright 2003 MakingThings LLC. */

/** \file intro_pwm.c
     Example of using a button on din to toggle on and off the pwm output,
     while a pot on ain controlls pwm duty cycle
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
TeleoError dutyUpdate ( TIntroPwm* tmpwm, float value );
TeleoError buttonValueUpdate ( TIntroDin* tidin, bool value );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices

TIntroAin* pot;
TIntroDin* button;
TIntroPwm* pwm;

// PWM duty cycle
int8 pwmDuty;

// PWM enable
bool pwmEnable;

// Debuggin aid: does the PWM device function before enable is touched?
bool firstTime;

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
  TIntroAin_Create( teleoDeviceManager, NULL, 3, NULL, &pot );
  TIntroDin_Create( teleoDeviceManager, NULL, 1, NULL, &button );
  TIntroPwm_Create( teleoDeviceManager, NULL, 0, NULL, &pwm );
  
  // make sure everything got initiallized properly
  if ( !pot || !button || !pwm )
    exit( 1 );
  
  // set input callbacks 
  TIntroDin_valueCallbackSet( button, buttonValueUpdate );
  TIntroAin_valueCallbackSet( pot, potValueUpdate );

  // Initial PWM values
  pwmDuty = 0;
  pwmEnable = 1;

  firstTime = true;
  
  TIntroAin_resolutionSet( pot, 7 );
  TIntroAin_samplePeriodSet( pot, 10 );
  TIntroPwm_dutyMaxSet( pwm, 100 );

  // Start the device system up
  TeleoEasy_Start();

  printf( "PWM Control Running: Ain 3 controls duty cycle and Din 1 toggles on/off of PWM 0\n" );

  // Wait around until something kills us.
  TeleoEasy_Continue();

  return TELEO_OK;
}

TeleoError buttonValueUpdate ( TIntroDin* tidin, bool value )
{
  printf("button value = %d\n", value); // to test whether din is still inverted

  if (firstTime)
  {
    printf("ignoring first button update, value = %d\n", value);
    firstTime = false;
    return TELEO_OK;
  }

  if ( value )
  {
    pwmEnable = !pwmEnable;

    printf( "  setting PWM Enable to %d\n", pwmEnable );
    TIntroPwm_enableSet( pwm, pwmEnable );

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

  pwmDuty = (int)value;
  
  TIntroPwm_dutySet( pwm, pwmDuty );

  printf( "  Set %d\n", pwmDuty );
  return TELEO_OK;
}

