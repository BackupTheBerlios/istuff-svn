/* Copyright 2003 MakingThings LLC. */

/*
 : set tabstop=2 shiftwidth=2
 */

/** \file motor.c
     Example of two devices interacting together
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#endif

#include "TeleoMioAin.h"
#include "TeleoMotor.h"
#include "TeleoEasy.h"
 
// local function for callbacks
TeleoError valueUpdate ( TMioAin* tmain, float value );

// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices
TMioAin* knob;
TMotor* motor;

int main( int argc, char* argv[] ) 
{
  cchar* devicePath;

#ifndef WIN32
  struct termios old_ts;
	struct termios new_ts;
#endif

  char c;
	bool done;
  
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
  if ( TMotor_10ACreate( teleoDeviceManager, NULL, NULL, &motor ) )
  {
	  printf("TMotor_Create() failed\n");
	  //printf("TMotor_Create() failed, retval %d\n", teleoError);
    exit( 1 );
	}
  
  // set callback
  TMioAin_valueCallbackSet( knob, valueUpdate );

  // Start the device system up
  TeleoEasy_Start();

  printf( "Knob output will be set to motor\n" );

  // Wait around until something kills us.
  //TeleoEasy_Continue();
	
	// in addition, open up stdin and use j, k, and <space>
	// to control the motor
	
	// first, open the stdin and turn of echo and canonical flags
#if defined MACOSX || defined WIN32
#else
	ioctl(0, TCGETS, &old_ts);
	memcpy(&new_ts, &old_ts, sizeof(old_ts));
	new_ts.c_lflag &= !ICANON;
	new_ts.c_lflag &= !ECHO;
	ioctl(0, TCSETS, &new_ts);

	// now loop, reading keyboard
  while (1) 
  {
		if ((c = getchar()) == EOF) 
		{
		  break;
		}
		switch(c)
		{
			case 'j':
				TMotor_speedSet( motor, -30);
				sleep(1);
				break;
			case 'k':
				TMotor_speedSet( motor, 30);
				sleep(1);
				break;
			case 'J':
				TMotor_speedSet( motor, -60);
				sleep(1);
				break;
			case 'K':
				TMotor_speedSet( motor, 60);
				sleep(1);
				break;
			case 'q':
			case 'Q':
				done=true;
				break;
			default:
				break;
		}
		TMotor_speedSet( motor, 0);

		if (done)
			break;
  }

	ioctl(0, TCSETS, &old_ts);
#endif
  return TELEO_OK;
}

TeleoError valueUpdate ( TMioAin* tmain, float value )
{
  printf( "Knob value %f\n", value );
  TMotor_speedSet( motor, (float)( value+18.75 ) );
  return TELEO_OK;
}

TeleoError positionTargetUpdate ( TMotor* tMotor, int16 positionTarget )
{
  return TELEO_OK;
}
