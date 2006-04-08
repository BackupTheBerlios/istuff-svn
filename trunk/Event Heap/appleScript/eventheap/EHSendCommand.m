//
//  EHSendCommand.m
//  eventheap
//
//  Created by eugen on Wed Apr 05 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import "EHSendCommand.h"


@implementation EHSendCommand



//How or when do I set delegates?
//This method is called if no responder is found accoring to the script and sdef file
-(id)performDefaultImplementation
{
	NSLog(@"perform send's default impl");
	// ask the Application delegate to do the work:
	/*	return [NSNumber numberWithBool:[
										[self delegate] 
									application:self 
									openFile:file]
			];
	*/
	return nil;
}
@end
