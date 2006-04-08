/* MyApplication */

#import <Cocoa/Cocoa.h>
#import "EHModel.h"

@interface MyApplication : NSApplication
{	
	IBOutlet id mEHModel;
	//NSDictionary * fields;
	//EHModel* mEHModel;
	NSMutableArray * events;
}
-(void)setEvents:(NSArray *)iArray;
- (id)handleSendCommand:(NSScriptCommand *)command;
- (id) handleAddCommand:(NSScriptCommand *)command;
- (NSArray *)events;
-(void)setEvents:(NSArray *)iArray;
@end
