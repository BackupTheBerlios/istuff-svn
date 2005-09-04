#include <jni.h>
#include "EventSim.h"
#include <ApplicationServices/ApplicationServices.h>

JNIEXPORT void JNICALL
Java_EventSim_enableEventStateCombining(JNIEnv *env, jclass class, jboolean enable)
{
    CGEnableEventStateCombining(enable);
}

JNIEXPORT void JNICALL
Java_EventSim_postMouseEvent(JNIEnv *env, jclass class,
                             jint x, jint y, jint leftButton, jint rightButton, jint middleButton)
{
    CGPoint p = { x, y };
    CGPostMouseEvent(p, 1, 3, leftButton, rightButton, middleButton);
}

JNIEXPORT void JNICALL
Java_EventSim_postScrollEvent(JNIEnv *env, jclass class,
                              jint value)
{
    CGPostScrollWheelEvent(1, value);
}

JNIEXPORT void JNICALL
Java_EventSim_postKeyEvent(JNIEnv *env, jclass class,
                           jint charCode, jint keyCode, jint state)
{
    CGPostKeyboardEvent(charCode, keyCode, state);
}
