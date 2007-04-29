/* 
 *     Created by Clockskew.  Use for whatever.  Don't sue me. 
 */


#import "GFGraph.h"

@class QCBooleanPort, QCContext, QCNumberPort, QCPatchRuntime;

@interface QCPatch : GFGraph
{
    QCPatchRuntime *_executionRuntime;
    int _executionMode;
    unsigned int _executionFlags;
    QCContext *_executionContext;
    int _timebase;
    QCBooleanPort *_enableInput;
    QCNumberPort *_timeInput;
    BOOL _enabled;
    unsigned int _activeCount;
    double _lastExecutionTime;
    unsigned int _lastExecutionFrame;
    double _activationTime;
    void *_observationInfo;
    void *_unused3[4];
}

+ (BOOL)accessInstanceVariablesDirectly;
+ (BOOL)automaticallyNotifiesObserversForKey:(id)fp8;
- (id)consumerSubpatches;
- (void)setOrder:(unsigned int)fp8 forConsumerSubpatch:(id)fp12;
- (unsigned int)orderForConsumerSubpatch:(id)fp8;
- (void)setTimebase:(int)fp8;
- (int)timebase;
- (id)systemInputPorts;
- (id)systemOutputPorts;

@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QCNumberPort
- (double)doubleValue;
- (void)setDoubleValue:(double)value;
@end

@interface QCColorPort
- (float)redComponent;
- (float)greenComponent;
- (float)blueComponent;
- (float)alphaComponent;
- (void)setRedComponent:(float)red;
- (void)setGreenComponent:(float)green;
- (void)setBlueComponent:(float)blue;
- (void)setAlphaComponent:(float)alpha;
@end

@interface QCStringPort
- (NSString*)stringValue;
- (void)setStringValue:(NSString*)fp8;
@end

@interface QCBooleanPort
- (BOOL)booleanValue;
- (void)setBooleanValue:(BOOL)value;
@end

@interface QCIndexPort
- (unsigned int)indexValue;
- (void)setIndexValue:(unsigned int)value;
@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
@interface QCGLPort_Color
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_Image
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_Blending
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_Culling
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

@interface QCGLPort_ZBuffer
- (void)set:(CGLContextObj)ctx;
- (void)unset:(CGLContextObj)ctx;
@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QCOpenGLContext
- (CGLContextObj)CGLContextObj;
@end

*/