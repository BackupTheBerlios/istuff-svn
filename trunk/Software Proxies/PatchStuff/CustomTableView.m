//
//  CustomTableView.m
//  QCiStuff
//
//  Created by Rene Reiners on 4/5/06.
//  Copyright 2006 Media Computing Group RWTH Aachen, Germany. All rights reserved.
//

#import "CustomTableView.h"


@implementation CustomTableView

- (void)textDidEndEditing:(NSNotification *)aNotification{	
	NSTextView *textView = [aNotification valueForKey:@"object"];
	// Post another notification that updates the list model.
	NSDictionary *postInfo = [NSDictionary dictionaryWithObject:[textView string] forKey:@"item"];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"NewItem" object:self userInfo:postInfo];
	//[super textDidEndEditing:aNotification];
}

@end
