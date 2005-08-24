/* Copyright 2003 MakingThings LLC. */

#ifndef _DINDEV_
#define _DINDEV_

/** \file TeleoMioDinDefines.h
    Defines for the MultiIO Din Device.
 */

//
// DEFINES
//

#define TELEO_MULTIIO_DIN_DEV_OFFSET      4

#define DINDEV_PORT_VALUE       	  0
#define DINDEV_PORT_INVERT      	  1
#define DINDEV_PORT_SAMPLE_RATE 	  2

#define DINDEV_DEFAULT_DEVICE             0
#define DINDEV_MIN_VALID_DEVICE           0
#define DINDEV_MAX_VALID_DEVICE           3

#define DINDEV_DEFAULT_SAMPLE_RATE      100
#define DINDEV_MIN_VALID_SAMPLE_RATE      0
#define DINDEV_MAX_VALID_SAMPLE_RATE   1000

#define DINDEV_DEFAULT_INVERT             1

#endif
