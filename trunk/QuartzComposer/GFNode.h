/* 
 *     Created by Clockskew.  Use for whatever.  Don't sue me. 
 */


#import <Cocoa/Cocoa.h>

@class GFGraph, GFList, NSMutableDictionary, NSString;

@interface GFNode : NSObject 
{
    GFList *_inputPorts;
    GFList *_outputPorts;
    GFGraph *_parent;
    NSString *_identifier;
    NSMutableDictionary *_userInfo;
    unsigned int _notificationsDisabled;
    unsigned int _notificationsPaused;
    GFList *_notificationsQueue;
    BOOL _portsUpdated;
    void *_unused[4];
}

+ (void)initialize;
+ (id)xmlAttributesWithIdentifier:(id)fp8;
+ (id)attributesWithIdentifier:(id)fp8;
+ (BOOL)createIvarPorts;
+ (id)nodeWithIdentifier:(id)fp8;
- (id)init;
- (void)__setValue:(id)fp8 forIvar:(const char *)fp12;
- (id)initWithIdentifier:(id)fp8;
- (void)_finalize_GFNode;
- (void)finalize;
- (void)dealloc;
- (id)identifier;
- (id)argumentsForIvarPortWithKey:(id)fp8;
- (id)createInputPortWithArguments:(id)fp8 forKey:(id)fp12;
- (id)createOutputPortWithArguments:(id)fp8 forKey:(id)fp12;
- (void)deleteInputPortForKey:(id)fp8;
- (void)deleteOutputPortForKey:(id)fp8;
- (id)userInfo;
- (id)inputPorts;
- (id)outputPorts;
- (id)ivarInputPorts;
- (id)ivarOutputPorts;
- (id)customInputPorts;
- (id)customOutputPorts;
- (BOOL)saveCustomInputPortStates:(id)fp8 toState:(id)fp12;
- (BOOL)saveCustomOutputPortStates:(id)fp8 toState:(id)fp12;
- (BOOL)restoreCustomInputPortStates:(id)fp8 fromState:(id)fp12;
- (BOOL)restoreCustomOutputPortStates:(id)fp8 fromState:(id)fp12;
- (id)xmlAttributes;
- (id)attributes;
- (id)description;
- (id)state;
- (BOOL)setState:(id)fp8;
- (void)encodeWithCoder:(id)fp8;
- (id)initWithCoder:(id)fp8;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (id)portForKey:(id)fp8;
- (id)keyForPort:(id)fp8;
- (int)directionForPort:(id)fp8;
- (id)graph;
- (void)pauseNotifications;
- (void)resumeNotifications;
- (void)stateUpdated;
- (void)logMessage:(id)fp8;
- (void)debugMessage:(id)fp8;
- (id)key;
- (void)nodeDidAddToGraph:(id)fp8;
- (void)nodeWillRemoveFromGraph;

@end

