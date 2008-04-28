//
//  RFIDReader.m
//  QCiStuff
//
//  Created in by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "RFIDReader.h"

@interface RFIDReader (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation RFIDReader
	
- (id)initWithIdentifier:(id)fp8
{
	[super initWithIdentifier:fp8];
	[outputTag setStringValue:nil];
	
	// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"PhidgetRFID"];
	[self addTemplateEvent:templateEvent];
	return self;
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) processEvent:(iStuffEvent *) event {
	[outputTag setStringValue:[event stringValueForField:@"TagNumber"]];
}


@end
