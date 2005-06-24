/* Copyright 2003 MakingThings LLC. */

/** \file TeleoChannel.h
    Channel API.
    Contains the structures, definitions and functions for the Teleo
    Channel.  
    
    The Channel is responsible for receiving
    raw characters from the OS, which involves parsing and checking them
    and packaging them up as messages.  The Channel also converts 
    messages into raw character streams and sends them out to the OS.
    
    Unlike the other layers of the Teleo API, the Channel has two
    callback structures - one similar to that of the Module Manager and the
    Device Manager and one System structure used for making callbacks into 
    the lower level functions of the interface.
    
    The code is designed to function with or without a rapid (i.e. 10ms) 
    timer callback.  If the application can provide this service, there
    are benefits for the incoming and outgoing functionality.  One problem
    with a character driven parser is if characters are dropped, the parser
    can sit waiting for them until the next packet is started.  The first few 
    bytes of the next packet cause the parser to detect the error.  But 
    unfortunately the next message is lost.  The timer helps by noting 
    when the parser has been sitting for a while and reseting it.  The timers
    help with outgoing messages (providing the send message queue is enabled)
    by providing a re-try mechanism in the case of a message failing to be sent. 
    If neither of these things are important the timer can be left unimplemented.
 */

/** \mainpage Teleo Application SDK
 
   \section Introduction
   
   The Teleo Application SDK was written to provide a way for application 
   programmers to interact with Teleo hardware.
   
   The SDK is layered to allow users to have access as close to the hardware
   as necessary, and also to provide useful high level abstractions.
      
   \section TC Teleo Channel
   
   At the lowest level, the Teleo Channel (abbreviated \e TC) deals
   with character streams to and from the hardware.  It converts these streams
   into incoming and outgoing messages.  See the API in TeleoChannel.h
   
   Each application that uses the SDK has to create a Channel and 
   provide it with incoming characters.  This permits the application to
   determine exactly how that is done.  See TeleoChannelTest.c for example code.
   
   \section TMM Teleo Module Manager
   
   At the next level, the Teleo Module Manager (abbreviated \e TMM) sends and
   receives messages from the Teleo Channel.  This layer knows about
   modules and all the messages they can send and receive like data messages, 
   notifications of button presses, resets, etc.  See the API in TeleoModuleManager.h.
   
   An application that uses a Module Manager first needs to create and set up a 
   Channel to handle the incoming and outgoing characters, then a Module
   Manager can be created and set up and passed in the Channel so it can 
   hook into the Channel's message facilities.  See TeleoModuleTest.c for
   example code.
   
   \section TDM Teleo Device Manager
   
   At the next level is the Teleo Device Manager (abbreviated \e TDM).  This 
   subsystem provides the Teleo Device abstraction.  It first permits the application
   to create Teleo Device objects each of which will correspond to a single device
   on a module, then it receives module-oriented messages from its Module Manager and passes
   these on to the application.  See the API in TeleoDeviceManager.h.
   
   An application that uses a Device Manager first needs to create and set up a 
   Channel to handle the incoming and outgoing characters, then a Device
   Manager can be created and set up and passed in the Channel so it can 
   hook into the Channel's message facilities.  There is no need for the application
   to create a Module Manager, this is done internally in the Device Manager initialization
   code. See TeleoDeviceTest.c for example code.
 
   \section ToDo To Do
   
   It might be nice to have a better (more fine grained) thread locking scheme.  The ideal scheme
   would hide locking and unlocking where it is needed in the various SDK function calls.
   
   More effort needs to be expended working through any threading issues.
   
   The Module Manager can currently only accomodate one Channel.  The API is
   designed to accomodate many.  This will involve implementation changes in TeleoModuleManager.c
   but hopefully no API changes.
      
 */

//
// TeleoChannel.h
//

#ifndef _TELEOCHANNELMANAGER_H_
#define _TELEOCHANNELMANAGER_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoError.h"

#define MODULE_ADDRESS_RESERVED            0
#define MODULE_ADDRESS_BROADCAST           1
#define MODULE_ADDRESS_MAX                63

/// Maximum message data size
#define TM_DATAMAX 20

/** Teleo Channel.
    The public structure used for 
    communication with the Channel.
    Internally it is cast into the actual structure
    used by the Channel implementation.
  */
typedef struct
{
  uint8 t;	
} TeleoChannel;
                          
/** Teleo Message Data Structure.
   Is the general structure used to 
   hold messages.  Since the maximum
   data is small, this structure can
   be created on the stack, easily copied, 
   passed by value, etc.  
 */
typedef struct
{
    uint8 address;  ///< destination address (2-63)
    uint8 count;    ///< number of data bytes (0-TM_DATAMAX)
    uint8 data[ TM_DATAMAX ]; ///< data itself
} TeleoMessage;

/** Create the Channel.
    \param tc pointer to TeleoChannel 
    \return TELEO_OK (0) or error code
  */
TeleoError TC_Create( TeleoChannel** tc );

/** Destroy the Channel
    \param tc the Channel
    \returns TELEO_OK or a Teleo Error (see TeleoError.h)
  */
TeleoError TC_destroy( TeleoChannel *tc );

/** Declare the receive callback
    \param tc TeleoChannel
    \param receive the receive function
    \return TELEO_OK (0) or error code
  */
TeleoError TC_receiveCallbackSet( TeleoChannel* tc, TeleoError (*receive)( TeleoChannel* tc, void* tcExt, TeleoMessage *message ) );

/**    
    Assigns the external reference used in non-system callbacks.
    This is useful in situations where there are several Channels running (on multiple
    USB ports, for example) so callbacks do not have to perform a lookup or search operation
    to identify their owners.
    \param tc the TeleoChannel
    \param tcExt the external reference
 */
TeleoError TC_externalReferenceSet( TeleoChannel *tc, void* tcExt );

/** Set the timerRequest callback
    \param tc the Channel
    \param timerRequest timerRequest function pointer
    \return TELEO_OK (0) or error code
  */
TeleoError TC_timerRequestCallbackSet( TeleoChannel* tc, TeleoError (*timerRequest)( TeleoChannel* tc, bool enable ) );

/** Set the output callback
    \param tc the Channel
    \param output output function pointer
    \return TELEO_OK (0) or error code
  */
TeleoError TC_outputCallbackSet( TeleoChannel* tc, TeleoError (*output)( TeleoChannel* tc, uint8* c, uint8 count ) );

/** Call this to get the channel name
    \param tc Channel 
    \param channelName return variable
    \return TELEO_OK (0) or error code
  */
TeleoError TC_channelNameGet( TeleoChannel* tc, cchar** channelName );

/** Call this to set the channel name.  The string is duplicated
    so no problems arise from the original disappearing. 
    \param tc Channel
    \param name new name for the channel
  */
TeleoError TC_channelNameSet( TeleoChannel* tc, cchar* name );

/** Informs the Channel of a new incoming character.  This simple
    appearing call may be quite complex in the case where the incoming
    character is the final one of a well formed message.  In this case
    the Channel will package the message up into a TeleoMessage 
    and invoke its receive() callback function.  When this message
    is received, other steps might need to be taken and so on.
    \param tc the TeleoChannel
    \param c the incoming character
    \returns TELEO_OK or a Teleo Error (see TeleoError.h)
  */
TeleoError TC_input( TeleoChannel* tc, uint8 c );
    
/** Requests a message be sent.  The Channel will format the 
    message into the correct character stream and attempt to send it
    using the output( ) system callback. If the send queue is enabled
    (see TC_sendQueueEnable( ) ) and there is a problem sending the 
    data, the whole message will be queued.  When the next timer tick is
    received, the send will be attempted again.
    \param tc the TeleoChannel
    \param message TeleoMessage to be sent
    \param reliable whether the message should be sent via the reliable system
    \returns TELEO_OK or a Teleo Error (see TeleoError.h)
  */
TeleoError TC_send( TeleoChannel* tc, bool reliable, TeleoMessage *message );

/** Requests a dummy message be sent - usually to ensure the interface
    is in binary mode.
    \param tc the TeleoChannel
    \returns TELEO_OK or a Teleo Error (see TeleoError.h)
  */
TeleoError TC_dummySend( TeleoChannel* tc );

/** Provides a way to monitor the size of the queue of messages waiting to be sent
    \param tc the TeleoChannel
    \param size returning queue size
    \returns TELEO_OK (0) or the appropriate error    
  */
TeleoError TC_sendQueueSizeGet( TeleoChannel* tc, int* size );

/** Enable the queuing of unsuccessful outgoing messages.
    This will require timer events be implemented 
    \param tc the TeleoChannel
    \param enable queing on or off
    \returns TELEO_OK (0) or the appropriate error    
 */
TeleoError TC_sendQueueEnable( TeleoChannel* tc, bool enable );

/**    
    Timer event raised.  This timer is used for two 
    purposes: to check the condition of the parser
    resetting it if necessary and to check the state
    of the send queue - retrying a send if necessary.
    \param tc the TeleoChannel
    \param ms approximate time since last event - provided so the timer events 
           don't have to be a fixed interval.  Try to get the interval as short 
           as pratical (around 10ms).
    \returns TELEO_OK (0) or the appropriate error    
 */
TeleoError TC_timerEvent( TeleoChannel* tc, int ms );

#ifdef __cplusplus
}
#endif

#endif
