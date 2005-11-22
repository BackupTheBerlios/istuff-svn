/* 
 *     Created by Clockskew.  Use for whatever.  Don't sue me. 
 */


@interface GFNodeManager : NSObject
- (void)registerNodeWithClass:(Class)patch_class;
@end

@protocol GFPlugInRegistration
+ (void)registerNodesWithManager:(GFNodeManager*)manager;
@end