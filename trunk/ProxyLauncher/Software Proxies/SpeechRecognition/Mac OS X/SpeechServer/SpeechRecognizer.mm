//
//  SpeechRecognizer.m
//  SpeechServer
//
//  Created by Daniel Spelmezan on Wed Mar 31 2004.
//  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
//

// there are some problems if you define multiple times the same language models and paths and add phrases to them!
// check this: starting SpeechServer and running (start/stop) SpeechClient multiple times will put the server in a loop - check output!

#import "SpeechRecognizer.h"
#import "LanguageObject.h"
#import "MyController.h"

// enclose all private methods here
@interface SpeechRecognizer (Private)
@end

@implementation SpeechRecognizer

// initialize instance variables and speech recognizer
//
- (id) init
{
	if (self == [super init]) {
		recognitionSystem = NULL;
		recognizer = NULL;
		
		// allocate new dictionary (release it in dealloc)
		languageObjectsDict = [[NSMutableDictionary alloc] init];
		
		// open recognition system and recognizer, install Apple event handler
		[self initSpeechRecognition];
	}

	return self;
}



// deallocate instance variables and close speech recognizer
//
- (void) dealloc
{
	// first, release Carbon SR language objects referenced in dictionary
	[self releaseLanguageObjectsFromDictionary];
	
	// release dictionary
	[languageObjectsDict release];
	
	// close speech recognition
	[self closeSpeechRecognition];
	
	[super dealloc];
}



// release all defined language objects, empty the contents of the dictionary, and reset the recognizer
//
- (OSErr) resetLanguageAndRecognizer
{
	NSLock *resetLock =[[NSLock alloc] init];
	[resetLock lock];
	
	// first, release Carbon SR language objects referenced in dictionary
	[self releaseLanguageObjectsFromDictionary];
	
	// empty the dictionary
	[languageObjectsDict removeAllObjects];

	// release recognizer and create a new one
	OSErr err = SRReleaseObject (recognizer);
	if (! err)
		err = SRNewRecognizer (recognitionSystem, &recognizer, kSRDefaultSpeechSource);
	
	NSLog (@"error %d, speech recognizer reset", err);
	
	[resetLock unlock];

	return err;
}



// release Carbon SR language objects referenced in dictionary
//
- (OSErr) releaseLanguageObjectsFromDictionary
{
	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	OSErr err = noErr;

	// get values from dictionary
	NSArray *valueArray = [[languageObjectsDict allValues] retain];
	
	// and release them
	for (unsigned index = 0; index < [languageObjectsDict count]; index++) {
		refLangObj = [valueArray objectAtIndex:index];
		speechLangObj = [refLangObj languageObject];

		// balance call to SRNewLanguageModel in newLanguageModel: (resp. SRNewPath in newPath:)
		err = SRReleaseObject ( (*speechLangObj) );
		
		// balance call to malloc for the new language object in newLanguageModel: (resp. newPath:)
		free (speechLangObj);
	}
	
	[valueArray release];

	NSLog (@"error %d, Carbon SR language objects deleted", err);
	
	return err;
}



// returns TRUE if Speech Recognition Manager is available
//
- (BOOL) speechRecognitionAvailable
{
	OSErr err;
	long version;
	BOOL response = FALSE;

	// version should be >= to 0x0150	
	err = Gestalt (gestaltSpeechRecognitionVersion, &version);
	if (! err)
		if (version >= 0x0150)
			response = TRUE;
			
	return response;
}



// open a recognition system and create a recognizer, install event handler (called by system when utterance is recognized)
//
- (OSErr) initSpeechRecognition
{
	OSErr err;
		
	// ensure that the Speech Recognition Manager is available
	if (! [self speechRecognitionAvailable])
		return kSRNotAvailable;
		
	// open the default recognition system
	err = SROpenRecognitionSystem (&recognitionSystem, kSRDefaultRecognitionSystemID);
	
	// choose feedback and listening modes
	if (! err) {
		short modes = kSRHasFeedbackHasListenModes;		// kSRHasFeedbackHasListenModes, kSRNoFeedbackHasListenModes, kSRNoFeedbackNoListenModes
		err = SRSetProperty (recognitionSystem, kSRFeedbackAndListeningModes, &modes, sizeof(modes));
	}
	
	// create a new recognizer
	if (! err)
		err = SRNewRecognizer (recognitionSystem, &recognizer, kSRDefaultSpeechSource);
	
	// set reference constant of rejected word if you don't want to use the defaulf 0
	//if (! err)
	//	err = [self setRejectedWordRefCon: 0];
	
	// install Apple event handler
	if (! err)
		err = AEInstallEventHandler (kAESpeechSuite, kAESpeechDone, (AEEventHandlerProcPtr) handleSpeechDone, (SInt32) self, FALSE);
	
	return err;
}



// dispose of recognizer and close recognition system
//
- (OSErr) closeSpeechRecognition
{
	OSErr err;
	
	// stop processing incoming sound
	err = SRStopListening (recognizer);
	
	// balance call to SRNewRecognizer in initSpeechRecognition
	err = SRReleaseObject (recognizer);
	
	// balance call to SROpenRecognitionSystem in initSpeechRecognition
	err = SRCloseRecognitionSystem (recognitionSystem);
	
	return err;
}



// start listening to speech
//
- (OSErr) startListening
{
	OSErr err = SRStartListening (recognizer);
	return err;
}



// stop listening to speech
//
- (OSErr) stopListening
{
	OSErr err = SRStopListening (recognizer);
	return err;
}



// set the rejected word's reference constant value (default is 0)
//
- (OSErr) setRejectedWordRefCon:(long)refCon
{
	OSErr err = noErr;
	SRWord rejectedWord = NULL;
	Size len = sizeof (rejectedWord);

	// get a reference to the rejected word
	err = SRGetProperty (recognitionSystem, kSRRejectedWord, &rejectedWord, &len);
	
	// set the refCon of the rejected word, so we can use it later when processing the search result
	if (! err)
		err = SRSetProperty (rejectedWord, kSRRefCon, &refCon, sizeof(refCon));

	// balance call to SRGetProperty
	if (rejectedWord)
		err = SRReleaseObject (rejectedWord);

	return err;
}



// returns the number of items contained in the language object
//
- (long) countItems:(NSString *)languageObjectName
{
	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	OSErr err;
	// number of items
	long count = 0;
	
	// get language object "languageObjectName" from dictionary
	refLangObj = [languageObjectsDict objectForKey:languageObjectName];
	
	// count items if language model exists
	if (refLangObj) {
		// get the reference to the SR language object
		speechLangObj = [refLangObj languageObject];
	
		err = SRCountItems ((*speechLangObj), &count);
		//NSLog (@"error %d, countItems:%s = %ld", err, [languageObjectName cString], count);
	}
	else {
		err = 1;
		NSLog (@"error %d, countItems:%s, argument does not exist", err, [languageObjectName cString]);
	}

	return count;
}



// activate the language model that you want to recognize (languageName is saved in the dictionary)
//
- (OSErr) activateLanguage:(NSString *)languageName
{
	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	OSErr err = noErr;

	// get language model "languageName" from dictionary
	refLangObj = [languageObjectsDict objectForKey:languageName];

	// activate language model if it exists
	if (refLangObj) {
		// get the reference to the SR language object
		speechLangObj = [refLangObj languageObject];

		// set active language only if it is a language object
		if ([refLangObj isLanguageType:@"language"]) {
			err = SRSetLanguageModel (recognizer, (*speechLangObj));
			NSLog (@"error %d, activateLanguage:%s", err, [languageName cString]);
		}
		else {
			err = 1;
			NSLog (@"error %d, activateLanguage:%s, argument is not a language model", err, [languageName cString]);
		}
	}
	else {
		err = 1;
		NSLog (@"error %d, activateLanguage:%s, argument does not exits", err, [languageName cString]);
	}

	return err;
}



// return the plain text of a speech object
//
- (OSErr) getSpelling:(Str255)str forSpeechObject:(SRSpeechObject *)speechObject
{
	Size len = 255;

	OSErr err = SRGetProperty ((*speechObject), kSRSpelling, str, &len);
	
	// append a null terminating character to the text since SRGetProperty does not add one
	if(! err) {
		str[len] = '\0';
	}
	
	return err;
}



// Apple event handler called by system if speech recognized
//
pascal OSErr handleSpeechDone (AppleEvent *theAEevt, AppleEvent *reply, long refCon)
{
	// refCon contains "self" so we can call the Cocoa handleSpeechDone: method below
	SpeechRecognizer *newRecognizer = (SpeechRecognizer *) refCon;

	//NSAutoreleasePool *localPool;
	//localPool = [[NSAutoreleasePool alloc] init];

	pascal OSErr err = [newRecognizer handleSpeechDone:theAEevt withReply:reply withRef:refCon];

	//[localPool release];

	return err;
}



// method to process recognized utterance
//
- (pascal OSErr) handleSpeechDone:(AppleEvent *)theAEevt withReply:(AppleEvent *)reply withRef:(long)refCon
{
	long actualSize;
	DescType actualType;
	OSErr recStatus = 0, err = noErr;
	SRRecognitionResult recResult;
	SRRecognizer myRec;
	
	// get recognition result status and recognizer
	err = AEGetParamPtr (theAEevt, keySRSpeechStatus, typeShortInteger, &actualType, (Ptr) &recStatus, sizeof (recStatus), &actualSize);
	if (! err)
		err = recStatus;
	
	if (! err) {
		err = AEGetParamPtr (theAEevt, keySRRecognizer, typeSRRecognizer, &actualType, (Ptr) &myRec, sizeof (myRec), &actualSize);
		
		if (! err) {
			// get reference to recResult
			err = AEGetParamPtr (theAEevt, keySRSpeechResult, typeSRSpeechResult, &actualType, (Ptr) &recResult, sizeof(recResult), &actualSize);
			
			// process the recognition result here
			if (! err) {
				// get the spelling of the utterance and browse the language result recursively
				[self processRecognitionResult:&recResult];

				// release the reference to recResult
				SRReleaseObject (recResult);
			}
		}
	}
	
	return err;
}





// create a new language model if it does not yet exist
// QUESTION: delete its contents if it already exists ?
// we don't need different reference constants for different utterances
// but we will use < 0 for irrelevant utterances, 0 for unregognized utterances, > 0 for relevant utterances
//
- (OSErr) newLanguage:(NSString *)languageName
{
	OSErr err = noErr;
	
	// a language model is a relevant utterance in the recognition result, so set its refCon to 1
	long refCon = 1;
	
	// the language model does not yet exist
	// create a new language model and save its reference in the dictionary
	if ([languageObjectsDict objectForKey:languageName] == nil) {
		// allocate memory for a new language model (free memory in dealloc)
		SRLanguageModel *newLM = (SRLanguageModel *) malloc (sizeof(SRLanguageModel));

		// create a new language model (release in dealloc)
		err = SRNewLanguageModel (recognitionSystem, newLM, [languageName cString], strlen([languageName cString]));
	
		// set the reference constant for the new language model
		if (! err)
			err = SRSetProperty ((*newLM), kSRRefCon, &refCon, sizeof (refCon));

		// now save both the pointer to the new language model (via class LanguageObject)
		// and the language name in the dictionary
		
		// allocate a new LanguageObject to save the reference to newLM
		LanguageObject *refLangObj = [[LanguageObject alloc] init];
		[refLangObj setLanguageObject:newLM ofType:@"language"];

		// add the language object with its reference to the dictionary
		[languageObjectsDict setObject:refLangObj forKey:languageName];
		
		// release LanguageObject since it's retained in the dictionary
		[refLangObj release];
		
		NSLog (@"error %d, newLanguage:%s", err, [languageName cString]);
	}
	// empty the contents of the existing language model
	else {
	//	err = [self emptyLanguageModel:languageName];
		//NSLog (@"error %d, newLanguage:%s, contents of existing language model removed", err, [languageName cString]);
		
		err = 1;
		NSLog (@"error %d, newLanguage:%s already exists", err, [languageName cString]);
	}

	return err;
}



// create a new path if it does not yet exist
// QUESTION: delete its contents if it already exists ?
//
- (OSErr) newPath:(NSString *)pathName
{
	OSErr err = noErr;
	
	// a path is a relevant utterance in the recognition result, so set its refCon to 1
	long refCon = 1;

	// the path does not yet exist
	// create a new path and save its reference in the dictionary
	if ([languageObjectsDict objectForKey:pathName] == nil) {
		//allocate memory for a new path (free memory in dealloc)
		SRPath *newPath = (SRPath *) malloc (sizeof(SRPath));
	
		// create a new path (release reference in dealloc)
		err = SRNewPath (recognitionSystem, newPath);
		
		// set the reference constant for the path
		if (! err)
			err = SRSetProperty ((*newPath), kSRRefCon, &refCon, sizeof (refCon));
	
		// now save both the pointer to the new path (via class LanguageObject)
		// and the path name in the dictionary
		
		// allocate a new LanguageObject to save the reference to newPath
		LanguageObject *refLangObj = [[LanguageObject alloc] init];
		[refLangObj setLanguageObject:newPath ofType:@"path"];

		// add the language object with its reference to the dictionary
		[languageObjectsDict setObject:refLangObj forKey:pathName];
	
		// release LanguageObject since it's retained in the dictionary
		[refLangObj release];
		
		NSLog (@"error %d, newPath:%s", err, [pathName cString]);
	}
	// empty the contents of the existing path
	else {
	//	[self emptyPath:pathName];
		//NSLog (@"error %d, newPath:%s, contents of existing path removed", err, [pathName cString]);
		
		err = 1;
		NSLog (@"error %d, newPath:%s already exists", err, [pathName cString]);
	}

	return err;
}



/* // Don't use this method. It's only for repeatable-/optional-flag test reasons
// CAUTION !!! The phrase will be a SR language object with phraseName as the text
//
// create a new phrase if it does not yet exist
// delete its contents if it already exists
//
- (OSErr) newPhrase:(NSString *)phraseName
{
	OSErr err = noErr;
	
	// a new phrase is an irrelevant utterance in the recognition result, so set its refCon to -1
	long refCon = -1;

	// the phrase does not yet exist
	// create a new phrase and save its reference in the dictionary
	if ([languageObjectsDict objectForKey:phraseName] == nil) {
		//allocate memory for a new path (free memory in dealloc)
		SRPhrase *newPhrase = malloc (sizeof(SRPhrase));
	
		// create a new phrase (release reference in dealloc)
		err = SRNewPhrase (recognitionSystem, newPhrase, [phraseName cString], strlen([phraseName cString]));
		
		// set the reference constant for the phrase
		if (! err)
			err = SRSetProperty ((*newPhrase), kSRRefCon, &refCon, sizeof (refCon));
	
		// now save both the pointer to the new path (via class LanguageObject)
		// and the path name in the dictionary
		
		// allocate a new LanguageObject to save the reference to newPath
		LanguageObject *refLangObj = [[LanguageObject alloc] init];
		[refLangObj setLanguageObject:newPhrase];

		// add the language object with its reference to the dictionary
		[languageObjectsDict setObject:refLangObj forKey:phraseName];
	
		// release LanguageObject since it's retained in the dictionary
		[refLangObj release];
		
		NSLog (@"error %d, newPhrase, phrase \"%s\" created", err, [phraseName cString]);
	}
	// the phrase already exists
	// empty the contents of the phrase
	else {
		[self emptyPath:phraseName];
		NSLog (@"error %d, newPhrase, contents of existing phrase \"%s\" removed", err, [phraseName cString]);
	}

	return err;
} */





// add an alternative phrase to a language model
// create a new SRPhrase object for the phrase so we can easily remove it afterwards from the language model
// do not use SRAddText because you won't have any reference to the phrase in the language model
//
- (OSErr) addAlternativePhrase:(NSString *)phraseName toLanguageModel:(NSString *)languageName
{
	OSErr err = noErr;

	// an alternative phrase is a relevant utterance in the recognition result, so set its refCon to 1
	long refCon = 1;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj, *refPhraseObj;
	SRLanguageObject *speechLangObj, *speechPhraseObj;

	// get the language / phrase object reference from the dictionary
	refLangObj = [languageObjectsDict objectForKey:languageName];
	refPhraseObj = [languageObjectsDict objectForKey:phraseName];
	
	// add the alternative phrase to the language model if the language model exists
	// create the phrase object if it does not exist yet
	if (refLangObj && [refLangObj isLanguageType:@"language"]) {
		// create the new phrase if it does not exist yet
		if (refPhraseObj == nil) {
			// allocate memory for a new phrase object (free memory in dealloc)
			SRPhrase *newPhrase = (SRPhrase *) malloc (sizeof(SRPhrase));
		
			// create a new phrase object (release reference in dealloc)
			err = SRNewPhrase (recognitionSystem, newPhrase, [phraseName cString], strlen([phraseName cString]));
		
			// set the reference constant for the phrase
			if (! err)
				err = SRSetProperty ((*newPhrase), kSRRefCon, &refCon, sizeof (refCon));
	
			// now save both the pointer to the new phrase (via class LanguageObject)
			// and the phrase name in the dictionary
		
			// allocate a new LanguageObject to save the reference to newPhrase
			refPhraseObj = [[LanguageObject alloc] init];
			[refPhraseObj setLanguageObject:newPhrase ofType:@"phrase"];

			// add the language object with its reference to the dictionary
			[languageObjectsDict setObject:refPhraseObj forKey:phraseName];
	
			// release LanguageObject since it's retained in the dictionary
			[refPhraseObj release];
		}
		
		// don't add if already added
		if ([self languageObject:languageName containsLanguageObject:phraseName]) {
			err = 1;
			NSLog (@"error %d, addAlternativePhrase:%s toLanguageModel:%s already added", err, [phraseName cString], [languageName cString]);
		}
		else {
			// get the reference to the SR language model
			speechLangObj = [refLangObj languageObject];
			speechPhraseObj = [refPhraseObj languageObject];		
	
			// add the phrase object to the language model object
			err = SRAddLanguageObject ((*speechLangObj), (*speechPhraseObj));
			NSLog (@"error %d, addAlternativePhrase:%s toLanguageModel:%s", err, [phraseName cString], [languageName cString]);
		}
	}
	// the language model does not exist
	else {
		err = 1;
		NSLog (@"error %d, addAlternativePhrase:%s toLanguageModel:%s, failed to add phrase to language", err, [phraseName cString], [languageName cString]);
	}

	return err;
}



// add a plain text phrase to a language object
// if the language object is a language model the phrase will be an alternative recognizable utterance
// if the language object is a path the phrase will be appended to the end of the path
// use a refCon of 1 (relevant utterance) if you add a phrase to a language model
// use a refCon of -1 (irrelevant utterance) if you add a phrase to a path
// repeatable/optional does not seem to work too well for phrases if set from here (better use newPhrase and set repeatable/optional flag manually)
//
// if you use this method to add a phrase to a langage model you won't have any reference to the phrase in the language model because of SRAddText
//
// SUGGESTION: make this generic method private
//
- (OSErr) addPhrase:(NSString *)phrase toLanguageObject:(NSString *)languageObjectName withRefCon:(long)refCon //asRepeatable:(BOOL)repeatable asOptional:(BOOL)optional
{
	OSErr err = noErr;
	//Size len;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	// the the language object reference from the dictionary
	refLangObj = [languageObjectsDict objectForKey:languageObjectName];
	
	// add the phrase to the language object if the object exists
	if (refLangObj) {
		// don't add if already added
		if ([self languageObject:languageObjectName containsLanguageObject:phrase]) {
			err = 1;
			NSLog (@"error %d, addPhrase:%s toLanguageObject:%s already added", err, [phrase cString], [languageObjectName cString]);
		}
		else {
			// get the reference to the SR language model
			speechLangObj = [refLangObj languageObject];
			err = SRAddText ((*speechLangObj), [phrase cString], strlen ([phrase cString]), refCon);
		
			// set the repeatable property
			//len = sizeof (repeatable);
			//err = SRSetProperty ((*speechLangObj), kSRRepeatable, &repeatable, len);

			// set the optional property
			//len = sizeof (optional);
			//err = SRSetProperty ((*speechLangObj), kSROptional, &optional, len);
		
			//NSLog (@"error %d, phrase \"%s\" added to language object \"%s\", as repeatable %d, as optional %d", err, [phrase cString], [languageObjectName cString], repeatable, optional);
			NSLog (@"error %d, addPhrase:%s toLanguageObject:%s", err, [phrase cString], [languageObjectName cString]);
		}
	}
	// the language object does not exist
	else {
		err = 1;
		NSLog (@"error %d, addPhrase:%s toLanguageObject:%s", err, [phrase cString], [languageObjectName cString]);
	}

	return err;
}

// add an alternative utterance with reference constant 1 (relevant utterance) to a language model
//
/* - (OSErr) addAlternativePhrase:(NSString *)phrase toLanguageModel:(NSString *)languageName //asRepeatable:FALSE asOptional:FALSE];
{
	// simply call the method above (addPhrase: toLanguageObject: withRefCOn:)
	return [self addPhrase:phrase toLanguageObject:languageName withRefCon:1]; //asRepeatable:FALSE asOptional:FALSE];
} */

// append a phrase with reference constant -1 (irrelevant utterance) to a path
//
- (OSErr) appendPhrase:(NSString *)phrase toPath:(NSString *)pathName //asRepeatable:(BOOL)repeatable asOptional:(BOOL)optional
{
	// simply call the method above (addPhrase: toLanguageObject: withRefCOn:)
	return [self addPhrase:phrase toLanguageObject:pathName withRefCon:-1]; //asRepeatable:repeatable asOptional:optional];
}





// add a language object to another language object
// the language object can either be a path or a language model
//
// SUGGESTION: make this generic method private
//
- (OSErr) addLanguageObject:(NSString *)languageObject_addon toLanguageObject:(NSString *)languageObject_base
{
	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj_base, *refLangObj_addon;
	SRLanguageObject *speechLangObj_base, *speechLangObj_addon;

	OSErr err = noErr;
	
	// get both language objects from dictionary
	refLangObj_base = [languageObjectsDict objectForKey:languageObject_base];
	refLangObj_addon = [languageObjectsDict objectForKey:languageObject_addon];

	// add the addon to base if both language objects exist
	if (refLangObj_base && refLangObj_addon) {
		// don't add if already added
		if ([self languageObject:languageObject_base containsLanguageObject:languageObject_addon]) {
			err = 1;
			NSLog (@"error %d, addLanguageObject:%s toLanguageObject:%s already added", err, [languageObject_addon cString], [languageObject_base cString]);
		}
		else {
			// get references to the both SR language objects
			speechLangObj_base = [refLangObj_base languageObject];
			speechLangObj_addon = [refLangObj_addon languageObject];
			err = SRAddLanguageObject ((*speechLangObj_base), (*speechLangObj_addon));
			NSLog (@"error %d, addLanguageObject:%s toLanguageObject:%s", err, [languageObject_addon cString], [languageObject_base cString]);
		}
	}
	else {
		err = 1;
		NSLog (@"error %d, addLanguageObject:%s toLanguageObject:%s", err, [languageObject_addon cString], [languageObject_base cString]);
		if (! refLangObj_base)
			NSLog (@" \"%s\" does not exist", [languageObject_base cString]);
		if (! refLangObj_addon)
			NSLog (@" \"%s\" does not exist", [languageObject_addon cString]);
	}
	
	return err;
}

// add an alternative language model to a language model
//
- (OSErr) addAlternativeLanguageModel:(NSString *)languageName toLanguageModel:(NSString *)base
{
	// simply call the method above (addLanguageObject: toLanguageObject:)
	return [self addLanguageObject:languageName toLanguageObject:base];
}

// add an alternative path to a language model
//
- (OSErr) addAlternativePath:(NSString *)pathName toLanguageModel:(NSString *)languageName
{
	// simply call the method above (addLanguageObject: toLanguageObject:)
	return [self addLanguageObject:pathName toLanguageObject:languageName];
}

// append a language model to a path
//
- (OSErr) appendLanguageModel:(NSString *)languageName toPath:(NSString *)pathName
{
	// simply call the method above (addLanguageObject: toLanguageObject:)
	return [self addLanguageObject:languageName toLanguageObject:pathName];
}

// append a path to a path
//
- (OSErr) appendPath:(NSString *)pathName toPath:(NSString *)base
{
	// simply call the method above (addLanguageObject: toLanguageObject:)
	return [self addLanguageObject:pathName toLanguageObject:base];
}





// empty the contents of a language object (= references to other objects it contains)
// don't remove the references from the dictionary (this is done in dealloc)
// the language object is either a language model or a path
//
- (OSErr) emptyLanguageObject:(NSString *)languageObjectName
{
	OSErr err = noErr;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	// get the language object reference from the dictionary
	refLangObj = [languageObjectsDict objectForKey:languageObjectName];
	
	// empty contents if the language object exists in the dictionary
	if (refLangObj) {
		// get the reference to the SR language model
		speechLangObj = [refLangObj languageObject];
		err = SREmptyLanguageObject ((*speechLangObj));
		NSLog (@"error %d, emptyLanguageObject:%s", err, [languageObjectName cString]);
	}
	// the language object does not exist in the dictionary
	else {
		err = 1;
		NSLog (@"error %d, emptyLanguageObject:%s, argument does not exist", err, [languageObjectName cString]);
	}

	return err;
}

// empty a language model
//
- (OSErr) emptyLanguageModel:(NSString *)languageName
{
	// simly call the method above (emptyLanguageObject:)
	return [self emptyLanguageObject:languageName];
}

// empty a path
//
- (OSErr) emptyPath:(NSString *)pathName
{
	// simly call the method above (emptyLanguageObject:)
	return [self emptyLanguageObject:pathName];
}





// remove a language object from another language object (but do not delete the dictionary entry)
//
- (OSErr) removeLanguageObject:(NSString *)languageObjectName fromLanguageObject:(NSString *)base
{
	OSErr err = noErr;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj_base, *refLangObj_language;
	SRLanguageObject *speechLangObj_base, *speechLangObj_language;
	
	// get the dictionary entry for both language objects
	refLangObj_base = [languageObjectsDict objectForKey: base];
	refLangObj_language = [languageObjectsDict objectForKey: languageObjectName];

	// remove language model "languageObjectName" from "base" if both exist
	if (refLangObj_base && refLangObj_language) {
		// get the reference to the Carbon SR language objects
		speechLangObj_base = [refLangObj_base languageObject];	
		speechLangObj_language = [refLangObj_language languageObject];
		err = SRRemoveLanguageObject ((*speechLangObj_base), (*speechLangObj_language));
		NSLog (@"error %d, removeLanguageObject:%s fromLanguageObject:%s", err, [languageObjectName cString], [base cString]);
	}
	// language object does not exist
	else {
		err = 1;
		NSLog (@"error %d, removeLanguageObject:%s fromLanguageObject:%s", err, [languageObjectName cString], [base cString]);
		if (! refLangObj_language)
			NSLog (@" \"%s\" does not exist", [languageObjectName cString]);
		if (! refLangObj_base)
			NSLog (@" \"%s\" does not exist", [base cString]);
	}

	return err;
}

// remove an alternative phrase from a language model
- (OSErr) removeAlternativePhrase:(NSString *)phrase fromLanguageModel:(NSString *)base
{
	// simply call the method above (removeLanguageObject: fromLanguageObject:)
	return [self removeLanguageObject:phrase fromLanguageObject:base];
}

// remove a language model from another language model
//
- (OSErr) removeLanguageModel:(NSString *)languageName fromLanguageModel:(NSString *)base
{
	// simply call the method above (removeLanguageObject: fromLanguageObject:)
	return [self removeLanguageObject:languageName fromLanguageObject:base];
}

// remove a language model from a path
//
- (OSErr) removeLanguageModel:(NSString *)languageName fromPath:(NSString *)pathName
{
	// simply call the method above (removeLanguageObject: fromLanguageObject:)
	return [self removeLanguageObject:languageName fromLanguageObject:pathName];
}

// remove a path from another language model
//
- (OSErr) removePath:(NSString *)pathName fromLanguageModel:(NSString *)base
{
	// simply call the method above (removeLanguageObject: fromLanguageObject:)
	return [self removeLanguageObject:pathName fromLanguageObject:base];
}

// remove a path from another path
//
- (OSErr) removePath:(NSString *)pathName fromPath:(NSString *)base
{
	// simply call the method above (removeLanguageObject: fromLanguageObject:)
	return [self removeLanguageObject:pathName fromLanguageObject:base];
}





// process reognition result, determine language model format and reference constants
//
- (OSErr) processRecognitionResult:(SRRecognitionResult *)recResult
{
	// this saves the recognized language model
	SRLanguageModel resultLM;
	// number of items in recognized language model
	long numberOfSubItems;
	// reference constant of language object
	//long refCon;
	// the name of the top language model
	Str255 str;

	Size len;
	OSErr err = noErr;
	
	// any result there ?
	if (recResult) {
		// first, get the recognized utterance as plain text
		err = [self getSpelling:str forSpeechObject:recResult];
		if (! err) {
			// put the recognized text as key/value pair to a new EventHeap event
			// the first call to postRecognizedText will generate a new event if it does not exist yet
			// SUGGESTION: DON't post when utterance is ???
			[myController postRecognizedText: "Full utterance"];
			[myController postRecognizedText: (char *) str];

			// print debug info to terminal
			NSLog (@"recognized: %s", str);
		}
		else
			// print debug info to terminal
			NSLog (@"error %d, could not get spelling of recognized utterance", err);

		// now, get the language model format of the recognized utterance
		len = sizeof (resultLM);
		err = SRGetProperty ((*recResult), kSRLanguageModelFormat, &resultLM, &len);
		// get the number of subitems
		err = SRCountItems (resultLM, &numberOfSubItems);
		// get the refCon of the subitem
		//len = sizeof (refCon);
		//err = SRGetProperty (resultLM, kSRRefCon, &refCon, &len);

		// process subitems recursively if any exist
		if (numberOfSubItems > 0) {
			// get the spelling of the top language model and announce it in an extra field in the EventHeap event
			err = [self getSpelling:str forSpeechObject:&resultLM];
			[myController postRecognizedText:"Top language"];
			[myController postRecognizedText:(char *) str];

			// print debug info to terminal
			NSLog (@"error %d, top language %s", err, str);
		
			// browse the recognized language tree recursively and add its subelements to the EventHeap event
			err = [self recursiveRefCon:&resultLM withSubItems:numberOfSubItems];
			
			// the NULL parameter posts the current event to the event heap
			[myController postRecognizedText:NULL];
		}

		// release reference fetched above in SRGetProperty (..., &resultLM, ...)
		err = SRReleaseObject (resultLM);
	}
	
	return err;
}



// get the recognized subItems recursively and send them to MyController to post them to the event heap
//
- (OSErr) recursiveRefCon:(SRLanguageObject *)languageObject withSubItems:(long)totalItems
{
	// subitem in the language object
	SRLanguageObject subItem;
	//number of items in the sub-language object
	long numberOfSubItems;
	// reference constant of the language object
	long refCon;
	// string of the recognized utterance of a sub-language object
	Str255 str;

	long i;
	Size len;
	OSErr err = noErr;
	
	// get the refCon of the language object
	len = sizeof (refCon);
	err = SRGetProperty ((*languageObject), kSRRefCon, &refCon, &len);
	
	// save recognized utterance as plain text only if it is relevant, i.e., refCon > 0
	if (refCon > 0) {
		err = [self getSpelling:str forSpeechObject:languageObject];
		
		// put the utterance to the event heap
		// two consecutive calls will result in a key/value pair being added to the event
		// i.e., the language model name and the corresponding utterance of the language model
		[myController postRecognizedText: (char *) str];

		// print the utterance to the terminal
		NSLog (@"error %d, string %s", err, str);
	}
		
	// get reference of sub-items and browse them recursively
	for (i = 0; i < totalItems; i++) {
			err = SRGetIndexedItem ((*languageObject), &subItem, i);

			// get number of subitems within the current subitem
			err = SRCountItems (subItem, &numberOfSubItems);
			
			// browse subitems recursively
			if (numberOfSubItems > 0)
				err = [self recursiveRefCon: &subItem withSubItems: numberOfSubItems];
	
			// balance call to SRGetIndexedItem
			err = SRReleaseObject (subItem);
	}
	
	return err;
}





// make the language object repeatable (TRUE) or not (FALSE)
//
- (OSErr) setRepeatableFlag:(BOOL)repeatableFlag forLanguageObject:(NSString *)languageObjectName
{
	OSErr err;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	Size len = sizeof (repeatableFlag);

	// get the language object reference from the dictionary
	refLangObj = [languageObjectsDict objectForKey:languageObjectName];

	// set the repeatable flag if language object exists
	if (refLangObj) {
		// get the reference to the language object
		speechLangObj = [refLangObj languageObject];
		err = SRSetProperty ((*speechLangObj), kSRRepeatable, &repeatableFlag, len);
		NSLog (@"error %d, setRepeatableFlag:%d forLanguageObject:%s", err, repeatableFlag, [languageObjectName cString]);
	}
	else {
		err = 1;
		NSLog (@"error %d, setRepeatableFlag:%d forLanguageObject:%s", err, repeatableFlag, [languageObjectName cString]);
	}
	
	return err;
}



// make the language object optional (TRUE) or not (FALSE)
//
- (OSErr) setOptionalFlag:(BOOL)optionalFlag forLanguageObject:(NSString *)languageObjectName
{
	OSErr err;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj;
	SRLanguageObject *speechLangObj;

	Size len = sizeof (optionalFlag);

	// get the language object reference from the dictionary
	refLangObj = [languageObjectsDict objectForKey:languageObjectName];

	// set the optional flag if language object exists
	if (refLangObj) {
		// get the reference to the language object
		speechLangObj = [refLangObj languageObject];
		err = SRSetProperty ((*speechLangObj), kSROptional, &optionalFlag, len);
		NSLog (@"error %d, setOptionalFlag:%d forLanguageObject:%s", err, optionalFlag, [languageObjectName cString]);
	}
	else {
		err = 1;
		NSLog (@"error %d, setOptionalFlag:%d forLanguageObject:%s", err, optionalFlag, [languageObjectName cString]);
	}
	
	return err;
}



// test whether or not the language object baseObj contains the language object anObj
// use this method before you add a phrase etc. to another language object,
// or you will duplicate it !
//
- (BOOL) languageObject:(NSString *)baseObj containsLanguageObject:(NSString *)anObj
{
	OSErr err = noErr;
	
	// dummy language object
	SRLanguageObject dummy;

	// LanguageObject that saves the pointer to a SR language object in the dictionary
	LanguageObject *refLangObj_base, *refLangObj_object;
	SRLanguageObject *speechLangObj_base, *speechLangObj_object;
	
	// get the dictionary entry for both language objects
	refLangObj_base = [languageObjectsDict objectForKey:baseObj];
	refLangObj_object = [languageObjectsDict objectForKey:anObj];

	speechLangObj_base = [refLangObj_base languageObject];
	speechLangObj_object = [refLangObj_object languageObject];

	// number of subitems in base object
	long items = [self countItems:baseObj];
	
	// compare all subitems to anObj
	for (long i = 0; i < items; i++) {
		err = SRGetIndexedItem ((*speechLangObj_base), &dummy, i);
		
		// match found
		if (dummy == (*speechLangObj_object)) {
			if (!err) SRReleaseObject (dummy);
			return TRUE;
		}
		else {
			if (!err) SRReleaseObject (dummy);
		}
	}
	
	// no match
	return FALSE;
}

@end
