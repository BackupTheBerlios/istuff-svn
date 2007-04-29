//
//  LanguageObject.h
//  SpeechServer
//
//  Created by Daniel Spelmezan on Mon Apr 19 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Carbon/Carbon.h>

// LanguageObject is my Cocoa class that stores the pointer to a Carbon SR language object
// this way I can save the language object reference in a Cocoa dictionary
//
@interface LanguageObject : NSObject
{
	// pointer to a Carbon SR language object
	SRLanguageObject *languageObject;
	
	// the type of the language object (language, path, phrase)
	NSString *languageType;
}

// set / return the pointer to the language object
- (void) setLanguageObject:(SRLanguageObject *)langObj ofType:(NSString *)typeName;
- (SRLanguageObject *) languageObject;

// test the type of the language object
- (BOOL) isLanguageType:(NSString *)typeName;

@end
