//
//  AppDelegate.m
//  eheapscriptview
//
//  Created by eugen on Sun Apr 02 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import "AppDelegate.h"


@implementation AppDelegate
- (BOOL)application:(NSApplication *)sender
 delegateHandlesKey:(NSString *)key
{
	if ([key isEqual:@"eheapName"] || [key isEqual:@"eTypeName"] || [key isEqual:@"field"]) {
		return YES;
	} else {
		return NO;
	}
}


- (NSString *)eheapName
{
	return [mEHModel getEventheapName];
}

- (void)setEheapName:(NSString *)text
{
	[mEHModel setEventheapName:text];
}


- (NSString *)eTypeName
{
	return [mEHModel getEventType];
}

- (void)setETypeName:(NSString *)text
{
	[mEHModel setEventType:text];
}

@end
