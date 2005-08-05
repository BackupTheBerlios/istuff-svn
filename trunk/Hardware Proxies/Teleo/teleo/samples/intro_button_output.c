/* Copyright 2003 MakingThings LLC. */

/** \file button.c
     Example code illustrating getting a single bit in from a button
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "TeleoIntroDin.h"
#include "TeleoIntroDout.h"
#include "TeleoEasy.h"

// shall we use callbacks? otherwise, poll
#define USING_CALLBACKS
#undef USING_CALLBACKS

// local function for callbacks
TeleoError valueUpdate ( TIntroDin* tmdin, bool value );
TeleoError invertUpdate ( TIntroDin* tmdin, bool invert );
TeleoError sampleUpdate ( TIntroDin* tmdin, int16 sample );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices
TIntroDin* button;
TIntroDout* output;

int main( int argc, char* argv[] ) 
{
  TeleoError teleoError;
  cchar* devicePath;
  bool newValue;
  bool lastValue = false;
  TeleoError te;

  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  if ( TeleoEasy_Init( devicePath, TI_USB, &teleoDeviceManager ) != TELEO_OK )
    exit( 1 );

  // create the button device
  teleoError 
    = TIntroDin_Create( teleoDeviceManager, 
      NULL,     // no address specified - use any
      0,        // use IntroDin 0
      NULL,     // no need to know bound status
      &button ); // the device
  if ( teleoError )
    exit( 1 );


  // create the output device
  teleoError 
    = TIntroDout_Create( teleoDeviceManager, 
      NULL,     // no address specified - use any
      0,        // use IntroDout 0
      NULL,     // no need to know bound status
      &output ); // the device
  if ( teleoError )
    exit( 1 );

# ifdef USING_CALLBACKS
  printf( "using callbacks\n");

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
# else
  printf("polled rather than callbacks\n");
  // Start the system up
  TeleoEasy_Start();

  while(1)
  {
    TeleoEasy_Lock();
    te = TIntroDin_valueGet(button, &newValue);

    if( te == TELEO_OK )
    {
      if( newValue != lastValue )
      {
	    printf ("\nturning motor %s\n",
	    newValue ? "ON" : "OFF");
	    TIntroDout_valueSet(output, newValue);
	    lastValue = newValue;
      }
    }
    TeleoEasy_Unlock();
    TI_SleepMs( 1000 );
  }
#endif
  return TELEO_OK;
}

TeleoError valueUpdate ( TIntroDin* tmdin, bool value )
{
  // if the button is being pressed
  if ( value )
    printf( "Hello, button\n" );
  TIntroDout_valueSet(output, value);

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
