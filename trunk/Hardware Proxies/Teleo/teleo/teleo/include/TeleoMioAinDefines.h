/* Copyright 2003 MakingThings LLC. */

#ifndef _AINDEV_
#define _AINDEV_

/** \file TeleoMioAinDefines.h
    Defines for the MultiIO Ain Device.
 */

//
// DEFINES
//

#define TELEO_MULTIIO_AIN_DEV_OFFSET      0

#define AINDEV_PORT_VALUE       0
#define AINDEV_PORT_DELTA       1	// no longer used, just a place holder
#define AINDEV_PORT_MIN         2
#define AINDEV_PORT_MAX         3
#define AINDEV_PORT_SAMPLE_RATE 4
#define AINDEV_PORT_IN_RANGE    5
#define AINDEV_PORT_RANGE_MIN   6
#define AINDEV_PORT_RANGE_MAX   7
#define AINDEV_PORT_RESOLUTION  8

#define AINDEV_DEFAULT_DEVICE              0
#define AINDEV_MIN_VALID_DEVICE            0
#define AINDEV_MAX_VALID_DEVICE            3

#define AINDEV_DEFAULT_SAMPLE_RATE       100
#define AINDEV_MIN_VALID_SAMPLE_RATE       0
#define AINDEV_MAX_VALID_SAMPLE_RATE    1000

#define AINDEV_MIN_VALID_MIN   -1024
#define AINDEV_MAX_VALID_MIN    1024

#define AINDEV_MIN_VALID_MAX   -1024
#define AINDEV_MAX_VALID_MAX    1024

#define AINDEV_DEFAULT_SCALE_MIN         -100
#define AINDEV_DEFAULT_SCALE_MAX          100

#define AINDEV_DEFAULT_IN_RANGE_MIN         0
#define AINDEV_DEFAULT_IN_RANGE_MAX       100

#define AINDEV_MIN_VALID_RESOLUTION         1
#define AINDEV_MAX_VALID_RESOLUTION        10
#define AINDEV_DEFAULT_RESOLUTION           5

#endif
