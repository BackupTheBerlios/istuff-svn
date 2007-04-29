#import "MyController.h"

@implementation MyController

- (id) init
{
	if (self = [super init]) {
	}
	
	return self;
}



- (void) dealloc
{
	[super dealloc];
}



- (IBAction) postEventsButton:(id)sender
{
	[self postEvents];
}



- (void) awakeFromNib
{
}



- (void) postEvents
{
	//eh2_EventPtr *event; // = [eventHeap createEvent];
	eh2_EventPtr *event; //, *event2, *event3, *event4, *event5, *event6, *event7, *event8;
	
	// define the language model to recognize

	/*event = [eventHeap createEvent];
	[eventHeap putStrKey:"newLanguage" andStrValue:"<commands>" toEvent:event];
	[eventHeap putStrKey:"entries"		andIntValue:9			toEvent:event];
	[eventHeap putStrKey:"phrase1"		andStrValue:"open"		toEvent:event];
	[eventHeap putStrKey:"phrase2"		andStrValue:"close"		toEvent:event];
	[eventHeap putStrKey:"phrase3"		andStrValue:"copy"		toEvent:event];
	[eventHeap putStrKey:"phrase4"		andStrValue:"cut"		toEvent:event];
	[eventHeap putStrKey:"phrase5"		andStrValue:"paste"		toEvent:event];
	[eventHeap putStrKey:"phrase6"		andStrValue:"insert"	toEvent:event];
	[eventHeap putStrKey:"phrase7"		andStrValue:"start"		toEvent:event];
	[eventHeap putStrKey:"phrase8"		andStrValue:"quit"		toEvent:event];
	[eventHeap postEvent:event];

	// activate the language model
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"activateLanguage" andStrValue:"<commands>" toEvent:event];
	[eventHeap postEvent:event]; */

	
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"newLanguage" andStrValue:"<make a call>" toEvent:event];
	[eventHeap postEvent:event];
	
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"newLanguage"  andStrValue:"<call>"	toEvent:event];
	[eventHeap putStrKey:"entries"		andIntValue:3			toEvent:event];
	[eventHeap putStrKey:"phrase1"		andStrValue:"call"		toEvent:event];
	[eventHeap putStrKey:"phrase2"		andStrValue:"phone"		toEvent:event];
	[eventHeap putStrKey:"phrase3"		andStrValue:"dial"		toEvent:event];
	[eventHeap postEvent:event];

	event = [eventHeap createEvent];
	[eventHeap putStrKey:"newLanguage"  andStrValue:"<person>"  toEvent:event];
	[eventHeap putStrKey:"entries"		andIntValue:5			toEvent:event];
	[eventHeap putStrKey:"phrase1"		andStrValue:"daniel"	toEvent:event];
	[eventHeap putStrKey:"phrase2"		andStrValue:"teeco"		toEvent:event];
	[eventHeap putStrKey:"phrase3"		andStrValue:"eric"		toEvent:event];
	[eventHeap putStrKey:"phrase4"		andStrValue:"stefan"	toEvent:event];
	[eventHeap putStrKey:"phrase5"		andStrValue:"ingo"		toEvent:event];
	[eventHeap postEvent:event];

	event = [eventHeap createEvent];
	[eventHeap putStrKey:"newPath"  andStrValue:"call person..." toEvent:event];
	[eventHeap postEvent:event];

	event = [eventHeap createEvent];
	[eventHeap putStrKey:"appendLanguage"   andStrValue:"<call>"			toEvent:event];
	[eventHeap putStrKey:"toPath"			andStrValue:"call person..."	toEvent:event];
	[eventHeap postEvent:event];

	event = [eventHeap createEvent];
	[eventHeap putStrKey:"appendLanguage"   andStrValue:"<person>"			toEvent:event];
	[eventHeap putStrKey:"toPath"			andStrValue:"call person..."	toEvent:event];
	[eventHeap postEvent:event];
	
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"addAlternativePath"	andStrValue:"call person..."	toEvent:event];
	[eventHeap putStrKey:"toLanguage"			andStrValue:"<make a call>"		toEvent:event];
	[eventHeap postEvent:event];
	
	// activate the language model
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"activateLanguage" andStrValue:"<make a call>" toEvent:event];

	[eventHeap postEvent:event];

	/*
	// add an alternative phrase to <person>
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"addAlternativePhrase"	andStrValue:"jan"		toEvent:event];
	[eventHeap putStrKey:"toLanguage"			andStrValue:"<person>"  toEvent:event];
	[eventHeap postEvent:event];
	
	// remove an alternative phrase from <person>
	event = [eventHeap createEvent];
	[eventHeap putStrKey:"removeAlternativePhrase"  andStrValue:"jan"		toEvent:event];
	[eventHeap putStrKey:"fromLanguage"				andStrValue:"<person>"  toEvent:event];
	[eventHeap postEvent:event];

	// empty the contents of <person>
	//event = [eventHeap createEvent];
	//[eventHeap putStrKey:"emptyLanguage" andStrValue:"<person>" toEvent:event];
	//[eventHeap postEvent:event];
	*/
}



// process the received Event Heap event
//
- (void) processReceivedEvent:(eh2_EventPtr)event
{
	// print debug info to terminal
	NSLog (@"processing Event Heap event...\n");
	
	// get the type of the event
	const char* eventType = event->getEventType ();
	if (strcmp (eventType, "SpeechServer") != 0) {
		NSLog (@"unknown event type received: %s\n", eventType);
	}
	else {		
		// this is the easiest way to get a value.
		// if something is wrong, an exception should occur
		const char* text = event->getPostValueString ("Full utterance");
		
		// print debug info to terminal
		NSLog (@"received event contains full utterance \"%s\"\n", text);
	}
}

@end
