/* Copyright 2003 MakingThings LLC. */

#ifndef _STEPPERDEV_
#define _STEPPERDEV_

/** \file TeleoStepperDefines.h
    Defines for the Teleo Stepper Device
 */

//
// DEFINES
//

#define STEPDEV_STEP_POS_CURR                     0
#define STEPDEV_STEP_POS_TARGET                   1
#define STEPDEV_STEP_RATE_MAX                     2
#define STEPDEV_STEP_ACCEL                        3
#define STEPDEV_STEP_RATE                         4
#define STEPDEV_STEP                              5
#define STEPDEV_STEP_DIR                          6
#define STEPDEV_ENABLE                            7
#define STEPDEV_MOTOR_CURR                        8
#define STEPDEV_AN_POS_CURR                       9
#define STEPDEV_LIMITA                           10
#define STEPDEV_LIMITB                           11
#define STEPDEV_BUSY                             12
#define STEPDEV_STEP_SIZE                        13
#define STEPDEV_LIMITS_ON                        14
#define STEPDEV_MOTOR_CURR_MAX                   15
#define STEPDEV_MOTOR_CURR_SAMP_PERIOD           16
#define STEPDEV_AN_POS_RES                       17
#define STEPDEV_AN_POS_SAMP_PERIOD               18
#define STEPDEV_STEP_POS_SAMP_PERIOD             19

#define STEPDEV_STEP_POS_TARGET_DEFAULT           0 
#define STEPDEV_STEP_POS_CURR_DEFAULT             0

#define STEPDEV_STEP_ACCEL_MIN                    0
#define STEPDEV_STEP_ACCEL_MAX                 1000.0
#define STEPDEV_STEP_ACCEL_DEFAULT              100.0

#define STEPDEV_MOTOR_CURR_MAX_MIN                0
#define STEPDEV_MOTOR_CURR_MAX_MAX             3000
#define STEPDEV_MOTOR_CURR_MAX_DEFAULT          250

#define STEPDEV_LIMITS_ON_DEFAULT                 1

#define STEPDEV_ENABLE_DEFAULT                    1

#define STEPDEV_STEP_DIR_MIN                     -1
#define STEPDEV_STEP_DIR_MAX                      1
#define STEPDEV_STEP_DIR_DEFAULT                  0

#define STEPDEV_STEP_SIZE_MIN                     1
#define STEPDEV_STEP_SIZE_MAX                     8
#define STEPDEV_STEP_SIZE_DEFAULT                 1

#define STEPDEV_STEP_RATE_MIN                     0
#define STEPDEV_STEP_RATE_MAX_MAX              1000.0
#define STEPDEV_STEP_RATE_DEFAULT                 0.0
#define STEPDEV_STEP_RATE_MAX_DEFAULT           100.0

#define STEPDEV_STEP_POS_SAMP_PER_MIN            10
#define STEPDEV_STEP_POS_SAMP_PER_MAX         10000
#define STEPDEV_STEP_POS_SAMP_PER_DEFAULT       250

#define STEPDEV_AN_POS_SAMP_PER_MIN              10
#define STEPDEV_AN_POS_SAMP_PER_MAX           10000
#define STEPDEV_AN_POS_SAMP_PER_DEFAULT         250

#define STEPDEV_AN_POS_RES_MIN                    1
#define STEPDEV_AN_POS_RES_MAX                   10
#define STEPDEV_AN_POS_RES_DEFAULT               10

#define STEPDEV_MOTOR_CUR_SAMP_PER_MIN           10
#define STEPDEV_MOTOR_CUR_SAMP_PER_MAX        10000
#define STEPDEV_MOTOR_CUR_SAMP_PER_DEFAULT     1000

#define STEPPERDEV_DEVICE_MIN                     0
#define STEPPERDEV_DEVICE_MAX                     0
#define STEPPERDEV_DEVICE_DEFAULT                 0

/*
#define STEPPERDEV_PORT_DIRECTION             0 // low level in
#define STEPPERDEV_PORT_RATE                  1 // low level in
#define STEPPERDEV_PORT_ON                    2 // low level in
#define STEPPERDEV_PORT_LIMITA                3 //           out
#define STEPPERDEV_PORT_LIMITB                4 //           out
#define STEPPERDEV_PORT_LIMITSON              5 //           in
#define STEPPERDEV_PORT_CURRENT_POSITION      6 //           out
#define STEPPERDEV_PORT_POS_SAMPLE_RATE       7 //           in
#define STEPPERDEV_PORT_POSITION_TARGET       8 // main      in
#define STEPPERDEV_PORT_RATEMAX               9 // main      in
#define STEPPERDEV_PORT_ACCELERATION         10 // main      in
#define STEPPERDEV_PORT_POWER                11 //           in
#define STEPPERDEV_PORT_BUSY                 12 //           out
#define STEPPERDEV_PORT_CURRENT_SAMPLE_RATE  13 //           in
#define STEPPERDEV_PORT_CURRENT              14 //           out

#define STEPPERDEV_MIN_VALID_TARGET          -32767	// confirm
#define STEPPERDEV_MAX_VALID_TARGET           32768	// confirm
#define STEPPERDEV_DEFAULT_TARGET                 0

#define STEPPERDEV_MIN_VALID_RATEMAX              0
#define STEPPERDEV_MAX_VALID_RATEMAX           1000	// confirm
#define STEPPERDEV_DEFAULT_RATEMAX              100

#define STEPPERDEV_MIN_VALID_ACCELERATION         0
#define STEPPERDEV_MAX_VALID_ACCELERATION      1000	// confirm
#define STEPPERDEV_DEFAULT_ACCELERATION         100

#define STEPPERDEV_MIN_VALID_POWER                0
#define STEPPERDEV_MAX_VALID_POWER              255
#define STEPPERDEV_DEFAULT_POWER                255

#define STEPPERDEV_DEFAULT_LIMITSON               0
#define STEPPERDEV_DEFAULT_ON                     1

#define STEPPERDEV_MIN_VALID_DIRECTION         -127	// confirm
#define STEPPERDEV_MAX_VALID_DIRECTION          128	// confirm
#define STEPPERDEV_DEFAULT_DIRECTION              0

#define STEPPERDEV_MIN_VALID_RATE                 0
#define STEPPERDEV_MAX_VALID_RATE              1000	// confirm
#define STEPPERDEV_DEFAULT_RATE                 100

#define STEPPERDEV_MIN_VALID_POS_SAMPLE_RATE      5
#define STEPPERDEV_MAX_VALID_POS_SAMPLE_RATE  32768
#define STEPPERDEV_DEFAULT_POS_SAMPLE_RATE      250

#define STEPPERDEV_MIN_VALID_CURRENT_SAMPLE_RATE      5
#define STEPPERDEV_MAX_VALID_CURRENT_SAMPLE_RATE  32768
#define STEPPERDEV_DEFAULT_CURRENT_SAMPLE_RATE     1000
*/

#endif
