//
//  EHModel.m
//  eheapscriptview
//
//  Created by eugen on Sun Apr 02 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import "EHModel.h"


@implementation EHModel
-(void)awakeFromNib
{
	mEventHeap  = [[EventHeapAdapter alloc] init];
}

-(NSString *)getEventheapName{
	return mHeapname;
}

-(void) setEventheapName: (NSString *) iHeapname{
	mHeapname = iHeapname;
	NSLog([@"Connecting to " stringByAppendingString: mHeapname]);
	[mEventHeap createEventHeap:@"local" atServer:mHeapname atPort:4535];
}

-(NSString *)getEventType{
	return eventType;
}

-(void) setEventType: (NSString *)iEventType{
	eventType = iEventType;
	NSLog([@"Send event " stringByAppendingString:iEventType]);
	
	eh2_EventPtr* oEvent = [mEventHeap createEvent: eventType];
	[mEventHeap postEvent: oEvent];
}


@end
