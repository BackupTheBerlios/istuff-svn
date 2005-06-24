/* Copyright 2003 MakingThings LLC. */

/*
 : set tabstop=2 shiftwidth=2
*/

/** \file TeleoVideo.h
    TeleoVideo API.
    
    Contains the structures, definitions and functions that 
    wrap the Teleo Video Module to provide a convenient
    programmatical interface.
        
    These functions work on top of the Device Manager, so
    require the device manager to be functioning properly.
 */

#ifndef _TELEO_VIDEO_MOVE_H_
#define _TELEO_VIDEO_MOVE_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"
#include "TeleoDeviceManager.h"
#include "TeleoError.h"
#include "TeleoUtil.h"
#include "TeleoModuleDefines.h"

//
// Teleo Video Move
//

/**
  Teleo Video reference structure.
  This structure exists to permit type safety
  for users of the device without
  exposing the internals to all callers.
 */
typedef struct 
{
  uint8 tag;
} TVideoMove;

/** Create a TVideoMove.
    \param tdm TeleoDeviceManager reference
    \param address module address (or 0 if don't care)
    \param deviceIndex Video device on the MultiIO (0 - 3)
    \param bound is the module specified already bound?
    \param tv a variable to hold the new device
    \return a reference to the object (or NULL if there was something wrong)
  */
TeleoError TVideoMove_Create( TeleoDeviceManager* tdm, cchar* address, uint8 deviceIndex, bool* bound, TVideoMove** tv );

/** Gets the current bound state
    \param tv TVideoMove
    \param bound pointer to the bound variable
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_boundGet( TVideoMove* tv, bool* bound );

/** Set the callback for bound updates
    \param tv TVideoMove
    \param boundUpdate bound callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_boundCallbackSet( TVideoMove* tv, TeleoError (*boundUpdate)( TVideoMove* tv, bool bound ) );

/** Sets the current running status.
    \param tv TVideoMove
    \param value new running value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_runningSet( TVideoMove* tv, bool value );

/** Gets the current running status.
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_runningGet( TVideoMove* tv, bool* value );

/** Set the callback for value updates
    \param tv TVideoMove
    \param runningUpdate runningUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_runningCallbackSet( TVideoMove* tv, TeleoError (*runningUpdate)( TVideoMove* tv, bool running ) );

/** Gets the current sample status.
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_sampleGet( TVideoMove* tv, uint8* value );

/** Set the callback for value updates
    \param tv TVideoMove
    \param sampleUpdate sampleUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_sampleCallbackSet( TVideoMove* tv, TeleoError (*sampleBackgroundLowUpdate)( TVideoMove* tv, uint8 sample ) );

/** Gets the current sample value.
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_sampleBackgroundLowGet( TVideoMove* tv, uint8* value );

/** Set the callback for sample background low value updates
    \param tv TVideoMove
    \param sampleUpdate sampleUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_sampleBackgroundHighCallbackSet( TVideoMove* tv, TeleoError (*sampleBackgroundLowUpdate)( TVideoMove* tv, uint8 backgroundLow ) );

/** Gets the current sample value.
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_sampleBackgroundHighGet( TVideoMove* tv, uint8* value );

/** Set the callback for sample background high value updates
    \param tv TVideoMove
    \param sampleUpdate sampleUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_sampleBackgroundHighCallbackSet( TVideoMove* tv, TeleoError (*sampleBackgroundHighUpdate)( TVideoMove* tv, uint8 backgroundHigh ) );

/** Sets the current sample co-ordinate.
    \param tv TVideoMove
    \param column column value
    \param row row value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_sampleCoordinatesSet( TVideoMove* tv, uint8 column, uint8 row );

/** Determines whether the background is static or dynamic.
    \param tv TVideoMove
    \param value new backgroundDynamic value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_backgroundDynamicSet( TVideoMove* tv, bool value );

/** Gets the background dynamic flag
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_backgroundDynamicGet( TVideoMove* tv, bool* value );

/** Set the callback for value updates
    \param tv TVideoMove
    \param runningUpdate runningUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_backgroundDynamicCallbackSet( TVideoMove* tv, TeleoError (*backgroundDynamicUpdate)( TVideoMove* tv, bool backgroundDynamic ) );

/** Sets the post process flag status.
    \param tv TVideoMove
    \param value new post process value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_postProcessSet( TVideoMove* tv, bool value );

/** Gets the current post process flag status.
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_postProcessGet( TVideoMove* tv, bool* value );

/** Set the callback for post process updates
    \param tv TVideoMove
    \param postProcessUpdate postProcessUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_postProcessCallbackSet( TVideoMove* tv, TeleoError (*postProcessUpdate)( TVideoMove* tv, bool postProcess ) );

/** Sets the tolerance value.
    \param tv TVideoMove
    \param value new tolerance value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_toleranceSet( TVideoMove* tv, bool value );

/** Gets the current tolerance status.
    \param tv TVideoMove
    \param value pointer to the value
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_toleranceGet( TVideoMove* tv, uint8* tolerance );

/** Set the callback for tolerance updates
    \param tv TVideoMove
    \param toleranceUpdate toleranceUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_toleranceCallbackSet( TVideoMove* tv, TeleoError (*toleranceUpdate)( TVideoMove* tv, uint8 tolerance ) );

/** Causes a new background to be captured.
    \param tv TVideoMove
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_backgroundCapture( TVideoMove* tv );

/** Gets the current background status.
    \param tv TVideoMove
    \param value pointer to the value - will return 0 if done acquiring background
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_backgroundGet( TVideoMove* tv, bool* value );

/** Set the callback for value updates
    \param tv TVideoMove
    \param backgroundUpdate backgroundUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_backgroundCallbackSet( TVideoMove* tv, TeleoError (*backgroundUpdate)( TVideoMove* tv, bool background ) );


/** Gets the specified movement row
    \param tv TVideoMove reference returned from TVideoMove_create( )
    \param rowIndex movement row index
    \param movementRow the array of bits of the row requested
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_movementRowGet( TVideoMove* tv, uint8 rowIndex, uint16* movementRow );

/** Set the callback for resolution updates
    \param tv TVideoMove
    \param movementRowUpdate movementRowUpdate callback function 
    \return TELEO_OK or appropriate error code
 */
TeleoError TVideoMove_movementRowCallbackSet( TVideoMove* tv, TeleoError (*movementRowUpdate)( TVideoMove* tv, uint8 rowIndex, uint16 movementRow ) );

/** Invoke the callback when the set of updates is completely sent
    \param tv TVideoMove
    \param movementUpdateComplete movementUpdateComplete callback function 
    \return TELEO_OK or appropriate error code
  */
TeleoError TVideoMove_movementUpdateCompleteCallbackSet( TVideoMove* tv, TeleoError (*movementUpdateComplete)( TVideoMove* tv ) );
    

#ifdef __cplusplus
}
#endif
  
#endif
