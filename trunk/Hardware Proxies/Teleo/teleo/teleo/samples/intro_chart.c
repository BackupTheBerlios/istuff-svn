/* Copyright 2003 MakingThings LLC. */

/** \file mini intro chart.c
     Example code showing MioAin and polling
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "TeleoIntroAin.h"
#include "TeleoEasy.h"

#define CHART_COLUMNS  65
#define DEFAULT_MAX    1024
#define DEFAULT_MIN    0

#define SLEEP_MS       100
  
// Device Manager
TeleoDeviceManager* teleoDeviceManager;

// Devices
TIntroAin* sensor;

int main( int argc, char* argv[] ) 
{
  TeleoError teleoError;
  cchar* devicePath;
  
  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  // create and set up the device manager
  if ( TeleoEasy_Init( devicePath, TI_USB, &teleoDeviceManager ) != TELEO_OK )
    exit( 1 );

  // create the device
  teleoError = TIntroAin_Create( teleoDeviceManager, NULL, 0, NULL, &sensor );
  if ( teleoError )
    exit( 1 );

  TeleoEasy_Start();

  printf( "Chart Running\n" );

  while ( 1 )
  {
    int16 value = 0;
    char  line[ CHART_COLUMNS + 1 ];
    char* lP = line;
    uint16 columns;
    
    TeleoEasy_Lock();
    TIntroAin_valueGet( sensor, &value );
    TeleoEasy_Unlock();

    columns = (int)( CHART_COLUMNS * ( value ) / ( 32 ) );
    while( columns-- )
      *lP++ = ' ';
    *lP++ = 'o';
    *lP = 0;

    printf( "\n  %4d | %s", value, line ); 

    TI_SleepMs( SLEEP_MS );
  }
}

