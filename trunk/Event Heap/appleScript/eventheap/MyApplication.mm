#import "MyApplication.h"
#import "EHEvent.h"
#define DEBUG 0

@implementation MyApplication
//Have to catch this "NSInternalScriptError" to make the programm more robust

-init
{
	self = [super init];
    if (self) {
		//the following settings is not necessary, they were done in NIB. 
		//mEHModel = [[EHModel allocWithZone:[self zone]] init]; //Don't create model, I already have one inside nib
		//[self setDelegate: mEHModel];
		events = [[NSMutableArray alloc]init];
    }
	return self;
}

- (void)dealloc {
    //[_events release];
    //[mEHModel release];
    //[super dealloc];
}

//Method called when "send" is used in a applescript.
//All events stored in the array are sent to the event heap, and will be emptied.
- (id)handleSendCommand:(NSScriptCommand *)command {
	//Later traverser through array and send the event inside the array.
	//Thereafter clear the array
	if (DEBUG) NSLog(@"handling send by app");
	
	//[mEHModel setEventheapName:@"parker"];
	NSEnumerator *enumerator = [events objectEnumerator];
	id anObject;
	while (anObject = [enumerator nextObject]) {
		[mEHModel sendEvent:anObject];
	}
	[events removeAllObjects];
	return nil;
}

//Method called when "add event" is used in the script
- (id) handleAddCommand:(NSScriptCommand *)command {
	if (DEBUG) NSLog(@"handling add by app");
	
	EHEvent * res = [[EHEvent alloc]init];
	//Set the event type fiedld
	[res setType:[command directParameter]];
	//Use properties to add to the fields
	
	

	//NSLog([[command arguments] objectForKey:@"withFields"] );
		
	NSEnumerator *enumerator = [[[command arguments] objectForKey:@"withFields"] objectEnumerator];
	id key;
	//Each key is a NSArray
	while ((key = [enumerator nextObject])) {
		//NSLog(key); 
		//NSLog([key objectAtIndex:0]);
		//NSLog([key objectAtIndex:1]);
		[res setValue:[key objectAtIndex:1] forField: [key objectAtIndex:0]] ;
		if ([key count]>=3)
			[res setType:[key objectAtIndex:2] forField:[key objectAtIndex:0]];
	}
	
	[events addObject:res];
	 return nil;
}


//Method called when "connect" is  used in the apple script
- (id) handleSetCommand:(NSScriptCommand *)command {
	if (DEBUG) NSLog(@"handling set by app");
	//NSLog([command directParameter]);
	
	[mEHModel setServerName: [command directParameter]];
	return nil;
}


//////////////////////////////////////////////////////////////////////////////////////////
///The following parts attempt to access event as an array, so that one can use
// tell application "eventheap"
//		set type of event 0 to "anewtype"
// end tell
// Untested yet
//
// run through our list of graphics and build a list of the subtypes
// on the fly:
/*
 - (NSArray *)graphicsWithClass:(Class)theClass {
	 NSArray *graphics = [self graphics];
	 NSMutableArray *result = [NSMutableArray array];
	 unsigned i, c = [graphics count];
	 id curGraphic;
	 for (i=0; i<c; i++) {
		 curGraphic = [graphics objectAtIndex:i];
		 if ([curGraphic isKindOfClass:theClass]) {
			 [result addObject:curGraphic];
		 }
	 }
	 return result;
 } */


////////////////////////////////////////////////////////////////////////////////////////////
//One to many

//use "set mycount to number of events" before to determine size
- (NSArray *)events {
    //return [self graphicsWithClass:[Image class]];
	//"set x to event 1" calls this methods
	if (DEBUG) NSLog(@"returning events by app");
	return events;
}

-(void)setEvents:(NSArray *)iArray
{
	if (DEBUG) NSLog(@"set events");
	events = iArray;   
}

- (void)insertInEvents:(EHEvent *)eventToAdd atIndex:(int)whereToInsert
{
	if (DEBUG) NSLog(@"insert in");
	NSMutableArray *a = [NSMutableArray arrayWithArray: events];
	[a insertObject:eventToAdd atIndex:whereToInsert];
	[self setEvents:a];
	// call the primitive method
}

- (void)addInEvents:(EHEvent *)iEvent
{
	if (DEBUG) NSLog(@"add in");
	NSMutableArray *a = [NSMutableArray arrayWithArray: events];
	[a  addObject:iEvent];
	[self setEvents:a];		
}

- (void)removeFromGraphicsAtIndex:(unsigned)index
{
	if (DEBUG) NSLog(@"remove from");
	NSMutableArray *a = [NSMutableArray arrayWithArray: events];
	[a removeObjectAtIndex:index];
	[self setEvents:a];	
}
 
- (void)replaceInGraphics:(EHEvent *)iEvent atIndex:(unsigned)index
{
	if (DEBUG) NSLog(@"replace in");
	NSMutableArray *a = [NSMutableArray arrayWithArray: events];
	[a  replaceObjectAtIndex:index  withObject:iEvent];
	[self setEvents:a];	
}

- (NSArray *)eventsWithClass:(Class)theClass {
	if (DEBUG) NSLog(@"events with class");
    NSArray *events = [self events];
    NSMutableArray *result = [NSMutableArray array];
    unsigned i, c = [events count];
    id curEvent;
	
    for (i=0; i<c; i++) {
        curEvent = [events objectAtIndex:i];
        if ([curEvent isKindOfClass:theClass]) {
            [result addObject:curEvent];
        }
    }
    return result;
}


/*
- (NSScriptObjectSpecifier *) objectSpecifier
{
	NSIndexSpecifier *specifier = [[NSIndexSpecifier alloc]
      initWithContainerClassDescription:
        (NSScriptClassDescription *)[myContainer classDescription]
					 containerSpecifier: [myContainer objectSpecifier]
									key: @"foobazi"];
	[specifier setIndex: [myContainer indexOfObjectInFoobazi: self]];
	return [specifier autorelease];
}*/

/*
 xxx
 setXxx
 
 countOfFoobazi
 objectInFoobaziAtIndex:
 getFoobazi:range:
 insertObject:inFoobaziAtIndex:
 removeObjectFromFoobaziAtIndex:
 replaceObjectInFoobaziAtIndex:withObject:
 validateFoobaz:error:
 */
@end
