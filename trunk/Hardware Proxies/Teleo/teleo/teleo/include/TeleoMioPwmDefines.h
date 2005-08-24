/* Copyright 2003 MakingThings LLC. */

#ifndef _PWMDEV_
#define _PWMDEV_

/** \file TeleoMioPwmDefines.h
    Defines for the MultiIO Pwm Device.
 */

//
// DEFINES
//

#define TELEO_MULTIIO_PWM_DEV_OFFSET     12

#define PWMDEV_PORT_SPEED      0   // int16
#define PWMDEV_PORT_SPEED_MAX  1   // int16
#define PWMDEV_PORT_ON         2   // int16

#define PWMDEV_DEFAULT_SPEED              0
#define PWMDEV_MIN_VALID_SPEED        -1024
#define PWMDEV_MAX_VALID_SPEED         1024

#define PWMDEV_DEFAULT_SPEED_MAX        100
#define PWMDEV_MIN_VALID_SPEED_MAX        0
#define PWMDEV_MAX_VALID_SPEED_MAX     1024

#define PWMDEV_DEFAULT_ON                 1
#define PWMDEV_MIN_VALID_ON               0
#define PWMDEV_MAX_VALID_ON               1

#define PWMDEV_DEFAULT_VALID_DEVICE       0
#define PWMDEV_MIN_VALID_DEVICE           0
#define PWMDEV_MAX_VALID_DEVICE           1

#endif
