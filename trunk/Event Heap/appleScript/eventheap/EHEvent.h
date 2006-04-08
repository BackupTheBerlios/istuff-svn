//
//  EHEvent.h
//  eventheap
//
//  Created by eugen on Wed Apr 05 2006.
//  Copyright (c) 2006 RWTH Aachen, Germany; Lehrstuhl Informatik 10 -Media Computing Group. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface EHEvent : NSObject {

	NSString * mtype;
	//A dictonary containing the fields:  {myField1:myValueStr1}
	//myField1 is an arbitrary string, can even contain space.
	//If fieldname(e.g.myField1) starts with ", then another " is expected at the end of the string. Both of this 
	// characters will be omitted. (later, the string will be checked for escape sequence)
	
	//Value is another string. By default, the value is interpreted as string.
	//The datatype can be specified by a postfic character:
	//i: integer
	//f: float
	//d: double
	//b: boolean
	//l: long
	NSMutableDictionary * fields;
	NSMutableDictionary * fieldTypes;
}

-(NSString *) getType;
-(void) setType:(NSString *)iTypeName;
-(NSDictionary *)fields;
-(NSDictionary *)fieldTypes;
-(void)setValue:(id)anObject forField:(id)aKey;

@end
