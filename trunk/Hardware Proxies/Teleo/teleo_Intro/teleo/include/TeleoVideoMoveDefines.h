#ifndef _VIDEODEVDEF_
#define _VIDEODEVDEF_

//
// DEFINES
//


#define VIDEODEV_PROPERTY_SAMPLE_PERIOD       0
#define VIDEODEV_PROPERTY_RUNNING             1
#define VIDEODEV_PROPERTY_BACKGROUND          2
#define VIDEODEV_PROPERTY_BACKGROUND_DYN     23   // move me later to 3, and the rest up...

#define VIDEODEV_PROPERTY_SAMPLE              3
#define VIDEODEV_PROPERTY_SAMPLE_BK_LOW       4
#define VIDEODEV_PROPERTY_SAMPLE_BK_HIGH      5
#define VIDEODEV_PROPERTY_SAMPLE_COLUMN       6
#define VIDEODEV_PROPERTY_SAMPLE_ROW          7

#define VIDEODEV_PROPERTY_MOVE_TOLERANCE      8
#define VIDEODEV_PROPERTY_MOVE_DESPECKLE      9

#define VIDEODEV_PROPERTY_MOVE_ROW_00        10
#define VIDEODEV_PROPERTY_MOVE_ROW_01        11
#define VIDEODEV_PROPERTY_MOVE_ROW_02        12
#define VIDEODEV_PROPERTY_MOVE_ROW_03        13
#define VIDEODEV_PROPERTY_MOVE_ROW_04        14
#define VIDEODEV_PROPERTY_MOVE_ROW_05        15
#define VIDEODEV_PROPERTY_MOVE_ROW_06        16
#define VIDEODEV_PROPERTY_MOVE_ROW_07        17
#define VIDEODEV_PROPERTY_MOVE_ROW_08        18
#define VIDEODEV_PROPERTY_MOVE_ROW_09        19
#define VIDEODEV_PROPERTY_MOVE_ROW_10        20
#define VIDEODEV_PROPERTY_MOVE_ROW_11        21

#define VIDEODEV_PROPERTY_MOVE_ROWS_DONE     22

#define VIDEODEV_MOVEMENT_ROWS      12
#define VIDEODEV_MOVEMENT_COLUMNS   16

#define VIDEODEV_PERIOD_DEFAULT      100
#define VIDEODEV_PERIOD_MIN          10
#define VIDEODEV_PERIOD_MAX          1000

#define VIDEODEV_RUNNING_DEFAULT     0

#define VIDEODEV_BACKGROUND_DEFAULT  0

#define VIDEODEV_TOLERANCE_DEFAULT      0
#define VIDEODEV_TOLERANCE_MIN          0
#define VIDEODEV_TOLERANCE_MAX          16

#define VIDEODEV_DESPECKLE_DEFAULT      0

#define VIDEODEV_DEVICE_DEFAULT     0
#define VIDEODEV_DEVICE_MIN         0
#define VIDEODEV_DEVICE_MAX         1

#endif