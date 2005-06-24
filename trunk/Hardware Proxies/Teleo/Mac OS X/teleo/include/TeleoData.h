/* Copyright 2003 MakingThings LLC. */

/** \file TeleoData.h
    Contains the TeleoData structure.
    
    This is a very simple tagged union
    of data types.  It corresponds very 
    closely to the format used on the 
    TeleoNetwork.
    
    See TeleoUtil.h for some routines that
    manipulate these structures.
*/

//
// TeleoData.h
//

#ifndef _TELEODATA_H_
#define _TELEODATA_H_

#ifdef __cplusplus              /* Note: two leading underscores */
extern "C" {
#endif

#include "TeleoTypes.h"

// Commonly used data structure for data within a message
// Note that the data that can fit in a message will
// almost always be less than the TM_DATAMAX since messages will
// also have to specify message type, etc. reducing the available
// space for data.

#define TD_DATAMAX 12

// MESSAGE DATA TYPE IDENTIFIERS
// identifyies the type of data in the structure below

#define MESSAGE_DATATYPE_NONE      0x00
#define MESSAGE_DATATYPE_EVENT     0x10
#define MESSAGE_DATATYPE_BOOL      0x11
#define MESSAGE_DATATYPE_SMALLINT  0x12
#define MESSAGE_DATATYPE_INT       0x13
#define MESSAGE_DATATYPE_FLOAT     0x14
#define MESSAGE_DATATYPE_STRING    0x15

/**
 Teleo data transfer tagged union.
 Tagged union that contains data sent to or received from 
 Modules
 */
typedef struct
{
  uint8  datatype;             ///< the data type
  union
  {
    uint8  b;                  ///< boolean
    int8   si;                 ///< small integer
    int16  i;                  ///< integer
    float  f;                  ///< float
    char   s[ TD_DATAMAX ];    ///< string
    uint8  d[ TD_DATAMAX ];    ///< data
  } data;
} TeleoData;


#ifdef __cplusplus
}
#endif

#endif
