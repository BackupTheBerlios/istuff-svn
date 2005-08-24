/* Copyright 2003 MakingThings LLC. */

/** \file TeleoError.h
    Teleo Error Return Codes.
 */

#ifndef _TELEOERROR_H_
#define _TELEOERROR_H_

typedef enum 
{
  TELEO_OK = 0,		     	  ///<  0: All OK
  TELEO_E_NOTHING,	   	  ///<  1: Data missing
  TELEO_E_LOGIC,		      ///<  2: Logic Error
  TELEO_E_UNKNOWN,		    ///<  3: Unknown
  TELEO_E_TRUNCATED,		  ///<  4: 
  TELEO_E_BOUND,		      ///<  5: Module wasn't bound
  TELEO_E_ILLEGAL_ADDRESS,///<  6: Address wasn't correct
  TELEO_E_UNIMPLEMENTED,	///<  7: Feature is not implemented
  TELEO_E_IO,			        ///<  8: IO Error
  TELEO_E_NULL_POINTER,		///<  9: Null pointer encountered
  TELEO_E_OPEN,			      ///< 10: Error Opening 
  TELEO_E_READ,			      ///< 11: Error Reading
  TELEO_E_WRITE,		      ///< 12: Error Writing
  TELEO_E_CLOSE,		      ///< 13: Error Closing
  TELEO_E_UNKNOWN_TYPE,		///< 14: Type was unknown
  TELEO_E_CONVERSION,		  ///< 15: Conversion error
  TELEO_E_ALLOC,		      ///< 16: Allocation error
  TELEO_E_NOT_FOUND,  	  ///< 17: Entity was not found
  TELEO_E_ILLEGAL_DEVICE, ///< 18: Device number was illegal
  TELEO_E_INSUFF_SPACE    ///< 19: Insufficient space for operation
} TeleoError;

#endif
