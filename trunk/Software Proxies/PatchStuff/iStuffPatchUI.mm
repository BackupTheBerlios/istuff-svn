//
//  iStuffPatchUI.m
//  QCiStuff
//
//  Created by René Reiners in Feb/March 2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "iStuffPatchUI.h"


@implementation iStuffPatchUI
// this method is called when a patch is inserted and 
// the inspector is  shown for the first time
+ (id)viewNibName
{
	return @"iStuffPatchUI.nib";
}
/*


 This method is always called  when the patch is selected
 fp8 is the currently active patch
 The patch passed as parameter provides the model.
 There is one instance of a view that always has to be updated with the current data from the patch.
 In setupViewForPatch the data from the model has to be read and the view has to be updated.
 
 In ResetView the currently displayed data in the view must be stored inside the current model.
 The method is called automatically when another patch or nothing is selected.
*/

- (void)setupViewForPatch:(id)fp8
{	
	[super setupViewForPatch:fp8];
	iStuffPatch *currentPatch;
	currentPatch = [self patch];
	
	[listOfEventHeaps setDelegate:self];
	
	[listenToEverything setState:[currentPatch listenToEverything]];
	if ([currentPatch listenToEverything]) {
		[proxyIDTextField setStringValue:@"<Listen To Everything>"];
		[proxyIDTextField setEnabled:false];
	}
	else {
		[proxyIDTextField setStringValue:[currentPatch proxyName]];
		[proxyIDTextField setEnabled:true];
	}
	arrayOfEventHeaps = [currentPatch foundEventHeaps];
	if ([currentPatch connected]){
	  [animationConnected stopAnimation:self];
	  [animationConnected setHidden:true];
	  [displayEventHeap setStringValue:[currentPatch ehName]];
	 //[displayEventHeap setTextColor:[NSColor greenColor]]; 
		[displayEventHeap setBackgroundColor:[NSColor greenColor]];
	  int index = [[currentPatch foundEventHeaps] indexOfObject:[currentPatch ehName]];
	  [listOfEventHeaps selectRowIndexes:[NSIndexSet indexSetWithIndex:index] byExtendingSelection:false];
	}
	else if ([currentPatch standby]) {
		[displayEventHeap setStringValue:@"Standby until reconnect or new EH is chosen"];
		//[displayEventHeap setTextColor:[NSColor orangeColor]];
		[displayEventHeap setBackgroundColor:[NSColor yellowColor]];
		[animationConnected startAnimation:self];
		[animationConnected setHidden:false];
	}
	else {
			[displayEventHeap setStringValue:@"Currently not connected"];
//			[displayEventHeap setTextColor:[NSColor redColor]];
			[displayEventHeap setBackgroundColor:[NSColor redColor]];
			[animationConnected stopAnimation:self];
			[animationConnected setHidden:true];
	}
	
	// Restore the Radio Buttons' status
	[allOrOneRadioGroup setState:1 atRow:[currentPatch radioButtonIndex] column:0];
	// check wether the advanced opitions are displayed
	if ([currentPatch advancedOptionsHidden]){
		[advancedConnectionOptions setHidden:true];
		[advancedOptionsButton setState:0];
	}
	else {
		[advancedConnectionOptions setHidden:false];
		[advancedOptionsButton setState:1];
	}
	// Just for iinformative purposes
	NSLog (@"The ID: %@", currentPatch);
}

-(void) refreshView:(NSNotification *) notification
{
	iStuffPatch *currentPatch  = [self patch];
	if (![advancedConnectionOptions isHidden]){
		[listOfEventHeaps reloadData];		
	}

	if (([notification userInfo] != nil) && (currentPatch !=nil)) {
		NSDictionary *ehStatusInfo = [notification userInfo];
		NSString *status = [ehStatusInfo valueForKey:@"connectionStatus"];
		if ([status isEqualToString:@"connected"]){
			//int index = [[currentPatch foundEventHeaps] indexOfObject:[currentPatch ehName]];
			//[listOfEventHeaps selectRowIndexes:[NSIndexSet indexSetWithIndex:index] byExtendingSelection:false];
			[animationConnected stopAnimation:self];
			[animationConnected setHidden:true];
			[displayEventHeap setStringValue:[currentPatch ehName]];
			[displayEventHeap setBackgroundColor:[NSColor greenColor]];
			//[displayEventHeap setTextColor:[NSColor greenColor]];
		}
		else if ([status isEqualToString:@"standby"]){
			[listOfEventHeaps deselectAll:self];
			[animationConnected startAnimation:self];
			[animationConnected setHidden:false];
			[displayEventHeap setStringValue:@"Standby until reconnect or new EH is chosen"];
			//[displayEventHeap setTextColor:[NSColor orangeColor]];
			[displayEventHeap setBackgroundColor:[NSColor yellowColor]];
		}
		else if ([status isEqualToString:@"disconnected"]){
			[displayEventHeap setStringValue:@"Currently not connected"];
//			[displayEventHeap setTextColor:[NSColor redColor]];
			[displayEventHeap setBackgroundColor:[NSColor redColor]];
			[animationConnected stopAnimation:self];
			[animationConnected setHidden:true];
		}
	}
}

- (id)init{
// Detach a thread that automatically refreshes the view with every notification.
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshView:) name:@"EHListChange" object:nil];
	[listenToEverything setState:NSOffState];
	[listOfEventHeaps setDoubleAction:@selector(connectToEvenHeap:)];
	allowRowEdit = false;
	return [super init];
}


// The resetView method is called when the current patch is deselected
- (void)resetView{
 // Here the currently specified data in the view has to be stored inside the model if that did not already happen inside IBActions.
 // --> Saving of what is not saved yet.
 
 iStuffPatch *currentPatch = [self patch];
 [currentPatch setAdvancedOptionsHidden:[advancedConnectionOptions isHidden]];
 [currentPatch setListenToEverything:[listenToEverything state]];
 [currentPatch setRadioButtonIndex:[allOrOneRadioGroup selectedRow]];
  [super resetView];

}


// **************UI Specific methods*********************


- (IBAction)connectToEventHeap:(id)sender{
NSLog(@"INNNN CONNECTECT TO EVENE HEAP");
	if ([listOfEventHeaps selectedRow] != -1) {
		// depending on the status of the radio buttons, all or only one patch has to reconnect
		iStuffPatch *currentPatch = [self patch];
		//global change for all patches
		if ([allOrOneRadioGroup selectedRow] == 0){
		// Create a one key dictionary that contains the new Event Heap name
		// get the selected entry from the EH list;
			int rowIndex = [listOfEventHeaps selectedRow];
				NSString *selectedEventHeap = [[currentPatch foundEventHeaps] objectAtIndex:rowIndex];
				NSDictionary *ehInfo = [NSDictionary dictionaryWithObject:selectedEventHeap forKey:@"newEHName"];
				[[NSNotificationCenter defaultCenter] postNotificationName: @"ReconnectAll" object:nil userInfo:ehInfo];
		}
		else {
			// local change for one patch
			NSString *newEventHeap;
			newEventHeap = [arrayOfEventHeaps objectAtIndex:[listOfEventHeaps selectedRow]];
			[currentPatch setEventHeapName:newEventHeap];
			[currentPatch connectToEventHeap];
		}
	}
}	

- (IBAction)disconnectFromEventHeap:(id)sender{
		iStuffPatch *currentPatch = [self patch];
		//global change for all patches
		if ([allOrOneRadioGroup selectedRow] == 0){
		// Post a notification that activates the disconnect method for all patches
		// get the selected entry from the EH list;
			[[NSNotificationCenter defaultCenter] postNotificationName: @"Disconnect" object:nil userInfo:nil];
		}
		else {
			// call the disconnect method for one patch directly
			[currentPatch disconnectFromCurrentEventHeap];
		}
}

- (IBAction)showAdvancedOptions:(id)sender{
	[listOfEventHeaps reloadData];
	if ([advancedConnectionOptions isHidden]){
		[advancedConnectionOptions setHidden:false];
	}
	
	else {
		[advancedConnectionOptions setHidden:true];
	}
}

- (IBAction)addEventHeap:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	NSMutableString *newMachineName = [NSMutableString stringWithString:@"new EH name or adress"];
	[[currentPatch foundEventHeaps] addObject:newMachineName];
	allowRowEdit=true;
	[listOfEventHeaps reloadData];
	// Mark the new entry and the list editable.
	
	// After entering something, the list should not editable anymore --> New method?
	[listOfEventHeaps selectRow:[listOfEventHeaps numberOfRows]-1 byExtendingSelection:false];
	NSLog(@"Selected Coloumn:%i and number of rows: %i",[listOfEventHeaps selectedColumn],[listOfEventHeaps numberOfRows]);
	//[listOfEventHeaps reloadData];
	[listOfEventHeaps editColumn:0 row:[listOfEventHeaps numberOfRows] -1 withEvent:nil select:false];
	[listOfEventHeaps performClick:nil];
}

- (IBAction)removeEventHeap:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	// only if it is a custom event heap, it may be removed manually
	if ([[[listOfEventHeaps selectedCell] stringValue] hasSuffix:@"(custom)"]) {
		[[currentPatch foundEventHeaps] removeObjectAtIndex:[listOfEventHeaps selectedRow]];
		NSLog(@"Value of selected row: %i", [listOfEventHeaps selectedRow]);
		[listOfEventHeaps reloadData];
	}

}

- (IBAction)changeProxyName:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	NSTextField *textField = sender;
	if (! [[sender stringValue] isEqualToString:@"<Listen To Everything>"]){
		[listenToEverything setState:NSOffState];
		[currentPatch setListenToEverything:NSOffState];
	//	[currentPatch setProxyName:[textField stringValue]];
	}
	else {
		[proxyIDTextField setStringValue:[currentPatch proxyName]];
	}
}


- (IBAction)enableListenToEverything:(id)sender{
	NSButton *switchButton = sender;
	iStuffPatch *currentPatch = [self patch];
	[currentPatch setListenToEverything:[switchButton state]];
	if ([switchButton state] == NSOnState) {
		[proxyIDTextField setStringValue:@"<Listen To Everything>"];
		[proxyIDTextField setEnabled:false];
	}
	else {
		[proxyIDTextField setEnabled:true];
		[proxyIDTextField setStringValue:[currentPatch proxyName]];
	}
}

-(int)numberOfRowsInTableView: (NSTableView *) Table{
	iStuffPatch *currentPatch = [self patch];
	return [[currentPatch foundEventHeaps] count];
}

-(id)tableView:(NSTableView *) Table
	objectValueForTableColumn:(NSTableColumn *) Column
	row: (int) Row{
	iStuffPatch *currentPatch = [self patch];
	return [[[currentPatch foundEventHeaps] objectAtIndex:Row] description];
	}
	
// Delegate methods
- (BOOL)tableView:(NSTableView *)aTableView shouldEditTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	return allowRowEdit;
}

- (void)controlTextDidEndEditing:(NSNotification *)aNotification{
//[super controlTextDidEndEditing:aNotification];
NSLog(@"Editing ended");
allowRowEdit=false;


iStuffPatch *currentPatch = [self patch];
NSMutableString *newEntry = [NSMutableString stringWithString:[[listOfEventHeaps selectedCell] stringValue]];
[newEntry appendString:@"(custom)"];
NSLog(@"currentEntry: %@", newEntry);

[[currentPatch foundEventHeaps] removeLastObject];
NSLog(@"Value of the text row: %@", [[listOfEventHeaps selectedCell] stringValue]);
[[currentPatch foundEventHeaps] addObject:newEntry];
[listOfEventHeaps reloadData];

[listOfEventHeaps editColumn:-1 row:-1 withEvent:nil select:false];

}


@end
