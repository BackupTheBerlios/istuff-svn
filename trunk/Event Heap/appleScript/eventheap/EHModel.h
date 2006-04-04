//
//  EHModel.h
//  eheapscriptview
//
//  Created by eugen on Sun Apr 02 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EventHeapAdapter.h"

@interface EHModel : NSObject {
	EventHeapAdapter * mEventHeap;
	
	NSString * mHeapname;
	NSString * eventType;
	
	NSDictionary * fields;
}

-(NSString *)getEventheapName;
-(void) setEventheapName: (NSString *) iHeapname;
-(NSString *)getEventType;
-(void) setEventType: (NSString *)iEventType;
@end
