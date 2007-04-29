/* Copyright 2003 MakingThings LLC. */

/** \file TeleoModuleLinux.c
     Sets up the Teleo SDK under Linux.
     Illustrates the connection of the lower 
     layers of the SDK for Linux. Used in several
     example apps.  See TeleoModuleTest.c
    
     Sets up a Channel Manager and a Module Manager.
     Reports modules, incoming messages, button presses, etc.
     Also runs threads for timer and input.
     
     Uses pthreads.
 */
 
#include "stdio.h"
#include "TeleoModule.h"
#include "TeleoModuleManager.h"
#include "TeleoInterface.h"

// for scandir
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>

#define EVENT_TIME 10

// Thread stuff
#include <pthread.h>

// Locals                            
/** Function provided to the timer thread to call back into the
    channel manager when the correct interval has elapsed
 */
void* doTimer( void* data );
/** Function provided to the input thread to call back into the
    channel manager when characters arrive.
 */
void* doInput( void* data );

// TeleoChannel Callbacks
/** Send the specified characters.
    Low level callback function from the TeleoChannel
 */
TeleoError output( TeleoChannel* tc, uint8* c, uint8 count );
/** Turn the timer on or off.
    Low level callback function from the TeleoChannel
 */
TeleoError timerRequest( TeleoChannel* tc, bool enable );

// TeleoChannel Device Finder
/** Function to find the device representing the Teleo USB Translator
 */
static TeleoError TI_FindUsbSerialDevice(char* dest, int destLen);

// routine used to select matches in scandir
/** Function to return true if an individual directory entry
    should be selected; returns false otherwise
  */
int  matchUsbSerialDevice (struct dirent * thisun);

TeleoModuleManager* teleoModuleManager;
TeleoChannel* teleoChannel;
TeleoInterface* teleoInterface;

// Threads
pthread_t teleoInputThread;
pthread_t teleoTimerThread;
pthread_mutex_t teleoThreadMutex;

#define DEVICE_NAME_MAX_LEN 80

TeleoError TeleoModule_Init( cchar* interfaceName, TI_InterfaceType interfaceType, TeleoModuleManager** tmm )
{
  uint8 c;
  TeleoData data;
  TMM_Module* mioTest;
  TeleoError teleoError;
  cchar* channelName;
  char usbSerialDeviceName[DEVICE_NAME_MAX_LEN];

  *tmm = NULL;

	// Find the USB serial device

  // first prepend the path to the device directory
  sprintf( usbSerialDeviceName, "%s", "/dev/");

  // next find the device itself and append that
  if ( ( teleoError = 
           TI_FindUsbSerialDevice(usbSerialDeviceName+strlen("/dev/"), 
                                  DEVICE_NAME_MAX_LEN ) ) != TELEO_OK )
  {
    // printf("Failed to find Teleo USB Serial device\n");
    return teleoError;
  }

  // Create the Interface
  if ( ( teleoError = TI_Create( usbSerialDeviceName, 
			interfaceType, 
			&teleoInterface ) ) != TELEO_OK )
       return teleoError;
  TI_blockingSet( teleoInterface, true );
  TI_typeGet(teleoInterface, &channelName );
  TI_open( teleoInterface );
  
  // Open the channel
  if ( ( teleoError = TC_Create( &teleoChannel ) ) != TELEO_OK )
    return teleoError;
  TC_channelNameSet( teleoChannel, channelName );
  TC_sendQueueEnable( teleoChannel, true );
  
  // set up the channel's system callbacks
  TC_outputCallbackSet( teleoChannel, &output );  
  TC_timerRequestCallbackSet( teleoChannel, &timerRequest );  
  
  // Open the session
  if ( ( teleoError = TMM_Create( &teleoModuleManager ) ) != TELEO_OK )
    return teleoError;  
  // Add the channel to the session
  TMM_channelAdd( teleoModuleManager, teleoChannel );

    
  *tmm = teleoModuleManager;
  return TELEO_OK;
}

void TeleoModule_Start()
{
  // Fire up the input thread
  pthread_create( &teleoInputThread, NULL, doInput, NULL );   
  // Fire up the timer thread
  pthread_create( &teleoTimerThread, NULL, doTimer, NULL );   
  // Create the mutex
  pthread_mutex_init( &teleoThreadMutex, NULL );
}
  
void TeleoModule_Continue()
{
  pthread_join( teleoInputThread, NULL );
  pthread_join( teleoTimerThread, NULL );
  pthread_mutex_destroy( &teleoThreadMutex );
}


void* doInput( void *data )
{  
  uint8 c;

  while ( true )
  {
    if ( TI_get( teleoInterface, &c, 1 ) == TELEO_OK )
    {
      TeleoModule_Lock( );
      TC_input( teleoChannel, c );
      TeleoModule_Unlock( );
    }
  }
}

void* doTimer( void* data )
{
  while ( true )
  {
    TeleoModule_Lock( );
    TC_timerEvent( teleoChannel, EVENT_TIME );
    TMM_timerModuleEvent(teleoModuleManager, EVENT_TIME );
    TeleoModule_Unlock();
    usleep( EVENT_TIME * 1000 );
  }
}

TeleoError output( TeleoChannel* tc, uint8* c, uint8 count )
{
  return TI_put( teleoInterface, c, count );  
}


TeleoError timerRequest( TeleoChannel* tc, bool timer )
{
  //printf( "Network Session : Unknown Message Receive\n" );
  return TELEO_OK;
}

/** Locks access to the library
  */
void TeleoModule_Lock()
{
  pthread_mutex_lock( &teleoThreadMutex );
}

/** Locks access to the library
  */
void TeleoModule_Unlock()
{
  pthread_mutex_unlock( &teleoThreadMutex );
}

static TeleoError TI_FindUsbSerialDevice(char* dest, int destLen)
{
	struct dirent **namelist;
	int n;

	n = scandir("/dev", &namelist, matchUsbSerialDevice, NULL);
	if (n < 0)
	{
		perror("scandir");
		return(TELEO_E_UNKNOWN);
	}
	if (n > 1)
	{
		// printf("more than one Teleo USB Serial device found, returning first\n");
	}
	strncpy(dest, namelist[0]->d_name, destLen);
	free(namelist[n]);
	free(namelist);
	return(TELEO_OK);
}

int  matchUsbSerialDevice (struct dirent * thisun)
{
	if (strncmp("tty.usbserial-", thisun->d_name, strlen("tty.usbserial-")))
		return 0;
	else
		return 1;
}
