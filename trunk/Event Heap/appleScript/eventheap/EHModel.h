//
//  EHModel.h
//  eheapscriptview
//
//  Created by eugen on Sun Apr 02 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EventHeap.h"
#import "EHEvent.h"

@interface EHModel : NSObject {
	NSString * mHeapname;	
	NSDictionary * fields;
	EventHeap * mHeapAdapter;
}

-(NSString *)serverName;
-(void)setServerName: (NSString *)iEheapName;
@end
