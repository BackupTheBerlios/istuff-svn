/* Copyright 2003 MakingThings LLC. */

/** \file TeleoEasyMacosX.c
     Sets up the Teleo SDK under MacosX.
     Illustrates the connection of all the 
     layers of the SDK for MacosX. Used in several example
     apps.
     
     Uses pthreads internally to achieve multithreaded IO.
 */

#include <stdio.h>

#include "TeleoEasy.h"
#include "TeleoInterface.h"
#include "TeleoDeviceManager.h"
  
#define EVENT_TIME 10

// Thread stuff
#include <pthread.h>

// 
// Locals
//

/** Function provided to the input thread to call back into the
    channel when characters arrive.
 */
static void* doInput( void* data );

/** Function provided to the timer thread to call back into the
    channel at the appropriate intervals.
 */
static void* doTimer( void* data );

// TeleoChannel SystemCallbacks
/** Function provided to the timer thread to call back into the
    channel at the appropriate intervals.
 */
static TeleoError output( TeleoChannel* tc, uint8* c, uint8 count );

// TeleoDeviceManagerDevice Callbacks
static void deviceBound( void* tdmdExt, bool bound );
static void devicePropertyUpdate( void* tdmdExt, uint8 propertyIndex, TeleoData* data );

/// Reference to the Module Manager
static TeleoDeviceManager* teleoDeviceManager;
/// Reference to the Module Manager
static TeleoModuleManager* teleoModuleManager;
/// Reference to the Channel
static TeleoChannel* teleoChannel;

static TeleoInterface* teleoInterface;
static pthread_t teleoInputThread;
static pthread_t teleoTimerThread;
static pthread_mutex_t teleoThreadMutex;

TeleoError TeleoEasy_Init( cchar* interfaceName, TI_InterfaceType interfaceTypeId, TeleoDeviceManager** tdm )
{
  uint8 c;

  cchar* interfaceType;
  TeleoError teleoError;

  *tdm = NULL;

  // Create the Interface
  if ( ( teleoError = TI_Create( NULL, 
                                 interfaceTypeId, 
                                 &teleoInterface ) ) != TELEO_OK )
  {
    // printf("TI_Create failed\n");
    return teleoError;
  }

  TI_blockingSet( teleoInterface, true );
  TI_typeGet(teleoInterface, &interfaceType );
  teleoError = TI_open( teleoInterface );
  if (teleoError) 
  {
    //printf("TI_open failed, TeleoError %d\n", teleoError);
    return(teleoError);
  }
  
  // Create the channel
  if ( ( teleoError = TC_Create( &teleoChannel ) ) != TELEO_OK )
    return teleoError;
  TC_channelNameSet( teleoChannel, interfaceType );
  TC_sendQueueEnable( teleoChannel, true );
  // Set up the channel's system callbacks
  TC_outputCallbackSet( teleoChannel, output );
  
  // Create the Module Manager
  if ( ( teleoError = TMM_Create( &teleoModuleManager ) ) != TELEO_OK )
    return teleoError;
  // Add the channel to the module manager
  TMM_channelAdd( teleoModuleManager, teleoChannel ); 
  
  // Create the device manager
  if ( ( teleoError = TDM_Create( &teleoDeviceManager ) ) != TELEO_OK )
    return teleoError;
  // Set up the device manager's callbacks
  //   tdmCallbacks = TDM_callbacksGet( teleoDeviceManager );
  //   we're not using any here
  // Add the module manager to the device manager
  TDM_moduleManagerSet( teleoDeviceManager, teleoModuleManager );

  // Coax the module out of ASCII mode if it's in it!
  TC_dummySend( teleoChannel );

  *tdm = teleoDeviceManager;
  return TELEO_OK;
}

TeleoError TeleoEasy_InterfaceAdd( cchar* interfaceName, TI_InterfaceType interfaceTypeId )
{
  return TELEO_E_UNIMPLEMENTED;
}


TeleoModuleManager* TeleoEasy_TeleoModuleManagerGet( )
{
  return teleoModuleManager;
}

void TeleoEasy_Start()
{
  // Create the mutex
  pthread_mutex_init( &teleoThreadMutex, NULL );
  // Fire up the input thread
  pthread_create( &teleoInputThread, NULL, doInput, NULL );   
  // Fire up the timer thread
  pthread_create( &teleoTimerThread, NULL, doTimer, NULL );   
}

void TeleoEasy_Continue()
{
  pthread_join( teleoInputThread, NULL );
  pthread_join( teleoTimerThread, NULL );
  pthread_mutex_destroy( &teleoThreadMutex );
}

void* doTimer( void *data )
{
  uint8 c;

  while( true )
  {
    TeleoEasy_Lock();
    TC_timerEvent( teleoChannel, EVENT_TIME );
    TMM_timerModuleEvent( teleoModuleManager, EVENT_TIME );
    TeleoEasy_Unlock();

    usleep( EVENT_TIME * 1000 );
  }
}

void* doInput( void* data )
{
  uint8 c;

    // see what characters there are ready to look at
  while ( 1 )
  {
    if ( TI_get( teleoInterface, &c, 1 ) == TELEO_OK )
    {
      //printf( "%d ", c );
      TeleoEasy_Lock();
      TC_input( teleoChannel, c );
      TeleoEasy_Unlock();
    }
  }
  return NULL;
}

void TeleoEasy_Lock()
{
  pthread_mutex_lock( &teleoThreadMutex );
}

void TeleoEasy_Unlock()
{
  pthread_mutex_unlock( &teleoThreadMutex );
}

//
// Callbacks - will be called by the Channel
//
TeleoError output( TeleoChannel* tc, uint8* c, uint8 count )
{
  return TI_put( teleoInterface, c, count );  
}
