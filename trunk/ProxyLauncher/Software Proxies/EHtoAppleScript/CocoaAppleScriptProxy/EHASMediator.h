/* EHASMediator */

#import <Cocoa/Cocoa.h>
#import <eh2.h>
#import "EventHeap.h"

@interface EHASMediator : NSObject
{   
	//EventHeap *
	IBOutlet id mEventHeap;
	BOOL scriptHasErred;

}
-(NSString *)executeScript:(NSString *)iScript;
-(eh2_EventPtr)processEvent:(eh2_EventPtr) iEventPtr;
@end
