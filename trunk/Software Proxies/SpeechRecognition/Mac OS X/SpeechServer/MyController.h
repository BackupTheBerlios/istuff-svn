/* MyController */

#import <Cocoa/Cocoa.h>
#import "SpeechRecognizer.h"
#import "EventHeap.h"

@interface MyController : NSObject
{
	// connections to user interface widgets
	IBOutlet NSButton *recognizeSpeechSwitch;
	
	// SpeechRecognizer is my Cocoa class that wraps the Carbon Speech Recognition API
	// EventHeap is my Cocoa class that wraps the Event Heap API
	IBOutlet SpeechRecognizer *recognizer;
	IBOutlet EventHeap *eventHeap;

	// event that will be posted to the Event Heap
	eh2_EventPtr *eventToPost;

	// temporarily save the pointer of the key you want to post to an Event Heap event (key/value pair = language object name/recognized utterance)
	char *temporaryLanguageName;
}

// toggle speech recognition on/off if checkbox clicked
- (IBAction) recognizeSpeech:(id)sender;
- (IBAction) resetSpeechRecognizer:(id)sender;

// check status of speech switch and enable/disable recognizer
- (void) toggleSpeechRecognitionOnSpeechSwitchStatus;

// post recognized utterance to Event Heap
- (void) postRecognizedText:(char *)text;

// process the received Event Heap event
- (void) processEvent:(eh2_EventPtr)event;

// process actions defined in Event Heap events
- (void) createNewLanguageModel:(eh2_EventPtr)event;
- (void) activateLanguageModel:(eh2_EventPtr)event;
- (void) addAlternativePhrase:(eh2_EventPtr)event;
- (void) removeAlternativePhrase:(eh2_EventPtr)event;
- (void) emptyLanguageModel:(eh2_EventPtr)event;
//- (void) addAlternativeLanguageModel:(eh2_EventPtr)event;
- (void) addAlternativePath:(eh2_EventPtr)event;

- (void) createNewPath:(eh2_EventPtr)event;
- (void) appendLanguageModel:(eh2_EventPtr)event;

@end
