/* Copyright 2003 MakingThings LLC. */

/** \file TeleoDeviceManager.h
    Device Manager API.
    Contains the structures, definitions and functions for the Teleo
    Device Manager.  The Device Manager is responsible for maintaining
    references to devices. Devices can be created at any time for future
    binding to modules. The Device Manager receives messages from the 
    Module Manager - concerning module appearance and disappearance, data
    etc. and presents them as device data.
 */

//
// TeleoDeviceManager.h
//

// TODO: 
// Need data type conversion routines like
//   int TeleoDataIntGet( TeleoData* ); etc.

#ifndef _TELEODEVICEMANAGER_H_
#define _TELEODEVICEMANAGER_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoModuleManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"

/**
  Teleo Device Manager reference structure.
  This structure exists to permit type safety
  for users of the Teleo Device Manager without
  exposing all the internals to all callers.
 */

typedef struct
{
  uint8 tag;
} TeleoDeviceManager;
  
/**
  Teleo Device Manager Device reference structure.
  This structure exists to permit type safety
  for users of the Device without
  exposing all the internals to all callers.
 */

typedef struct
{
  uint8 tag;
} TDM_Device;

/**
  Teleo Device Manager Module reference structure.
  This structure exists to permit type safety
  for users of the Module without
  exposing all the internals to all callers.
 */

typedef struct
{
  uint8 tag;
} TDM_Module;

/** Make a new Teleo Device Manager.
    There are two more things that need to be done before the Device Manager will work
    correctly: a completely set-up Module Manager needs to be set into the Device Manager and
    any callbacks that are important need to be set up.  See TeleoDeviceLinux.c for an example.
    @param tdm variable to receive the new TeleoDeviceManager
    @return TELEO_OK (0) or appropriate error code
 */
TeleoError TDM_Create( TeleoDeviceManager** tdm );

/** Destroy a Teleo Device Manager.
    @param tdm Teleo Device Manager
    @return TELEO_OK (0) or appropriate error code
 */
TeleoError TDM_destroy( TeleoDeviceManager* tdm );

/** Set the external reference.
    This is useful in situations where there are several Devices running 
    so callbacks do not have to perform a lookup or search operation
    to identify their owners
    @param tdm Teleo Device Manager
    @param tdmExt void* that the Device will use to communicate with the application
    @return TELEO_OK (0) or appropriate error code
 */
TeleoError TDM_externalReferenceSet( TeleoDeviceManager* tdm, void* tdmExt );

/** Set the function to be called when a device is bound
    @param tdm the Teleo Device Manager
    @param deviceBound the bound callback function
    @return TELEO_OK (0) or an error code
 */
TeleoError TDM_deviceBoundCallbackSet( TeleoDeviceManager* tdm, TeleoError (*deviceBound)( TeleoDeviceManager* tdm, void* tdmExt, TDM_Device* tdmd, void* tdmdExt, bool bound ) );

/** Set the function to be called when a device property is updated
    @param tdm the Teleo Device Manager
    @param propertyUpdate propertyUpdate callback function
    @return TELEO_OK (0) or an error code
 */
TeleoError TDM_propertyUpdateCallbackSet( TeleoDeviceManager* tdm, TeleoError (*propertyUpdate)( TeleoDeviceManager* tdm, void* tdmExt, TDM_Device* tdmd, void* tdmdExt, uint8 propertyIndex, TeleoData* data ) );

/** Add a ModuleManager to the Device Manager.
    @param tdm pointer returned from TDM_open( )
    @param tmm the module manager
    @return TELEO_OK (0) or appropriate error code
 */
TeleoError TDM_moduleManagerSet( TeleoDeviceManager* tdm, TeleoModuleManager* tmm );

/** Request that all inputs be monitored
    @param tdm pointer returned from TDM_open( )
    @return TELEO_OK (0) or appropriate error code
 */
TeleoError TDM_monitorAll( TeleoDeviceManager* tdm );

/** Create a new device.
    Create a device corresponding to the device index supplied
    on the module that fits the specification.  
    
    The idea is that the module that is wanted can be specified as tightly
    as is necessary. You can create devices as they are needed
    in your application without concern for the presence
    or absence of the corresponding module.  
    
    If the device is specified precisely, the Module Manager will permit
    communication to begin before the module is bound, so
    in this case be prepared to receive data callbacks immediately 
    even before receiving the bound callback.
    
    If the module was already bound when the device was created, this 
    presents another challenge - this device will not receive a Bound 
    messsage.  In this case the caller has to perform the requisite 
    bound( ) callback functions.
    
    @param tdm Teleo Device Manager
    @param tdmdExt External Reference used in callbacks
    @param device device on the Module to bind to
    @param address module address
    @param type module type
    @param bound pointer to a bound variable
    @param tdmd return value for the new device (TDM_Device).
    @return TELEO_OK (0) or appropriate error
  */
TeleoError TDM_deviceCreate( TeleoDeviceManager* tdm, void* tdmdExt, uint8 device, cchar* address, cchar* type, bool* bound, TDM_Device** tdmd );

/** Deletes the device.
 */
TeleoError TDM_deviceDestroy( TeleoDeviceManager* tdm, TDM_Device* tdmd );

/** Set the function to be called when the device is bound
    @param tdmd the Teleo Device
    @param bound the bound callback function
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_boundCallbackSet( TDM_Device* tdmd, TeleoError (*bound)( TDM_Device* tdmd, void* tdmdExt, bool bound ) );

/** Set the function to be called when a device property is updated
    @param tdmd the Teleo Device
    @param propertyUpdate the propertyUpdate callback function
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyUpdateCallbackSet( TDM_Device* tdmd, TeleoError (*propertyUpdate)( TDM_Device* tdmd, void* tdmdExt, uint8 propertyIndex, TeleoData* data ) );

/** Set the external reference.
    @param tdmd the Teleo Device
    @param tdmdExt void* that the Device will use to communicate with the application
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_externalReferenceSet( TDM_Device* tdmd, void* tdmdExt );

/** Checks if the Device is bound or not.
    @param tdmd the Teleo Device
    @param bound variable for holding the return value
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_boundGet( TDM_Device* tdmd, bool* bound );

/** Returns the bound module
    @param tdmd Device
    @param tmmm return variable for the module 
    @return TELEO_OK (0) or an error code
  */
TeleoError TDMD_moduleBoundGet( TDM_Device* tdmd, TMM_Module** tmmm );
      
/** Sets the specified device property. 
    When a module is bound, this will result in sending the 
    data all the way down to the module itself. 
    @param tdmd the Teleo Device
    @param propertyIndex the index of the property
    @param data the new data
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertySet( TDM_Device* tdmd, uint8 propertyIndex, TeleoData* data );

/** Gets the specified device property.  Provided that the property is 
    being monitored, this will be the latest value received by the system.
    This means that this call will return immediately, not after a request
    for the data is sent down to the module and comes all the way back. 
    Note that the data will be copied into the provided TeleoData structure.
    @param tdmd the Teleo Device
    @param propertyIndex the index of the property
    @param data the new data
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyGet( TDM_Device* tdmd, uint8 propertyIndex, TeleoData* data );

/** Requests the specified device property be monitored.  
    Thereafter, every time
    the data changes, the value will be sent to this device.
    @param tdmd the Teleo Device
    @param propertyIndex the index of the property
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyMonitor( TDM_Device* tdmd, uint8 propertyIndex );

/** Requests the specified device property be obtained from the network.
    This is useful because sometimes values change very slowly, so the 
    method of relying on updates being sent wouldn't work.
    @param tdmd the Teleo Device
    @param propertyIndex the index of the property
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyRequest( TDM_Device* tdmd, uint8 propertyIndex );

/** Connects two properties.
    Causes the two device / properties to be connected at the lowest level 
    possible in the system.  This will result in a very efficient connection.
    @param tdmd the source Teleo Device
    @param propertyIndex the index of the source property
    @param toTDMD the destination Teleo Device
    @param toPropertyIndex the index of the destination property
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyConnect( TDM_Device* tdmd, uint8 propertyIndex, TDM_Device* toTDMD, uint8 toPropertyIndex );

/** Disconnects two properties.
    @param tdmd the source Teleo Device
    @param propertyIndex the index of the source property
    @param toTDMD the destination Teleo Device
    @param toPropertyIndex the index of the destination property
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyDisconnect( TDM_Device* tdmd, uint8 propertyIndex, TDM_Device* toTDMD, uint8 toPropertyIndex );

/** Requests the specified device be monitored.  
    Thereafter, every time the data changes, the value will be sent to this device.
    @param tdmd the Teleo Device
    @return TELEO_OK (0) or an error code
 */
TeleoError TDMD_propertyMonitorAll( TDM_Device* tdmd );

#ifdef __cplusplus
}
#endif

#endif
