//
//  LanguageObject.m
//  SpeechServer
//
//  Created by Daniel Spelmezan on Mon Apr 19 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import "LanguageObject.h"

@implementation LanguageObject

// initiate instance variables
//
- (id) init
{
	if (self == [super init]) {
		languageObject = NULL;
		languageType = nil;
	}

	return self;
}



// release the reference to the language object (if it's a valid reference)
//
- (void) dealloc
{
	if (languageObject)
		SRReleaseObject ( (*languageObject) );
		
	if (languageType)
		[languageType release];
	
	[super dealloc];
}



// save the pointer to the language object and its type
//
- (void) setLanguageObject:(SRLanguageObject *)langObj ofType:(NSString *)typeName
{
	if (languageObject)
		SRReleaseObject ( (*languageObject) );

	languageObject = langObj;
		
	if (languageType)
		[languageType release];

	languageType = [typeName retain];
}



// return the pointer to the language object
//
- (SRLanguageObject *) languageObject
{
	return languageObject;
}



// test the type of the language object
//
- (BOOL) isLanguageType:(NSString *)typeName
{
	if ([languageType compare:typeName] == NSOrderedSame)
		return TRUE;
	else
		return FALSE;
}

@end
