/* Copyright 2003 MakingThings LLC. */

/** \file TeleoModuleManager.h
    Module Manager API.
    Contains the structures, definitions and functions for the Teleo
    Module Manager.  The Module Manager is responsible for receiving
    raw messages from the Teleo Channel Manager and interpretting them
    as messages from Teleo Modules.
*/

//
// TeleoModuleManager.h
//

#ifndef _TELEOMODULEMANAGER_H_
#define _TELEOMODULEMANAGER_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoChannel.h"
#include "TeleoError.h"
#include "TeleoUtil.h"

// MESSAGE TYPE IDENTIFIERS
#define MESSAGE_IDENT              0x20
#define MESSAGE_BUTTON             0x21
#define MESSAGE_DATA               0x22
#define MESSAGE_CONNECT            0x23
#define MESSAGE_CONNECT_CANCEL     0x24
#define MESSAGE_MONITOR            0x25
#define MESSAGE_MONITOR_CANCEL     0x26
#define MESSAGE_CONFIG_LOAD        0x27
#define MESSAGE_CONFIG_SAVE        0x28
#define MESSAGE_CONFIG_RESET       0x29
#define MESSAGE_DATA_REQUEST       0x2A
#define MESSAGE_ADDRESS_CHANGE     0x2B
#define MESSAGE_MONITOR_ALL        0x2C
#define MESSAGE_MONITOR_ALL_CANCEL 0x2D

#define MESSAGE_ERRORREQ           0x40
#define MESSAGE_ECHO               0x41
#define MESSAGE_RESET              0x42
#define MESSAGE_TEST_REQUEST       0x43
#define MESSAGE_TEST               0x44
#define MESSAGE_STATUS_REQUEST     0x45
#define MESSAGE_STATUS             0x46
#define MESSAGE_CAPACITY_WARNING   0x47

#define MESSAGE_IGNORE             0xF0

// OFFSETS TO DIFFERENT FIELDS IN MESSAGE
#define MESSAGE_MONITOR_ADDRESS_OFFSET     0x01
#define MESSAGE_MONITOR_DEVICE_OFFSET      0x02
#define MESSAGE_MONITOR_property_OFFSET    0x03
#define MESSAGE_MONITOR_DATA_TYPE_OFFSET   0x04
#define MESSAGE_MONITOR_DATA_OFFSET        0x05

#define MODULE_CONTROLLER 2

/**
  Teleo Module Manager reference structure.
  This structure exists to permit type safety
  for users of the Teleo Module Manager without
  exposing all the internals to all callers.
 */
typedef struct
{
  uint8 tag;     // Codewarrior does not like empty structures 
} TeleoModuleManager;
 
/**
  Teleo Module Manager - Module reference structure.
  This structure exists to permit type safety
  for users of the Teleo Module Manager without
  exposing the internals to all callers.
 */

typedef struct
{
  uint8 tag;
} TMM_Module;

/** Open a new Module Manager.  The return value will be used in all application initiated communication.
    \param tmm return variable for TeleoModuleManager
    \return TELEO_OK (0) or error as appropriate
  */
TeleoError TMM_Create( TeleoModuleManager** tmm  );

/** Destroy the Module Manager
    \param tmm pointer returned from TMM_open( )
    \return TELEO_OK (0) or error as appropriate
  */
TeleoError TMM_destroy( TeleoModuleManager* tmm );

/** Assigns the external reference used in Module Manager callbacks.
    This is useful in situations where there are several Module Managers running (on multiple
    USB ports, for example) so callbacks do not have to perform a lookup or search operation
    to identify their owners.  A similar scheme operates with Channel and Device Managers's.
    \param tmm pointer returned from TMM_open( )
    \param tmmExt return variable for the manager's external reference
    \return TELEO_OK (0) or error as appropriate
  */
TeleoError TMM_externalReferenceSet( TeleoModuleManager* tmm, void* tmmExt );

/** Add a channel to the Module Manager.  Currently supports only one. 
    \param tmm pointer returned from TMM_open( )
    \param tc new channel
  */
TeleoError TMM_channelAdd( TeleoModuleManager* tmm, void* tc );

/** Find or Create a module.  If a matching module already exists, 
    the existing pointer is returned.  If no module exists and the
    supplied spec (address and type) are complete, a module will
    be created.
    
    At create time, the caller's data structures will not yet be set
    up properly. To avoid race-condition nastiness, the bound callback 
    is not invoked in the case of existing modules, instead the bound 
    flag is set.  The caller then should invoke whatever
    bound( ) callback function is required.
    
    \param tmm TeleoModuleManager
    \param address the module address
    \param type the module type
    \param bound pointer to bound variable  
    \param tmmm return variable for new Module
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleFindCreate( TeleoModuleManager* tmm, cchar* address, cchar* type, bool* bound, TMM_Module** tmmm );

/** Finds the described module.  
    This function will perform wildcard matching - it
    will reply with found modules if the address is left
    under specified.
    \param tmm pointer returned from TMM_open( )
    \param address module's address.  May be NULL.
    \param type module's type.  May be NULL
    \param tmmm return variable for new Module
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleFind( TeleoModuleManager* tmm, cchar* address, cchar* type, TMM_Module** tmmm );

/** Checks to see if a module matches the supplied address/type 
    \param tmm TeleoModuleManager
    \param tmmm TMM Module
    \param address module's address
    \param type module's type - manufacturer dependent
    \param match whether the module's information matches the supplied specification
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleMatch( TeleoModuleManager* tmm, TMM_Module* tmmm, cchar* address, cchar* type, bool* match );

/** Get the module count
    \param tmm TeleoModuleManager
    \param count variable for returning the number of modules available
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleCountGet( TeleoModuleManager* tmm, int* count );

/** Get the module reference by index
    \param tmm TeleoModuleManager
    \param index module index
    \param tmmm variable for holding the module
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleGet( TeleoModuleManager* tmm, int index, TMM_Module** tmmm );

/** Get the module external reference by index
    \param tmm TeleoModuleManager
    \param index module index
    \param tmmmExt variable for holding the module's external reference
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleExternalGetByIndex( TeleoModuleManager* tmm, int index, void** tmmmExt );

/** Get the module reference by module address
    \param tmm TeleoModuleManager
    \param address address of the module being sought
    \param tmmm variable for holding the module
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleGetByAddress( TeleoModuleManager* tmm, cchar* address, TMM_Module** tmmm );

/** Replaces the default module reference with another Application relevant one.
    Importantly, all calls into the Module Manager layer still need to refer
    to the original one.
    \param tmm TeleoModuleManager
    \param tmmm module passed in by (*moduleFound)( )
    \param tmmmExt external reference to be used in callbacks
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleExternalSet( TeleoModuleManager* tmm, TMM_Module* tmmm, void* tmmmExt );

/** Get the module external reference by index
    \param tmm TeleoModuleManager
    \param tmmm TMM_Module
    \param tmmmExt return variable for external reference
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleExternalGet( TeleoModuleManager* tmm, TMM_Module* tmmm, void** tmmmExt );

/** Request module information about a particular module.
    \param tmm TeleoModuleManager
    \param tmmm module reference passed back by moduleFound()
    \param tmmmExt module external reference set by TMM_moduleExternalReferenceSet()
    \param type module's type
    \param address module's address
    \param version_major major part of the version number
    \param version_minor minor part of the version number
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleInfoGet( TeleoModuleManager* tmm, TMM_Module* tmmm, void** tmmmExt, cchar** type, cchar** address, uint8* version_major, uint8* version_minor );

/** Request the module address from a particular module.
    \param tmm TeleoModuleManager
    \param tmmm module reference passed back by moduleFound()
    \param address module's address
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleAddressGet( TeleoModuleManager* tmm, TMM_Module* tmmm, cchar** address );

/** Request the module type from a particular module.
    \param tmm TeleoModuleManager
    \param tmmm module reference passed back by moduleFound()
    \param type module's type
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleTypeGet( TeleoModuleManager* tmm, TMM_Module* tmmm, cchar** type );

/** Request version information from a particular module.
    \param tmm TeleoModuleManager
    \param tmmm module reference passed back by moduleFound()
    \param version_major major part of the version number
    \param version_minor minor part of the version number
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_moduleVersionGet( TeleoModuleManager* tmm, TMM_Module* tmmm, uint8* version_major, uint8* version_minor );

/** Signal to the Module Manager layer that a Module timer event has occured.
    This routine should be called approximately every \a 1000ms.  It is 
    not an error if this is never called, but the system will not notice
    when Modules are lost (unplugged, etc.)
    \param tmm TeleoModuleManager
    \param ms approximate duration of timer interval
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_timerModuleEvent( TeleoModuleManager* tmm, int ms );

/** Set the moduleBound callback 
    \param tmm Teleo Module Manager
    \param moduleBound moduleBound function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_moduleBoundCallbackSet( TeleoModuleManager* tmm, TeleoError (*moduleBound)( TeleoModuleManager* tmm, void* tmmExt, TMM_Module *tmmm, void* tmmmExt, bool bound ) );

/** Set the dataReceive callback 
    \param tmm Teleo Module Manager
    \param dataReceive dataReceive function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_dataReceiveCallbackSet( TeleoModuleManager* tmm, TeleoError (*dataReceive)( TeleoModuleManager* tmm, void* tmmExt, TMM_Module *tmmm, void* tmmmExt, uint8 device, uint8 property, TeleoData* data ) );

/** Set the callback buttonPress
    \param tmm Teleo Module Manager
    \param buttonPress buttonPress function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_buttonPressCallbackSet( TeleoModuleManager* tmm, TeleoError (*buttonPress)( TeleoModuleManager* tmm, void* tmmExt, TMM_Module *tmmm, void* tmmmExt ) );

/** Set the readdressReceive callback 
    \param tmm Teleo Module Manager
    \param readdressReceive readdressReceive function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_readdressReceiveCallbackSet( TeleoModuleManager* tmm, TeleoError (*readdressReceive)( TeleoModuleManager* tmm, void* tmmExt, TMM_Module *tmmm, void* tmmmExt ) );

/** Set the resetReceive callback 
    \param tmm Teleo Module Manager
    \param resetReceive resetReceive function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_resetReceiveCallbackSet( TeleoModuleManager* tmm, TeleoError (*resetReceive)( TeleoModuleManager* tmm, void* tmmExt, TMM_Module *tmmm, void* tmmmExt ) );

/** Set the echoReceive callback 
    \param tmm Teleo Module Manager
    \param echoReceive echoReceive function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_echoReceiveCallbackSet( TeleoModuleManager* tmm, TeleoError (*echoReceive)( TeleoModuleManager* tmm, void* tmmExt, TeleoMessage* message ) );

/** Set the callback addressConflict
    \param tmm Teleo Module Manager
    \param addressConflict addressConflict function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_addressConflictCallbackSet( TeleoModuleManager* tmm, TeleoError (*addressConflict)( TeleoModuleManager* tmm, void* tmmExt, cchar* address ) );

/** Set the unknownMessageReceive callback
    \param tmm Teleo Module Manager
    \param unknownMessageReceive unknownMessageReceive function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_unknownMessageReceiveCallbackSet( TeleoModuleManager* tmm, TeleoError (*unknownMessageReceive)( TeleoModuleManager* tmm, void* tmmExt, TeleoMessage* message ) );

/** Set the messageReceive callback
    \param tmm Teleo Module Manager
    \param messageReceive messageReceive function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_messageReceiveCallbackSet( TeleoModuleManager* tmm, TeleoError (*messageReceive)( TeleoModuleManager* tmm, void* tmmExt, TeleoMessage* message, TMM_Module *tmmm_ ) );

/** Set the capacityWarning callback
    \param tmm Teleo Module Manager
    \param capacityWarning capacityWarning function pointer
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_capacityWarningCallbackSet( TeleoModuleManager* tmm, TeleoError (*capacityWarning)( TeleoModuleManager* tmm, void* tmmExt, TMM_Module *tmmm, void* tmmmExt, bool incoming ) );


/** Sends a packet of data to the module refered to.
    \param tmm Teleo Module Manager
    \param module module reference
    \param device device index
    \param property property index
    \param data TeleoData structure to be sent
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_dataSend( TeleoModuleManager* tmm, TMM_Module* module,  uint8 device, uint8 property, TeleoData* data );

/** Requests the data from the module refered to.  Does not return the
    data immediately since the message has to be sent all the way to the 
    module and back again
    \param tmm pointer returned from TMM_open( )
    \param module module reference
    \param device device index
    \param property property index
    \return TeleoError indicating the success or otherwise of the call
  */
TeleoError TMM_dataRequest( TeleoModuleManager* tmm, TMM_Module* module, uint8 device, uint8 property );

/** Request all module/device/propertys be monitored.  This will result in a data
    message being sent from any module whenever any property value changes
    \param tmm pointer returned from TMM_open( )
    \return TELEO_OK (0) or appropriate error code
*/
TeleoError TMM_monitorAll( TeleoModuleManager* tmm);

/**Request a module/device/property be monitored.  This will result in a data
   message being sent from module whenever the property value changes
    \param tmm pointer returned from TMM_open( )
    \param module module reference
    \param device device index
    \param property property index
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_monitor( TeleoModuleManager* tmm, TMM_Module* module, uint8 device, uint8 property );

/**Request a module/device/property be directly connected to another.  Whenever
    the value changes on the from (source) property, the new value is 
    sent to the to (destination) property.
    \param tmm pointer returned from TMM_open( )
    \param fromModule \e from module reference
    \param fromDevice \e from device index
    \param fromProperty \e from property index
    \param toModule \e to module reference
    \param toDevice \e to device index
    \param toProperty \e to property index
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_connect( TeleoModuleManager* tmm, TMM_Module* fromModule, uint8 fromDevice, uint8 fromProperty, TMM_Module* toModule, uint8 toDevice, uint8 toProperty );

/** Request a module/device/property be disconnected from another one.
    \param tmm pointer returned from TMM_open( )
    \param fromModule \e from module reference
    \param fromDevice \e from device index
    \param fromProperty \e from property index
    \param toModule \e to module reference
    \param toDevice \e to device index
    \param toProperty \e to property index
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_disconnect( TeleoModuleManager* tmm, TMM_Module* fromModule, uint8 fromDevice, uint8 fromProperty, TMM_Module* toModule, uint8 toDevice, uint8 toProperty  );

/** Broadcasts a new address.  Someone must have placed a module into the re-addressing mode
    by pressing its pushbutton for >3s for this to work.
    \param tmm pointer returned from TMM_open( )
    \param addressNew address the module will now assume
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_addressAssert( TeleoModuleManager* tmm, cchar* addressNew );

/** Requests a module save its configuration 
    \param tmm  pointer returned from TMM_open( )
    \param module module to save or NULL for all modules
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_configSave( TeleoModuleManager* tmm, TMM_Module* module );

/** Requests a module load its configuration 
    \param tmm pointer returned from TMM_open( )
    \param module module to save or NULL for all modules
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_configLoad( TeleoModuleManager* tmm, TMM_Module* module );

/** Requests a module reset its configuration 
    \param tmm pointer returned from TMM_open( )
    \param module module to save or NULL for all modules
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_configReset( TeleoModuleManager* tmm, TMM_Module* module );

/** Requests an echo packet be sent to the specified module
    \param tmm pointer returned from TMM_open( )
    \param module receiving module
    \param messageLength number of bytes to send
    \param message actual value to echo
    \param reliable whether the message should be sent using the reliable protocol
    \return TELEO_OK (0) or appropriate error code
  */
TeleoError TMM_echoRequest( TeleoModuleManager* tmm, TMM_Module* module, uint16 messageLength, char* message, bool reliable );

/** Requests the current size of the Message Manager's send queue.  Handy for detecting 
    excessive data transmission.
    \param tmm pointer returned from TMM_open( )
    \param size return variable for queue size
    \return TELEO_OK (0) or appropriate error code
 */
TeleoError TMM_sendQueueSizeGet( TeleoModuleManager* tmm, int* size );
    
#ifdef __cplusplus
}
#endif

#endif
