//
//  EHEvent.m
//  eventheap
//
//  Created by eugen on Wed Apr 05 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//
#import "EHEvent.h"


@implementation EHEvent
-init
{
	self = [super init];
	if (self){
		mtype = @"testype";
		//fields = [NSMutableDictionary dictionaryWithCapacity:30];
		fields = [[NSMutableDictionary alloc] initWithCapacity:20];
		fieldTypes = [[NSMutableDictionary alloc] initWithCapacity:20];
	}
	return self;
}

- (void)dealloc
{
	//[mEHModel release];
    //[super dealloc];
    [mtype release];
	[fields release];
	[fieldTypes release];
}

////////////////////////////////////////////////////////////
-(NSString *) getType
{
	return mtype;
}

-(void) setType:(NSString *)iTypeName
{
	mtype = [[NSString alloc] initWithString:iTypeName];
}


////////////////////////////////////////////////////////////
-(NSDictionary *)fields
{
	return fields;
}

//Put fields into the event object
- (void)setValue:(id)anObject forField:(id)aKey
{
	[fields setValue: anObject forKey: aKey];
}

////////////////////////////////////////////////////////////
-(NSDictionary *)fieldTypes
{
	return fieldTypes;
}

//Put fields into the event object
- (void)setType:(id)anObject forField:(id)aKey
{
	[fieldTypes setValue: anObject forKey: aKey];
}
@end
