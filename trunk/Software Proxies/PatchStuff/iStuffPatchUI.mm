//
//  iStuffPatchUI.m
//  QCiStuff
//
//  Created by René Reiners in Feb - April 2006.
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
	[listOfEventHeaps deselectAll:self];
	[customListOfEventHeaps setDelegate:self];
	[customListOfEventHeaps deselectAll:self];
	[listOfEventHeaps reloadData];
	[removeEventHeapButton setEnabled:false];
	if ([currentPatch automaticConnection]){
		NSLog(@"SHOULD BE TRUE");
	
		[toggleAutomaticConnectionManagement setState:NSOnState];
		}
	else {
		[toggleAutomaticConnectionManagement setState:NSOffState];
				NSLog(@"SHOULD NOT BE TRUE");
			}
		

	//[displayEventHeapName setStringValue:[currentPatch ehName]];

	// Load the user specified list with each refresh
	NSMutableArray *loadedEHList = [NSKeyedUnarchiver unarchiveObjectWithFile:[currentPatch prefsFile]];
	[[currentPatch specifiedEventHeaps] removeAllObjects];
	[[currentPatch specifiedEventHeaps] addObjectsFromArray:loadedEHList];

	[listenToEverything setState:[currentPatch listenToEverything]];
	if ([currentPatch listenToEverything]) {
		[proxyIDTextField setStringValue:@"<Listen To Everything>"];
		[proxyIDTextField setEnabled:false];
	}
	else {
		[proxyIDTextField setStringValue:[currentPatch eventID]];
		[proxyIDTextField setEnabled:true];
	}
	arrayOfEventHeaps = [currentPatch foundEventHeaps];
	if ([currentPatch connected]){
	  [self connectedState];
	}
	else if ([currentPatch standby]) {
	  [self standbyState];
	}
	else {
	  [self disconnectedState];
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
}

-(void) refreshView:(NSNotification *) notification
{
    //NSLog (@"RECEIVED a notification: INFO: %@", [notification userInfo]);

	iStuffPatch *currentPatch  = [self patch];
	if (![currentPatch advancedOptionsHidden])	{
	  [listOfEventHeaps reloadData];
	  [customListOfEventHeaps reloadData];
	}
	
	NSDictionary *ehStatusInfo = [notification userInfo];
//	if ((ehStatusInfo != nil) && (currentPatch !=nil) && ([[ehStatusInfo valueForKey:@"Identity"] isEqualTo: currentPatch]) ) {
	if (ehStatusInfo != nil){// && ([[ehStatusInfo valueForKey:@"Identity"] isEqualTo: currentPatch]) ) {

		NSString *status = [ehStatusInfo valueForKey:@"connectionStatus"];
		    //NSLog (@"Received a notification -  STATUS: %@", status);
		if ([status isEqualToString:@"connected"]){
		  //NSLog (@"Received a notification - CONNECTED");
		  [self connectedState];
		}
		else if ([status isEqualToString:@"standby"]){
			[self standbyState];
		}
		else if ([status isEqualToString:@"disconnected"]){
		  //NSLog (@"Received a notification - DISCONNECTED");
		  [self disconnectedState];
		}
	}
}

- (id)init{
// Detach a thread that automatically refreshes the view with every notification.
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshView:) name:@"EHListChange" object:[self patch]];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshListOfEventHeaps:) name:@"NewItem" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadList) name:@"NetServicesUpdate" object:nil];
	[listenToEverything setState:NSOffState];
	[customListOfEventHeaps setDelegate:self];
	[listenToEverything setHidden:false];
	selectedList = 0;
	//[listOfEventHeaps setDoubleAction:@selector(connectToEvenHeap:)];
	//[listOfEventHeaps setDelegate:listOfEventHeaps];
	
	allowRowEdit = false;
	return [super init];
}

- (void) reloadList {
NSLog(@"In reloadList");
[listOfEventHeaps reloadData];
}

// The resetView method is called when the current patch is deselected
- (void)resetView{
 // Here the currently specified data in the view has to be stored inside the model if that did not already happen inside IBActions.
 // --> Saving of what is not saved yet.
 
 iStuffPatch *currentPatch = [self patch];
 if ([listenToEverything state] == NSOffState){
	NSMutableDictionary *nodeAttributes = [currentPatch userInfo];
	[nodeAttributes setValue:[currentPatch eventID] forKey:@"eventID"];
  }

  [currentPatch setAdvancedOptionsHidden:[advancedConnectionOptions isHidden]];
  [currentPatch setListenToEverything:[listenToEverything state]];
  [currentPatch setRadioButtonIndex:[allOrOneRadioGroup selectedRow]];
//  NSLog(@"Reset the view: %@", [currentPatch userInfo]);
  
  [super resetView];

}


// **************UI Specific methods*********************


- (IBAction)connectToEventHeap:(id)sender{

// Only needed if selection from a list is desired
//	if (selectedList != -1) {

	iStuffPatch *currentPatch = [self patch];
	if (![[displayEventHeapName stringValue] isEqualToString:@""]) {
	/*
		// Check which table was selected:
		NSMutableArray *eHeapsModel;
		NSTableView *selectedTableView;
		if (selectedList == 0) {
			selectedTableView = listOfEventHeaps;
			eHeapsModel = [currentPatch foundEventHeaps];
		}
		else if (selectedList == 1){
			selectedTableView = customListOfEventHeaps;
			eHeapsModel = [currentPatch specifiedEventHeaps];
		}
 	*/
	
		NSString *selectedEventHeap = [displayEventHeapName stringValue];
		//NSString *selectedEventHeap = [eHeapsModel objectAtIndex:[selectedTableView selectedRow]];
		NSHost *hostWithName = [NSHost hostWithName:selectedEventHeap];
		NSHost *hostWithAddress = [NSHost hostWithAddress:selectedEventHeap];
		// The user can specify both, a name and a network address.
		// This cannot be checked, but therefore both initializations were made.
		// If both of the following checks reveal null pointers, that means
		// that the specified hosts are not reachable
		if ( ([hostWithName addresses] != nil) || ([hostWithAddress names] != nil) ) {
			//[self setEventHeapName:newEHServerName];
			//[self connectToEventHeap];
			NSLog(@"The name could be resolved...? %@", selectedEventHeap);
			[self disconnectFromEventHeap:nil];
			sleep(1); //forced because of stability 
			
			// depending on the status of the radio buttons, all or only one patch has to reconnect
			//global change for all patches
			if ([allOrOneRadioGroup selectedRow] == 0){
			// Create a one key dictionary that contains the new Event Heap name
			// get the selected entry from the EH list;
//			int rowIndex = [selectedTableView selectedRow];
//			if (rowIndex != -1) {
				//NSString *selectedEventHeap = [eHeapsModel objectAtIndex:rowIndex];
				NSMutableDictionary *ehInfo = [NSMutableDictionary dictionaryWithObject:selectedEventHeap forKey:@"newEHName"];
				[[NSNotificationCenter defaultCenter] postNotificationName: @"ConnectAll" object:nil userInfo:ehInfo];
				//sleep(1); //Needed for connection stability - otherwise QC may crash
	//		}
			}
			else {
				// local change for one patch
				//NSString *newEventHeap;
				//newEventHeap = [eHeapsModel objectAtIndex:[selectedTableView selectedRow]];
				//newEventHeap = [displayEventHeapName stringValue];
				[currentPatch disconnectFromCurrentEventHeap];
				[currentPatch setEventHeapName:selectedEventHeap];
				[currentPatch connectToEventHeap];
			}
		[self connectedState]; // Only change the view if the connection was succesful
		}
		//if ([currentPatch connected])
		//	[self connectedState]; // Only change the view if the connection was succesful
		else if (![currentPatch connected]){
			[displayEventHeapName setStringValue:@""];
			[self disconnectedState];
		}
	[listOfEventHeaps deselectAll:self];
	[customListOfEventHeaps deselectAll:self];
 }
 
}	

- (IBAction)disconnectFromEventHeap:(id)sender{
	//if (selectedList != -1) {
		iStuffPatch *currentPatch = [self patch];
		//global change for all patches
		if ([allOrOneRadioGroup selectedRow] == 0){
		// Post a notification that activates the disconnect method for all patches
			[[NSNotificationCenter defaultCenter] postNotificationName: @"DisconnectAll" object:nil userInfo:nil];
			//sleep(1);  //Needed for connection stability - otherwise QC may crash
		}
		else {
			// call the disconnect method for one patch directly
		  [currentPatch disconnectFromCurrentEventHeap];
		  //NSLog(@"ONLY the selected PATCH should DISCONNECT");
		}
    [self disconnectedState];
}

- (IBAction)showAdvancedOptions:(id)sender{
	[listOfEventHeaps reloadData];
//	if ([advancedConnectionOptions isHidden]){
	[advancedConnectionOptions setHidden:![advancedConnectionOptions isHidden]];
//	}
	
//	else {
//		[advancedConnectionOptions setHidden:true];
//	}
}

- (IBAction)addEventHeap:(id)sender{
	[addEventHeapButton setEnabled:false]; // Avoid several clicks on that button
	iStuffPatch *currentPatch = [self patch];
	// Let the button only be functional when there is no empty event heap inside
	[[currentPatch specifiedEventHeaps] addObject:@""];
	[customListOfEventHeaps reloadData];
	if ([customListOfEventHeaps numberOfColumns] == 0)
	//	[customListOfEventHeaps selectRow:[customListOfEventHeaps numberOfRows]-1 byExtendingSelection:false];
	sleep(1);
	[customListOfEventHeaps selectRow:[customListOfEventHeaps numberOfRows]-1 byExtendingSelection:false];
	[customListOfEventHeaps editColumn:0 row:[customListOfEventHeaps numberOfRows] -1 withEvent:nil select:false];
	[customListOfEventHeaps performClick:nil];
}

- (IBAction)removeEventHeap:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	// only if it is a custom event heap, it may be removed manually
	//if ([[[listOfEventHeaps selectedCell] stringValue] hasSuffix:@"(custom)"]) {
		if ([customListOfEventHeaps selectedRow] != -1) {
			[[currentPatch specifiedEventHeaps] removeObjectAtIndex:[customListOfEventHeaps selectedRow]];
			[NSKeyedArchiver archiveRootObject:[currentPatch specifiedEventHeaps] toFile:[currentPatch prefsFile]];
		}
	//	NSLog(@"Value of selected row: %i", [listOfEventHeaps selectedRow]);
	
	
		[customListOfEventHeaps reloadData];
		[removeEventHeapButton setEnabled:false];
	//}

}

- (IBAction)changeProxyName:(id)sender{
	//NSLog(@"In change ProxyName");
	iStuffPatch *currentPatch = [self patch];
	NSTextField *textField = sender;
	if (! [[sender stringValue] isEqualToString:@"<Listen To Everything>"]){
		[listenToEverything setState:NSOffState];
		[currentPatch setListenToEverything:NSOffState];
		[currentPatch setEventID:[textField stringValue]];
	}
	else {
		[proxyIDTextField setStringValue:[currentPatch eventID]];
	}
	//NSLog(@"Name should have been changed: %@", [currentPatch userInfo]);
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
		[proxyIDTextField setStringValue:[currentPatch eventID]];
	}
}

- (IBAction)toggleEHConnectionManagement:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	[currentPatch setAutomaticEHConnection:![currentPatch automaticConnection]];
	[currentPatch automaticEHConnection];
}

-(int)numberOfRowsInTableView: (NSTableView *) Table{
	iStuffPatch *currentPatch = [self patch];
	if ([[[Table class] description] isEqualToString:@"NSTableView"])
		return [[currentPatch foundEventHeaps] count];
	else
		return [[currentPatch specifiedEventHeaps] count];
}

-(id)tableView:(NSTableView *) Table
	objectValueForTableColumn:(NSTableColumn *) Column
	row: (int) Row{
			
			
	iStuffPatch *currentPatch = [self patch];
	// Ask what table view has been passed and decide what to return
	if ([[[Table class] description] isEqualToString: @"NSTableView"]) 
		return [[[currentPatch foundEventHeaps] objectAtIndex:Row] description];
		
	else 
		return [[[currentPatch specifiedEventHeaps] objectAtIndex:Row] description];
}

- (void) refreshListOfEventHeaps:(NSNotification *) info {
	iStuffPatch *currentPatch = [self patch];
	//NSLog(@"NOTIFICATION RECEIVED:");
	NSString *itemName = [NSString stringWithString:[[info userInfo] valueForKey:@"item"]];
	[[currentPatch specifiedEventHeaps] removeObject:@""];
	//Only if the textfield is not empty the new entry should be added
	if (! [itemName isEqualToString:@""])
		[[currentPatch specifiedEventHeaps] addObject:itemName];
	[customListOfEventHeaps reloadData];
			[listOfEventHeaps selectRow:-1 byExtendingSelection:false];
		//	[listOfEventHeaps deselectAll:self];
	// Now the "addEventHeaps button can be reactivated
	[addEventHeapButton setEnabled:true];
	// Store the list in the prefs file
	[NSKeyedArchiver archiveRootObject:[currentPatch specifiedEventHeaps] toFile:[currentPatch prefsFile]];
}

- (void) tableViewSelectionDidChange:(NSNotification *) aNotification {
	iStuffPatch *currentPatch = [self patch];
	[removeEventHeapButton setEnabled:false];
	// There are always two notiications triggered.
	// The first one has the priority.
	//NSLog (@"Inside the delegate method. TableObject: %@",[ aNotification valueForKey:@"object"]);
	NSTableView *selectedTableView;
	selectedTableView = [aNotification valueForKey:@"object"];
	NSString *tableClassDescription;
	tableClassDescription = [[selectedTableView class] description];

	if ((!discoveredEventHeapsFirst) && (!specifiedEventHeapsFirst)) { // This is the first call
		if ([tableClassDescription isEqualToString:@"NSTableView"]) {
			discoveredEventHeapsFirst = true;
			specifiedEventHeapsFirst = false;
	//		selectedList = -1;
		}
		else {
			discoveredEventHeapsFirst = false;
			specifiedEventHeapsFirst = true;
		//	selectedList = -1;
		}
	}

	if ( ([tableClassDescription isEqualToString:@"NSTableView"]) && (discoveredEventHeapsFirst) ) {
	// deselect the user-specified list
		//NSLog(@"In if branch - reset the customlist");
		[customListOfEventHeaps deselectAll:self];
		discoveredEventHeapsFirst = false;
		selectedList = 0; // The discovered EH list is selected
		// Reset the EH Name label to the current value. 
		if ( ([selectedTableView selectedRow] != -1) && (![currentPatch connected]) )
			[displayEventHeapName setStringValue:[[currentPatch foundEventHeaps] objectAtIndex:[selectedTableView selectedRow]]];
	}
	else if ( ([tableClassDescription isEqualToString:@"CustomTableView"]) && (specifiedEventHeapsFirst) ) {
	//NSLog(@"In else if branch");
		[listOfEventHeaps deselectAll:self];
		specifiedEventHeapsFirst = false;
		selectedList = 1; // The user-specified list was selected.
		[removeEventHeapButton setEnabled:true];
		// Reset the EH Name label to the current value. 
		if ( ([selectedTableView selectedRow] != -1) && (![currentPatch connected]) )
			[displayEventHeapName setStringValue:[[currentPatch specifiedEventHeaps] objectAtIndex:[selectedTableView selectedRow]]];
	}
	else { // It was the second call --> Reset everything
		//NSLog(@"In else branch - there was the second run");
		discoveredEventHeapsFirst = false;
		specifiedEventHeapsFirst = false;
		selectedList = -1;
	}
}

-(void) disconnectedState {
			//iStuffPatch *currentPatch = [self patch];
			[displayConnectionStatus setStringValue:@"Not connected"];
			[displayEventHeapName setStringValue:@""];
			//[displayEventHeapName setStringValue:[currentPatch ehName]];
			[displayEventHeapName setEditable:false];
//			[displayEventHeap setTextColor:[NSColor redColor]];
			[displayConnectionStatus setBackgroundColor:[NSColor redColor]];
			[animationConnected stopAnimation:self];
			[animationConnected setHidden:true];
}

-(void) standbyState {
			iStuffPatch *currentPatch = [self patch];
		//NSLog (@"Received a notification -  STANDBY");
			[listOfEventHeaps deselectAll:self];
			[displayEventHeapName setStringValue:[currentPatch ehName]];
			[displayEventHeapName setEditable:false];
			[animationConnected startAnimation:self];
			[animationConnected setHidden:false];
			[displayConnectionStatus setStringValue:@"Standby"];
			//[displayEventHeap setTextColor:[NSColor orangeColor]];
			[displayConnectionStatus setBackgroundColor:[NSColor yellowColor]];

}

-(void) connectedState {
			iStuffPatch *currentPatch = [self patch];
			//int index = [[currentPatch foundEventHeaps] indexOfObject:[currentPatch ehName]];
			//[listOfEventHeaps selectRowIndexes:[NSIndexSet indexSetWithIndex:index] byExtendingSelection:false];
			[animationConnected stopAnimation:self];
			[animationConnected setHidden:true];
			[displayEventHeapName setStringValue:[currentPatch ehName]];
			[displayEventHeapName setEditable:true];
			//NSLog(@"Name should have been set: Name: %@", [currentPatch ehName]);
			[displayConnectionStatus setStringValue:@"Connected"];
			[displayConnectionStatus setBackgroundColor:[NSColor greenColor]];
			
			// Save the new Event Heap in the patches' dictionary
			 [[currentPatch userInfo] setValue:[displayEventHeapName stringValue] forKey:@"LastEHName"];
			 //NSLog(@"Reset the dictionary: %@", [currentPatch userInfo]);
			//[displayEventHeap setTextColor:[NSColor greenColor]];
}	

// Delegate method for the NSTableViews
- (BOOL)tableView:(NSTableView *)aTableView shouldEditTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	return false; // Do not allow editing
}


@end
