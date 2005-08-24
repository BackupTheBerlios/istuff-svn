/* Copyright 2003 MakingThings LLC. */

/** \file TeleoModuleTest.c
    Module Manager Test Program.
    Sets up a Channel Manager and a Module Manager.
    Reports modules, incoming messages, button presses, etc.
    Also runs a OS timer for Module and Channel events.
 */

#include <stdio.h>
#include <stdlib.h>
#include "TeleoModule.h"

// TeleoModuleManager Callbacks
TeleoError moduleBound( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt, bool bound );
TeleoError moduleLost( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt );
TeleoError dataReceive( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt, uint8 device, uint8 port, TeleoData* data );
TeleoError buttonPress( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt );
TeleoError unknownMessageReceive( TeleoModuleManager* tmm, void* tmmExt, TeleoMessage* message );
TeleoError resetReceive( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt );
TeleoError echoReceive( TeleoModuleManager* tmm, void* tmmExt, TeleoMessage* message );
TeleoError capacityWarning( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt, bool incoming );
TeleoError addressConflict( TeleoModuleManager* tmm, void* tmmExt, cchar* address );

TeleoModuleManager* teleoModuleManager;

int main( int argc, char* argv[] ) 
{
  TMM_Module* mioTest;
  cchar* devicePath;
  
  if ( argc == 2 )
    devicePath = argv[ 1 ];
  else
    devicePath = NULL;

  if ( TeleoModule_Init( devicePath, TI_USB, &teleoModuleManager ) != TELEO_OK )
  {
    exit( 1 );
  }

  // Set the callbacks up
  TMM_moduleBoundCallbackSet( teleoModuleManager, moduleBound );
  TMM_buttonPressCallbackSet( teleoModuleManager, buttonPress );
  TMM_dataReceiveCallbackSet( teleoModuleManager, dataReceive );
  TMM_echoReceiveCallbackSet( teleoModuleManager, echoReceive );
  TMM_resetReceiveCallbackSet( teleoModuleManager, resetReceive );
  TMM_addressConflictCallbackSet( teleoModuleManager, addressConflict );
  TMM_capacityWarningCallbackSet( teleoModuleManager, capacityWarning );
  TMM_unknownMessageReceiveCallbackSet( teleoModuleManager, unknownMessageReceive );
  
  TMM_moduleFindCreate( teleoModuleManager, "3", "3", NULL, &mioTest );
  
  TeleoModule_Start();
  
  // Send the request to monitor all the properties of all the devices
  TMM_monitorAll( teleoModuleManager );

  TeleoModule_Continue();

  return TELEO_OK;
}
  
TeleoError moduleBound( TeleoModuleManager* tmm, void* tmmExt, TMM_Module* tmmm, void* tmmmExt, bool bound )
{
  cchar* type;
  cchar* address;
  uint8 version_major;
  uint8 version_minor;

  TMM_monitorAll( teleoModuleManager );

  TMM_moduleInfoGet( teleoModuleManager, tmmm, NULL, &type, &address, &version_major, &version_minor );
                                     
  if ( bound )
    printf( "Found : Address %s Type %s Version %d.%d \r\n", address, type, version_major, version_minor );
  else  
    printf( "Lost : Address %s Type %s Version %d.%d \r\n", address, type, version_major, version_minor );

  return TELEO_OK;
}

TeleoError dataReceive( TeleoModuleManager* tcm, void* tcmExt, TMM_Module* tmmm, void* tmmmExt, uint8 device, uint8 port, TeleoData* data )
{
  cchar* address;

  TMM_moduleInfoGet( teleoModuleManager, tmmm, NULL, NULL, &address, NULL, NULL );
  
  printf( "Module Manager : %s.%d.%d Data ", address, device, port );

  switch ( data->datatype )
  {
    case MESSAGE_DATATYPE_EVENT:
      printf( " Event!" );
      break;
    case MESSAGE_DATATYPE_BOOL:
      printf( " %d", data->data.b );
      break;
    case MESSAGE_DATATYPE_SMALLINT:
      printf( " %d", data->data.si );
      break;
    case MESSAGE_DATATYPE_INT:
      printf( " %d", data->data.i );
      break;
    case MESSAGE_DATATYPE_FLOAT:
      printf( " %f", (double)data->data.f  );
      break;
    case MESSAGE_DATATYPE_STRING:
      printf( " %s", data->data.s  );
      break;
  }

  printf( "\r\n" );

  if ( data->datatype == MESSAGE_DATATYPE_FLOAT )
  {
    if ( device == 0 && port == 0 )
    {
      data->data.f =  ( data->data.f < 0.0 ) ? -data->data.f : data->data.f;

      TMM_dataSend( teleoModuleManager, tmmm, 12, 0, data );
    }
  }

  return TELEO_OK;
}

TeleoError buttonPress( TeleoModuleManager* tcm, void* tcmExt, TMM_Module* tmmm, void* tmmmExt )
{
  cchar* address;
  TMM_moduleInfoGet( teleoModuleManager, tmmm, NULL, NULL, &address, NULL, NULL );
  
  printf( "Module Manager : Button %s\r\n", address );

  return TELEO_OK;
}

TeleoError resetReceive( TeleoModuleManager* tcm, void* tcmExt, TMM_Module* tmmm, void* tmmmExt  )
{
  cchar* address;
  TMM_moduleInfoGet( teleoModuleManager, tmmm, NULL, NULL, &address, NULL, NULL );
  
  printf( "Module Manager : Module %s Reset\r\n", address );
  
  return TELEO_OK;
}

TeleoError echoReceive( TeleoModuleManager* tcm, void* tcmExt, TeleoMessage *message )
{
  printf( "Module Manager : Module Echo Received\r\n" );
  
  return TELEO_OK;
}

TeleoError capacityWarning( TeleoModuleManager* tcm, void* tcmExt, TMM_Module* tmmm, void* tmmmExt, bool incoming )
{
  cchar* address;
  TMM_moduleInfoGet( teleoModuleManager, tmmm, NULL, NULL, &address, NULL, NULL );
  
  printf( "Module Manager : %s CAPACITY WARNING on %s\n", ( incoming ? "INCOMING" : "OUTGOING" ), address );

  return TELEO_OK;
}

TeleoError addressConflict( TeleoModuleManager* tmm, void* tmmExt, cchar* address )
{
  printf( "Module Manager : Address Conflict @ %s\n", address );
  
  return TELEO_OK;
}

TeleoError unknownMessageReceive( TeleoModuleManager* tcm, void* tcmExt, TeleoMessage* message )
{
  printf( "Module Manager : Unknown Message Receive\n" );
   
  return TELEO_OK;
}


