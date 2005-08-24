/* Copyright 2003 MakingThings LLC. */

/** \file TeleoChannelTest.c
    Channel Manager Test Program.
    Sets a Channel Manager up and reports 
    incoming messages to the console.  Also
    includes a thread to perform timer events
    used by the Channel Manager.
    
    Note the use of the mutex to prevent the two threads
    from accessing the data at the same time.
 */

#include "stdio.h"
#include "TeleoChannel.h"
#include "TeleoInterface.h"

#include <stdio.h>
#include <stdlib.h>

// thread stuff
#include <pthread.h>

#define EVENT_TIME 10

// Globals
TeleoInterface* teleoInterface;
static pthread_t teleoTimerThread;
static pthread_mutex_t teleoThreadMutex;

// Locals
/** Function provided to the timer thread to call back into the
    channel manager at the appropriate intervals.
 */
static void* doTimer( void *data );

// TeleoChannel System Callbacks
static TeleoError output( TeleoChannel* tc, uint8* c, uint8 count );
static TeleoError timerRequest( TeleoChannel* tc, bool enable );
static TeleoError receive( TeleoChannel* tc, void* tcExt, TeleoMessage *message );

TeleoChannel* teleoChannel;

int main( int argc, char** argv )
{
  cchar* interfaceType;
  cchar* devicePath;
  uint8 c;

  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  printf( "RUNNING\r\n" );

  // Get the interface open
  if ( TI_Create( devicePath, TI_SERIAL, &teleoInterface ) != TELEO_OK )
    exit( 1 );
  TI_typeGet( teleoInterface, &interfaceType );
  TI_blockingSet( teleoInterface, true );
  TI_open( teleoInterface );
  printf( "OPEN %s\r\n", interfaceType );
  
  // Create the Channel Manager
  if ( TC_Create( &teleoChannel ) != TELEO_OK )
    exit( 1 );

  TC_sendQueueEnable( teleoChannel, true );

  // assign the callbacks
  TC_receiveCallbackSet( teleoChannel, receive );  

  // assign the system callbacks
  TC_outputCallbackSet( teleoChannel, &output );  
  TC_timerRequestCallbackSet( teleoChannel, &timerRequest );  
  
  // Fire up the timer thread, prep the mutex
  pthread_create( &teleoTimerThread, NULL, doTimer, NULL );
  pthread_mutex_init( &teleoThreadMutex, NULL );

  TC_dummySend( teleoChannel );

  while ( 1 )
  {
    while ( TI_get( teleoInterface, &c, 1 ) == TELEO_OK )
    {
      pthread_mutex_lock( &teleoThreadMutex );
      TC_input( teleoChannel, c );
      pthread_mutex_unlock( &teleoThreadMutex );
    }
  }

  return 0;
}

void* doTimer( void *data )
{
  while( true )
  {
    pthread_mutex_lock( &teleoThreadMutex );
    TC_timerEvent( teleoChannel, EVENT_TIME );
    pthread_mutex_unlock( &teleoThreadMutex );
    TI_SleepMs( EVENT_TIME );
  }
}

TeleoError output( TeleoChannel* outer, uint8* c, uint8 count )
{
  if ( TI_put(teleoInterface, c, count ) == TELEO_OK )
  {
    printf( " OUT:" );
    while ( count > 0 )
    {
      printf( "%02x ", *c++ );
      count--;
    }
    printf( "\r\n" );

    return TELEO_OK;
  }
  else
    return TELEO_E_IO;

}

TeleoError receive( TeleoChannel* tc, void* tcExt, TeleoMessage *message )
{
  int i;

  printf( "MESSAGE %02x:", message->address );
  for ( i = 0; i < message->count; i++ )
  {
    printf( " %02x", message->data[ i ] );
  }
  printf( "\r\n" );

  return TELEO_OK;
}

TeleoError timerRequest( TeleoChannel* tc, bool enable )
{
  // printf( "Switch Timer %s\n", ( enable ) ? "ON" : "OFF" );
  return TELEO_OK;
}
