#import "EHASMediator.h"

@implementation EHASMediator

/**
This object communicates with the event heap and execute the script conained in an event.
*/


-init
{
	self = [super init];
	if (self){
		//mEventHeap = [[EventHeap alloc]init];
		//[mEventHeap setEventProcessor:self];
		//[mEventHeap createEventHeap:@"CocoaAppleScriptProxy" atServer:@"127.0.0.1" atPort:4535];
		scriptHasErred = NO;
	}
	return self;
}

-dealloc
{
	[mEventHeap release];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//Not used yet, but later, the EventHeap object should use this method to get event templaes
-(eh2_EventPtr) getTemplateEvent
{
	eh2_EventPtr res = eh2_Event::cs_create ();
	res->setEventType ("AppleScript");
	res->allocateField("script",eh2_FieldType::cs_string());
	res->setTemplateValueString("script","FORMAL");
	return res;
}

/*
EventHeap object calls this method to process the incoming event.
Depending on the script, it will return a result in a "content" field or generate an error.
Lster: maybe return a collection of events. 
 */
-(eh2_EventPtr)processEvent:(eh2_EventPtr) iEventPtr
{
	if (!(iEventPtr->fieldExists("script"))) return nil;
	//Get the script, use executeScript
	NSString * script  = [NSString stringWithCString:iEventPtr->getPostValueString("script")];
	
	//Call execute
	NSString *res  = [self executeScript:script];
	
	//create event with result
	eh2_EventPtr eventPtr = eh2_Event::cs_create ("AppleScript");	
	eventPtr->allocateField("type",eh2_FieldType::cs_string());
	if (scriptHasErred){
		eventPtr->setPostValueString ("type", "error");
	}
	else{
		eventPtr->setPostValueString ("type", "result");
	}
	
	if ([res length]>0){
		eventPtr->allocateField("content",eh2_FieldType::cs_string());
		eventPtr->setPostValueString("content",[res UTF8String]);
	}
	
	eventPtr->allocateField("TimeToLive",eh2_FieldType::cs_int());
	eventPtr->setPostValueInt("TimeToLive",1000);
	return eventPtr;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*Exeucte an applescript. If error occurs, the error message will be returned, else returning the result of the script.
*/
-(NSString *)executeScript:(NSString *)iScript
{
	NSString * res = @"";
	NSAppleScript *aScript = [[NSAppleScript alloc] initWithSource: iScript];
	if (aScript){
		NSMutableDictionary *mDict = [[NSMutableDictionary alloc]initWithCapacity:10];
		BOOL compileErr = [aScript compileAndReturnError: &mDict];
		//NSLog(@"compiled and return %i",compileErr);

		NSAppleEventDescriptor * executeRes = [aScript executeAndReturnError: &mDict]; 
		
		if ([mDict count]>0){
			NSLog(@"Error occured");
			/*
			 Error dictionaryhas the following fields. These will eventually be filled after executeAndReturnError was called.
			 NSAppleScriptErrorNumber
			 NSAppleScriptErrorBriefMessage
			 NSAppleScriptErrorMessage
			 NSAppleScriptErrorRange
			 //This pattern is used to traverse throug the entries of the error dictionary
			 NSEnumerator *enumerator = [mDict keyEnumerator];
			 id key;
	 		 while ((key = [enumerator nextObject])) {
				NSLog(key);
			}
			*/
			scriptHasErred = YES;
			res = [mDict objectForKey:@"NSAppleScriptErrorMessage"];
		}
		else{
			scriptHasErred = NO;
			res  =[executeRes stringValue];
		}
	}
	else{
		res = @"init failed";
		NSLog(res);
	}
	//NSLog(res);
	return res;
}
@end
