/* Copyright 2003 MakingThings LLC. */

#ifndef _INTROPWMDEV_
#define _INTROPWMDEV_

/** \file TeleoIntroPwmDefines.h
    Defines for the Intro Pwm Device.
 */

//
// DEFINES
//

#define TELEO_INTRO_PWM_DEV_OFFSET             8

#define INTROPWMDEV_PORT_DUTY                  0   // int16
#define INTROPWMDEV_PORT_ON                    1   // int16

#define INTROPWMDEV_DEFAULT_DUTY               0
#define INTROPWMDEV_MIN_VALID_DUTY             0
#define INTROPWMDEV_MAX_VALID_DUTY           255

#define INTROPWMDEV_DEFAULT_ON                 1
#define INTROPWMDEV_MIN_VALID_ON               0
#define INTROPWMDEV_MAX_VALID_ON               1

#define INTROPWMDEV_DEFAULT_VALID_DEVICE       0
#define INTROPWMDEV_MIN_VALID_DEVICE           0
#define INTROPWMDEV_MAX_VALID_DEVICE           1

#endif
