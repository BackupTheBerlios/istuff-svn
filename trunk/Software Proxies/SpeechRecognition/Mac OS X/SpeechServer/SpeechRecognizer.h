//
//  SpeechRecognizer.h
//  SpeechServer
//
//  Created by Daniel Spelmezan on Wed Mar 31 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Carbon/Carbon.h>

// SpeechRecognizer is my Cocoa class that wraps the Carbon Speech Recognition API
//
@interface SpeechRecognizer : NSObject
{
	// myController is the connection to the MyControllerClass
	// it does not work with an explicit typecast
	IBOutlet id myController;
	
	// Carbon peech recognition system and recognizer
	SRRecognitionSystem recognitionSystem;
	SRRecognizer recognizer;
	
	// this Cocoa dictionary saves the names of and references to user defined language models and paths using class LanguageObject
	NSMutableDictionary *languageObjectsDict;
}


// returns TRUE if Speech Recognition Manager is available
- (BOOL) speechRecognitionAvailable;
// initialize the speech recognition engine (open a recognition system, create a recognizer, allocate the dictionary ...)
- (OSErr) initSpeechRecognition;
// dispose of recognizer and close recognition system, release dictionary ...
- (OSErr) closeSpeechRecognition;

// delete language models and reset recognizer
- (OSErr) resetLanguageAndRecognizer;

// release Carbon SR language objects referenced in dictionary
- (OSErr) releaseLanguageObjectsFromDictionary;

// start and stop listening to speech
- (OSErr) startListening;
- (OSErr) stopListening;

// set the rejection's word reference constant value
- (OSErr) setRejectedWordRefCon:(long)refCon;
// returns the number of items contained in the language object
- (long) countItems:(NSString *)languageObjectName;
// set active language model
- (OSErr) activateLanguage:(NSString *)languageName;

// Apple event handler has to be a C function, which is called by the system if speech has been recognized
pascal OSErr handleSpeechDone (AppleEvent *theAEevt, AppleEvent *reply, long refCon);
// this is the method called from within the Apple event handler C function (above) to handle the recognized utterance
- (pascal OSErr) handleSpeechDone:(AppleEvent *)theAEevt withReply:(AppleEvent *)reply withRef:(long)refCon;

// create a new language model
- (OSErr) newLanguage:(NSString *)languageName;
// create a new path
- (OSErr) newPath:(NSString *)pathName;

// add a phrase to a language object (language object is either a language model or a path)
- (OSErr) addPhrase:(NSString *)phrase toLanguageObject:(NSString *)languageObjectName withRefCon:(long)refCon; //asRepeatable:(BOOL)repeatable asOptional:(BOOL)optional;
// add an alternative utterance to a language model
- (OSErr) addAlternativePhrase:(NSString *)phrase toLanguageModel:(NSString *)languageName;
// append a phrase to a path
- (OSErr) appendPhrase:(NSString *)phrase toPath:(NSString *)pathName; //asRepeatable:(BOOL)repeatable asOptional:(BOOL)optional;

// add a language object to another language object
- (OSErr) addLanguageObject:(NSString *)languageObject_addon toLanguageObject:(NSString *)languageObject_base;
// add an alternative language model to a language model
- (OSErr) addAlternativeLanguageModel:(NSString *)languageName toLanguageModel:(NSString *)base;
// add an alternative path to a language model
- (OSErr) addAlternativePath:(NSString *)pathName toLanguageModel:(NSString *)languageName;
// append a language model to a path
- (OSErr) appendLanguageModel:(NSString *)languageName toPath:(NSString *)pathName;
// append a path to a path
- (OSErr) appendPath:(NSString *)pathName toPath:(NSString *)base;

// empty the contents of a language object but keep its references in the dictionary
- (OSErr) emptyLanguageObject:(NSString *)languageObjectName;
// empty a language model
- (OSErr) emptyLanguageModel:(NSString *)languageName;
// empty a path
- (OSErr) emptyPath:(NSString *)pathName;

// remove a language object from another language object
- (OSErr) removeLanguageObject:(NSString *)languageObjectName fromLanguageObject:(NSString *)base;
// remove an alternative phrase from a language model
- (OSErr) removeAlternativePhrase:(NSString *)phrase fromLanguageModel:(NSString *)base;
// remove a language model from another language model
- (OSErr) removeLanguageModel:(NSString *)languageName fromLanguageModel:(NSString *)base;
// remove a language model from a path
- (OSErr) removeLanguageModel:(NSString *)languageName fromPath:(NSString *)pathName;
// remove a path from another language model
- (OSErr) removePath:(NSString *)pathName fromLanguageModel:(NSString *)languageName;
// remove a path from another path
- (OSErr) removePath:(NSString *)pathName fromPath:(NSString *)base;

// process recognition result, determine language model format of recognized utterance
- (OSErr) processRecognitionResult:(SRRecognitionResult *)recResult;
// browse language model subitems recursively, get reference constant and utterance as string
- (OSErr) recursiveRefCon:(SRLanguageObject *)languageObject withSubItems:(long)totalItems;

// make a language object repeatable
- (OSErr) setRepeatableFlag:(BOOL)repeatableFlag forLanguageObject:(NSString *)languageObjectName;
// make a language object optional
- (OSErr) setOptionalFlag:(BOOL)optionalFlag forLanguageObject:(NSString *)languageObjectName;

// test whether or not the language object baseObj contains the language object anObj
- (BOOL) languageObject:(NSString *)baseObj containsLanguageObject:(NSString *)anObj;

@end
