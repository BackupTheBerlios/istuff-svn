//
//  EHMakeEventCommand.m
//  eventheap
//
//  Created by eugen on Thu Apr 06 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import "EHMakeEventCommand.h"
#import "EHEvent.h"

@implementation EHMakeEventCommand

-(id)performDefaultImplementation
{
	NSLog(@"make command create object");
	EHEvent * res = [[EHEvent alloc]init];
	return res;
}
@end
