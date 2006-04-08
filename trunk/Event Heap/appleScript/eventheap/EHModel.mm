//
//  EHModel.m
//  eheapscriptview
//
//  Created by eugen on Sun Apr 02 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import "EHModel.h"
#define DEBUG 0

@implementation EHModel

-(void)awakeFromNib
{
	if (DEBUG) NSLog(@"EHModel:awake");
	mHeapname = @"default heap name,wake";
}

-init
{
	self = [super init];
	if (self){
		if (DEBUG) NSLog(@"EHModel:init");
		mHeapname = @"default heap name";
		
		mHeapAdapter = [[EventHeap alloc]init];
	}
	return self;
}

- (BOOL)application:(NSApplication *)sender delegateHandlesKey:(NSString *)key { 
	if (DEBUG) NSLog(key);
    if ([key isEqualToString: @"serverName"]) return YES; 
    return NO; 
}


-(NSString *)serverName
{
	if (DEBUG) NSLog(@"EHModel:Getter");
	return mHeapname;
}

-(void)setServerName:(NSString *)iEheapName
{
	if (DEBUG) NSLog(@"EHModel:Setter");
	//NSLog(mHeapname);
	mHeapname = [[NSString alloc] initWithString:iEheapName]; //?????
	//mHeapname initWithString:iEheapName];
	//[@"" stringByAppendingString:iEheapName]; 
	//NSLog(mHeapname);
	NSLog([@"Connecting to " stringByAppendingString: mHeapname]);
	[mHeapAdapter createEventHeap:@"applescriptinterface" atServer:mHeapname atPort:4535];
	NSLog([@"Connected to " stringByAppendingString: mHeapname]);
}




//iEvent holds all information that can create an event
-(void) sendEvent: (EHEvent *)iEvent
{
	//Strange, it seems that I have to realloc a new eventheap before sending the event
	//This might waste a lot of time?!
	//mHeap  = [[EventHeap alloc] init];
	//[mHeapAdapter createEventHeap:@"applescriptinterface" atServer:mHeapname atPort:4535];	
	//[mHeapAdapter postEvent:[mEventHeap createEvent: @"test send  from ehemodel"]];
	if (DEBUG) NSLog(@"posting");	
	NSLog(@"posting");	
	eh2_EventPtr* oEvent = [mHeapAdapter createEvent: [iEvent getType]];
	
	
	NSEnumerator *enumerator = [[iEvent fields] keyEnumerator];
	id fieldName;
	
	while ((fieldName = [enumerator nextObject])) {
		NSLog(fieldName);	
		NSString * fieldVal = [[iEvent fields] objectForKey:fieldName];
		
		NSString *type = [[iEvent fieldTypes]objectForKey:fieldName];
		if (type){
			if ([type isEqualToString:@"i"]){
				(*oEvent)->setPostValueInt([fieldName UTF8String],[fieldVal intValue]);	
			}
			else if ([type isEqualToString:@"d"]){
				(*oEvent)->setPostValueDouble([fieldName UTF8String],[fieldVal doubleValue]);	
			}
			else if ([type isEqualToString:@"f"]){
				(*oEvent)->setPostValueFloat([fieldName UTF8String],[fieldVal  floatValue]);	
			}
			else if ([type isEqualToString:@"b"]){
				if ([fieldVal isEqualToString:@"YES"] || [fieldVal isEqualToString:@"1"] || [fieldVal isEqualToString:@"T"] || [fieldVal isEqualToString:@"TRUE"]){
					(*oEvent)->setPostValueBoolean([fieldName UTF8String],YES);
				}
				else{
					(*oEvent)->setPostValueBoolean([fieldName UTF8String],NO);
				}						
			}
			//long??
		}
		else { //by default, if no type is specified, treat it as a string
			(*oEvent)->setPostValueString([fieldName UTF8String],[fieldVal UTF8String]);	
		}
		//Can we set the template value to a value that is not "VIRTUAL"?
		//(*oEvent)->setTemplateValueString([fieldName UTF8String], "FORMAL");
	}
	NSLog(@"out of loop");	
	[mHeapAdapter postEvent: oEvent];
}

@end