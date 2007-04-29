#import "MyController.h"

@implementation MyController

// initialize instance variables
//
- (id) init
{
	if (self == [super init]) {
		// nothing to post yet
		eventToPost = NULL;
		temporaryLanguageName = NULL;
	}
	
	return self;
}



- (void) dealloc
{
	[super dealloc];
}



// start the recognizer
//
- (void) awakeFromNib
{
	// enable/disable recognition depending on status of speech switch
	[self toggleSpeechRecognitionOnSpeechSwitchStatus];

	// ********************
	// create a new language model <call>
	//[recognizer newLanguage: @"<call>"];
	//[recognizer addAlternativePhrase:@"call"	toLanguageModel:@"<call>"];
	//[recognizer addAlternativePhrase:@"phone"   toLanguageModel:@"<call>"];
	//[recognizer addAlternativePhrase:@"dial"	toLanguageModel:@"<call>"];

	// create a new language model <person>
	//[recognizer newLanguage:@"<person>"];
	//[recognizer addAlternativePhrase:@"daniel"		toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"teeco"		toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"eric"		toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"ingo"		toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"jan"			toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"stefan"		toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"jonathan"	toLanguageModel:@"<person>"];
	//[recognizer addAlternativePhrase:@"marius"		toLanguageModel:@"<person>"];

	// create a new path to concatenate the two language models
	//[recognizer newPath:@"call person..."];
	//[recognizer appendLanguageModel:@"<call>"   toPath:@"call person..."];
	//[recognizer appendLanguageModel:@"<person>" toPath:@"call person..."];

/*
	// ********************
	// create a new language model <date>
	[recognizer newLanguage:@"<date>"];
	[recognizer addAlternativePhrase:@"day"		toLanguageModel:@"<date>"];
	[recognizer addAlternativePhrase:@"month"   toLanguageModel:@"<date>"];
	[recognizer addAlternativePhrase:@"year"	toLanguageModel:@"<date>"];
	[recognizer addAlternativePhrase:@"time"	toLanguageModel:@"<date>"];
	
	// create a new path to concatenate the two language models
	[recognizer newPath:@"what date is it..."];
	[recognizer appendPhrase:@"what"			toPath:@"what date is it..."];
	[recognizer appendLanguageModel:@"<date>"   toPath:@"what date is it..."];
	[recognizer appendPhrase:@"is it"			toPath:@"what date is it..."];

	// ********************
	// create a new language model
	[recognizer newLanguage:@"<action>"];
	[recognizer addAlternativePhrase: @"open"   toLanguageModel:@"<action>"];
	[recognizer addAlternativePhrase: @"start"  toLanguageModel:@"<action>"];
	[recognizer addAlternativePhrase: @"launch" toLanguageModel:@"<action>"];
	[recognizer addAlternativePhrase: @"close"  toLanguageModel:@"<action>"];
	[recognizer addAlternativePhrase: @"quit"   toLanguageModel:@"<action>"];
	[recognizer addAlternativePhrase: @"exit"   toLanguageModel:@"<action>"];
	
	// create a new language model
	[recognizer newLanguage:@"<object>"];
	[recognizer addAlternativePhrase: @"finder"		toLanguageModel:@"<object>"];
	[recognizer addAlternativePhrase: @"mail"		toLanguageModel:@"<object>"];
	[recognizer addAlternativePhrase: @"safari"		toLanguageModel:@"<object>"];
	[recognizer addAlternativePhrase: @"word"		toLanguageModel:@"<object>"];
	[recognizer addAlternativePhrase: @"excel"		toLanguageModel:@"<object>"];
	[recognizer addAlternativePhrase: @"powerpoint" toLanguageModel:@"<object>"];

	// create a new path to concatenate the two language models
	[recognizer newPath:@"action object..."];
	[recognizer appendLanguageModel:@"<action>" toPath:@"action object..."];
	[recognizer appendLanguageModel:@"<object>" toPath:@"action object..."];
*/

	// ********************
	//create a new (top) language model and add other paths/language models to it
	//[recognizer newLanguage:@"<top_1>"];
	//[recognizer addAlternativePath:@"call person..." toLanguageModel:@"<top_1>"];
//	[recognizer addAlternativePath:@"what date is it..." toLanguageModel:@"<top_1>"];
//	[recognizer addAlternativePath:@"action object..." toLanguageModel:@"<top_1>"];

	// activate the language model you want to recognize, don't activate a path !
	//[recognizer activateLanguage:@"<top_1>"];
	//[recognizer activateLanguage:@"<person>"];

	//[recognizer addAlternativePhrase:@"hello" toLanguageModel:@"<top_1>"];

	// ********************
	// count items contained in language objects
	//[recognizer countItems:@"<top_1>"];
	//[recognizer countItems:@"<call>"];
	//[recognizer countItems:@"<person>"];
	//[recognizer countItems:@"call person..."];
//	[recognizer countItems:@"<date>"];
//	[recognizer countItems:@"what date is it..."];
//	[recognizer countItems:@"<action>"];
//	[recognizer countItems:@"<object>"];
//	[recognizer countItems:@"action object..."];
}



// toggle speech recognition on/off if checkbox clicked
//
- (IBAction) recognizeSpeech:(id)sender
{
	// start to listen for speech if checkbox enabled
	if ([sender state] == NSOnState) {
		[recognizer startListening];
	}
	// stop speech recognizer if checkbox disabled
	else if ([sender state] == NSOffState) {
		[recognizer stopListening];
	}
}



// enable / disable recognizer depending on status of "Recognize speech" switch
//
- (void) toggleSpeechRecognitionOnSpeechSwitchStatus
{
	// start to listen for speech if checkbox is enabled
	if ([recognizeSpeechSwitch state] == NSOnState)
		[recognizer startListening];
	else if ([recognizeSpeechSwitch state] == NSOffState)
		[recognizer stopListening];
}



// remove existing language objects and reset the speech recognizer
//
- (IBAction) resetSpeechRecognizer:(id)sender
{
	[recognizer resetLanguageAndRecognizer];
	
	// update listening status
	[self toggleSpeechRecognitionOnSpeechSwitchStatus];
}



// update the textfield in the user interface with the recognized utterance
//
/* - (void) updateRecognizedText:(char *)text
{
	[textField setObjectValue:[NSString stringWithCString: (const char *) text]];
} */



// post utterance to Event Heap
// first, a new event is created if it does not exist yet
//
// as you put key/value pairs to the event, the key text will be saved in the instance variable "temporaryLanguageName" without putting it to the event
// only in the following call both the saved key and the new text are put into the event
// this is necesssary because the language model is processed recursively and we receive only one item in each recursion step
//
// a final call with text as NULL pointer posts the actual event to the heap
// this way I call only one method from within SpeechRecognizer to post events
//
- (void) postRecognizedText:(char *)text
{
	// create a new event and save its pointer in the instance variable
	if (eventToPost == NULL)
		eventToPost = [eventHeap createEvent];

	// save the language model's name to which the recognized utterance belongs
	if (temporaryLanguageName == NULL)
		temporaryLanguageName = text;
	// now you have the key/value pair
	else {
		// put the language name (key) and the recognized utterance (value) to the event
		[eventHeap putStrKey:temporaryLanguageName andStrValue:text toEvent:eventToPost];

		// delete the reference to the saved language name so we can save the next key in the next step
		temporaryLanguageName = NULL;
	}
	
	// post the previously created event to the EventHeap if text = NULL
	if (text == NULL) {
		[eventHeap postEvent:eventToPost];
		// create a new event in the next step
		eventToPost = NULL;
	}
}



// process the received Event Heap event
//
- (void) processEvent:(eh2_EventPtr)event
{
	// get the type of the event
	const char* eventType = event->getEventType ();
	
	if (strcmp (eventType, "SpeechClient") != 0) {
		NSLog (@"Unknown event type received: %s", eventType);
	}
	else {
		const eh2_Field* field;
			
		// define a new language model
		field = event->getField ("newLanguage");
		if (field != NULL)
			[self createNewLanguageModel:event];
			
		// activate a language model
		field = event->getField ("activateLanguage");
		if (field != NULL)
			[self activateLanguageModel:event];
			
		// add an alternative phrase to a language model
		field = event->getField ("addAlternativePhrase");
		if (field != NULL)
			[self addAlternativePhrase:event];

		// remove an alternative phrase from a language model
		field = event->getField ("removeAlternativePhrase");
		if (field != NULL)
			[self removeAlternativePhrase:event];
			
		// empty contents of a language model
		field = event->getField ("emptyLanguage");
		if (field != NULL)
			[self emptyLanguageModel:event];
			
		// add an alternative language model to a language model
		//field = event->getField ("addAlternativeLanguage");
		//if (field != NULL)
		//	[self addAlternativeLanguageModel:event];

		// add an alternative path to a language model
		field = event->getField ("addAlternativePath");
		if (field != NULL)
			[self addAlternativePath:event];
			
		// create a new path
		field = event->getField ("newPath");
		if (field != NULL)
			[self createNewPath:event];
			
		// append a language model to a path
		field = event->getField ("appendLanguage");
		if (field != NULL)
			[self appendLanguageModel:event];
	}

	/* // this is the easiest way to get a value.
	// if something is wrong, an exception should occur
	const char* text = event->getPostValueString ("newLanguage");
	
	// this is the complete way to get a value
	int age;
	const eh2_Field* field = event->getField ("AGE");
	if (field == NULL) {
		// the event has no age field
	}
	else if (! field->getType()->equals(eh2_FieldType::cs_int())) {
		// the field is not expected type
	}
	else if (field->isPostValueNull ()) {
		// the content of the value is null
	}
	else {
		// get the int value
		age = field->getPostValueInt ();
	} */
}



// create the new language model defined in the received event
//
- (void) createNewLanguageModel:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	char phrase[10];
	int entries;
	NSString *languageName;
	
	// get the language name
	field = event->getField ("newLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString: (const char*) text];
			[recognizer newLanguage:languageName];
		}
	}

	// get number of alternative entries
	field = event->getField ("entries");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_int())) {
			entries = field->getPostValueInt ();
		}
		// add each alternative phrase to the language model
		for (int i = 1; i <= entries; i++) {
			// concatenate number i to string "phrase"
			sprintf (phrase, "phrase%d", i);
			field = event->getField (phrase);
			// stop if entry i not defined by speech client
			if (field == NULL) {
				NSLog (@"error 1, incomplete language model defined");
				break;
			}
			if (field->getType()->equals(eh2_FieldType::cs_string())) {
				text = (char *) field->getPostValueString ();
				[recognizer addAlternativePhrase:[NSString stringWithCString:(const char *)text] toLanguageModel:languageName];
			}
		}
	}
}



// activate a language model to recognize
//
- (void) activateLanguageModel:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	
	// get the language name
	field = event->getField ("activateLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			[recognizer activateLanguage:[NSString stringWithCString:(const char*)text]];
		}
	}
}



// add an alternative phrase to a language model
//
- (void) addAlternativePhrase:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *languageName, *phrase;
	
	// get phrase
	field = event->getField ("addAlternativePhrase");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			phrase = [[NSString alloc] initWithCString:(const char*)text];			
		}
	}

	// get name of language
	field = event->getField ("toLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString:(const char*)text];
		}
	}
	
	// add phrase to language model
	[recognizer addAlternativePhrase:phrase toLanguageModel:languageName];
}



// remove an alternative phrase from a language model
//
- (void) removeAlternativePhrase:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *languageName, *phrase;
	
	// get phrase
	field = event->getField ("removeAlternativePhrase");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			phrase = [[NSString alloc] initWithCString:(const char*)text];			
		}
	}

	// get name of language
	field = event->getField ("fromLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString:(const char*)text];
		}
	}
	
	// remove phrase from language model
	[recognizer removeAlternativePhrase:phrase fromLanguageModel:languageName];
}



// empty the contents of a language model
//
- (void) emptyLanguageModel:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *languageName;

	// get name of language
	field = event->getField ("emptyLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString:(const char*)text];
		}
	}

	// empty contents of language model
	[recognizer emptyLanguageModel:languageName];
}



// add an alternative language model to a language model
// An alternative language model in a language model generates an error when posting the recognized result to the Event Heap 
// because we miss the key in the recursion step (we have only the value).
//
/* - (void) addAlternativeLanguageModel:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *languageName, *addon;
	
	// get name of alternative language model
	field = event->getField ("addAlternativeLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			addon = [[NSString alloc] initWithCString:(const char*)text];			
		}
	}

	// get name of language to which to add
	field = event->getField ("toLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString:(const char*)text];
		}
	}
	
	// add alternative language "addon" to language model
	[recognizer addAlternativeLanguageModel:addon toLanguageModel:languageName];
} */



// add an alternative path to a language model
//
- (void) addAlternativePath:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *languageName, *pathName;
	
	// get name of path
	field = event->getField ("addAlternativePath");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			pathName = [[NSString alloc] initWithCString:(const char*)text];			
		}
	}

	// get name of language to which to add
	field = event->getField ("toLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString:(const char*)text];
		}
	}
	
	// add alternative path to language model
	[recognizer addAlternativePath:pathName toLanguageModel:languageName];
}



// create a new path
//
- (void) createNewPath:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *pathName;
	
	// get the language name
	field = event->getField ("newPath");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			pathName = [[NSString alloc] initWithCString: (const char*) text];
			[recognizer newPath:pathName];
		}
	}
}



// append an alternative language model to a path
//
- (void) appendLanguageModel:(eh2_EventPtr)event
{
	const eh2_Field* field;
	char *text;
	NSString *languageName, *pathName;
	
	// get name of path
	field = event->getField ("appendLanguage");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			languageName = [[NSString alloc] initWithCString:(const char*)text];			
		}
	}

	// get name of language to which to add
	field = event->getField ("toPath");
	if (field != NULL) {
		if (field->getType()->equals(eh2_FieldType::cs_string())) {
			text = (char *) field->getPostValueString ();
			pathName = [[NSString alloc] initWithCString:(const char*)text];
		}
	}
	
	// add alternative path to language model
	[recognizer appendLanguageModel:languageName toPath:pathName];
}

@end
