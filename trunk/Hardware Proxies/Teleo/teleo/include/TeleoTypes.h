/* Copyright 2003 MakingThings LLC. */

/** \file TeleoTypes.h
    Common datatype abbreviations and constants
 */


#ifndef _TELEOTYPES_H_
#define _TELEOTYPES_H_

typedef signed char    int8;
typedef unsigned char  uint8;
typedef unsigned char  uchar;
typedef signed short   int16;
typedef unsigned short uint16;
typedef signed int     int32;
typedef unsigned int   uint32;
typedef const char     cchar;

#ifndef __cplusplus              // built-in type in c++ 
typedef unsigned char    bool;
#endif

//#ifndef _WIN32
#define false 0
#define true  1
//#endif

#endif
