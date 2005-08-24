/* Copyright 2003 MakingThings LLC. */

#ifndef _SERVODEV_
#define _SERVODEV_


/** \file TeleoServoDefines.h
    Defines for the Teleo Servo Device
 */ 

//
// DEFINES
//

#define SERVODEV_PORT_POSITION       0   // int16
#define SERVODEV_PORT_ENABLE         1
#define SERVODEV_PORT_MIN            2
#define SERVODEV_PORT_MAX            3

#define SERVODEV_DEFAULT_POSITION              0
#define SERVODEV_MIN_VALID_POSITION        -1024
#define SERVODEV_MAX_VALID_POSITION         1024

#define SERVODEV_DEFAULT_MIN               -100
#define SERVODEV_DEFAULT_MAX                100

#define SERVODEV_DEFAULT_ENABLE             1

#define SERVODEV_DEFAULT_DEVICE             0
#define SERVODEV_MIN_VALID_DEVICE           0
#define SERVODEV_MAX_VALID_DEVICE           7

#endif
