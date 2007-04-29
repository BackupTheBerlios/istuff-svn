/* Copyright 2003 MakingThings LLC. */

/** \file TeleoUtil.h
    Teleo Utility Function API.
    Contains Array and CRC code.
 */

//
// TeleoUtil.h
//

#ifndef _TELEOUTIL_H_
#define _TELEOUTIL_H_

#include "TeleoTypes.h"
#include "TeleoData.h"
#include "TeleoError.h"
         
/// Variable length array.  
/** Used for storage of void*'s in an array of
    memory.  Array_XXX functions perform operations on it.
 */
typedef struct
{
  void*  (*data);    ///< pointer to the actual data
  uint16 capacity;   ///< capacity of the current block of memory
  uint16 size;       ///< current valid data size
} Array;

/// Allocate, initialize and return a new Array structure
Array* Array_new( void );

/** get rid of an array and internal data
    \param array the Array*
*/
void Array_delete( Array* array );

/** Initialize a pre-allocated Array
    \param array the Array*
*/
TeleoError Array_init( Array* array );

/** Free the data in an Array
    \param array Array*
*/
void Array_uninit( Array* array );

/** Append a void* element onto the end of the Array
    \param array the Array*
    \param element the element to add
*/
void Array_append( Array* array, void* element );

/** Remove a specifed element from the Array.  Does 
    not free the element. It is the responsibility
    of the caller to shrink the array again.  Call
    Array_capacitySet( ).
    \param array the Array*
    \param element the element to remove
*/
void Array_remove( Array* array, void* element );

/** Empty the Array - size is set to 0.  No elements
    are freed or NULL'ed.  It is the responsibility
    of the caller to shrink the array again.  Call
    Array_capacitySet( ).
    \param array the Array*
*/
void Array_empty( Array* array );

/** Free the contents of the array.
    All non-NULL elements in the array are free'd and
    the array size is set to 0
    \param array the Array*
  */
void Array_freeAll( Array* array );

/** Get the current number of elements in the array 
    \param array the Array
 */
int  Array_sizeGet( Array* array );

/** Get the index of the specified element
    \param array the Array*
    \param element the element to remove
    \return the index of the element or -1 if it wasn't found
  */
int  Array_elementFind( Array* array, void* element );

/** Get the element at the specified location
    \param array the Array*
    \param index the index of the element
    \return the element
*/
void* Array_elementGet( Array* array, int index );

/** Set the element at the specified location
    \param array Array
    \param index index of the element
    \param element new element
    \return element requested
*/
void Array_elementSet( Array* array, int index, void* element );

/** Make the array a specified size: if the size is larger than the current
    size, an array of the specified size is created and the contents
    of the existing array are copied in.  This routine should be
    used to shrink the required memory if a large array is used
    temporarily.  This is not done automatically by Array_empty( )
    or Array_remove( ).
    \param array Array*
    \param capacity new capacity
*/
void Array_capacitySet( Array* array, int capacity );

/** Prepares an unsigned 16bit int to be a CRC number
    \param crc pointer to the crc accumulator
*/
void CRC_Init( uint16* crc );
/** Adds the datum c to the crc
    \param crc pointer to the crc accumulator
    \param c next byte to add to the crc
*/
void CRC_Data( uint16* crc, uint8 c );


/** Reads the data from the supplied data structure as the
 desired type.
 \param teleoData TeleoData structure to be read
 \param value TeleoData interpretted as an Integer
 \return error code
*/
TeleoError TeleoData_readInt( TeleoData* teleoData, int16* value );

/** Reads the data from the supplied data structure as the
 desired type.
 \param teleoData TeleoData structure to be read
 \param value TeleoData interpretted as an Small Integer
 \return error code
*/
TeleoError TeleoData_readSmallInt( TeleoData* teleoData, int8* value );

/** Reads the data from the supplied data structure as the
 desired type.
 \param teleoData TeleoData structure to be read
 \param value TeleoData interpretted as a Float
 \return error code
*/
TeleoError TeleoData_readFloat( TeleoData* teleoData, float* value );

/** Reads the data from the supplied data structure as the
 desired type.
 \param teleoData TeleoData structure to be read
 \param value TeleoData interpretted as a Bool
 \return error code
*/
TeleoError TeleoData_readBool( TeleoData* teleoData, bool* value );

/** Reads the data from the supplied data structure as the
 desired type.
 \param teleoData TeleoData structure to be read
 \param string pointer to destination for converted result
 \param sLen maximum string size
 \return error code
*/
TeleoError TeleoData_readString( TeleoData* teleoData, char* string, int sLen );

/** Copies data.  Quicker than a structure copy.
 \param toData TeleoData structure to be assigned
 \param fromData TeleoData structure to be read
 \return error code
*/
TeleoError TeleoData_copy( TeleoData* toData, TeleoData* fromData );

#endif
