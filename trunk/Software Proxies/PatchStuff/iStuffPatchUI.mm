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
	//[removeEventHeapButton setEnabled:false];
	if ([currentPatch automaticConnection]){
		NSLog(@"SHOULD BE TRUE");
	
		[toggleAutomaticConnectionManagement setState:NSOnState];
		}
	else {
		[toggleAutomaticConnectionManagement setState:NSOffState];
				NSLog(@"SHOULD NOT BE TRUE");
			}

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

	// Set the state depending on the state of the iStuff patch
	if ([currentPatch connected]){
	  [self connectedState];
	}
	else if ([currentPatch standby]) {
	  [self standbyState];
	}
	else {
	  [self disconnectedState];
	}
}

-(void) refreshView:(NSNotification *) notification
{
	iStuffPatch *currentPatch  = [self patch];
	
	if (![currentPatch advancedOptionsHidden])	{
	  [listOfEventHeaps reloadData];
	  [customListOfEventHeaps reloadData];
	}
	
	// Refresh the view depending on the state of the iStuff patch
	NSDictionary *ehStatusInfo = [notification userInfo];
	if (ehStatusInfo != nil){
		NSString *status = [ehStatusInfo valueForKey:@"connectionStatus"];
		if ([status isEqualToString:@"connected"]){
			[self connectedState];
		}
		else if ([status isEqualToString:@"standby"]){
			[self standbyState];
		}
		else if ([status isEqualToString:@"disconnected"]){
		  [self disconnectedState];
		}
	}
}

- (id)init{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshView:) name:@"NetServicesUpdate" object:[self patch]];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshListOfEventHeaps:) name:@"NewItem" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadList) name:@"NetServicesUpdate" object:nil];
	
	[listenToEverything setState:NSOffState];
	[customListOfEventHeaps setDelegate:self];
	[listenToEverything setHidden:false];
	selectedList = 0;
	allowRowEdit = false;
	return [super init];
}

- (void) reloadList {
	// When a new service is found, the list containing the discovered Event Heaps should be reloaded
	[listOfEventHeaps reloadData];
}

- (void)resetView{
	// The resetView method is called when the current patch is deselected

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
  
  [super resetView];

}


// **************UI Specific methods*********************

- (IBAction)connectToEventHeap:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	NSString *selectedEventHeap = nil;

	if ( (![currentPatch connected]) && (![[displayEventHeapName stringValue] isEqualToString:@""]) ) 
		// Connect to the Event Heap displayed if the patch is not connected
		selectedEventHeap = [displayEventHeapName stringValue];
	else{
		// otherwise take the selected entry from one of the lists
		
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
		if ([selectedTableView selectedRow] != -1)
			selectedEventHeap = [eHeapsModel objectAtIndex:[selectedTableView selectedRow]]; 
	}

	// Only try to connected if a new Event Heap was selected
	if (selectedEventHeap != nil) {
		[self disconnectFromEventHeap:self];
		// The user can specify both, a name and a network address.
		NSHost *hostWithName = [NSHost hostWithName:selectedEventHeap];
		NSHost *hostWithAddress = [NSHost hostWithAddress:selectedEventHeap];
		// If both of the following checks reveal null pointers, that means
		// that the specified hosts are not reachable
		if ( ([hostWithName addresses] != nil) || ([hostWithAddress names] != nil) ) {
			// Resolution was successful - now check wether an Event Heap is really running.
			// Set up a new socket connection that chekcs wether a service
			// namely the Event Heap is running
			struct sockaddr_in server;
			const char *ipAddress = [[[hostWithName addresses] objectAtIndex:0]cString];
			server.sin_family = AF_INET;
			server.sin_port = htons(4535);
			inet_aton(ipAddress,&server.sin_addr);
		int sock = socket( AF_INET, SOCK_STREAM, 0 );
		if (connect(sock,(struct sockaddr*)&server, sizeof(server)) < 0){
			// Connection could not be established --> Patch is disconnected
		}
		else{			
			// depending on the status of the radio buttons, all or only one patch has to reconnect
			if ([allOrOneRadioGroup selectedRow] == 0){
			// Global change for all patches:
			// Create a one key dictionary that contains the new Event Heap name
			// Get the selected entry from the EH list;
				NSMutableDictionary *ehInfo = [NSMutableDictionary dictionaryWithObject:selectedEventHeap forKey:@"newEHName"];
				[[NSNotificationCenter defaultCenter] postNotificationName: @"ConnectAll" object:nil userInfo:ehInfo];
			}
			else {
				// local change for one patch
				[currentPatch disconnectFromCurrentEventHeap];
				[currentPatch setEventHeapName:selectedEventHeap];
				[currentPatch connectToEventHeap];
			}
		[self connectedState]; // Only change the view if the connection was succesful
		}
	}
 	[listOfEventHeaps deselectAll:self];
	[customListOfEventHeaps deselectAll:self];
	}
}	

- (IBAction)disconnectFromEventHeap:(id)sender{
		iStuffPatch *currentPatch = [self patch];
		// Global change for all patches
		if ([allOrOneRadioGroup selectedRow] == 0){
		// Post a notification that activates the disconnect method for all patches
			[[NSNotificationCenter defaultCenter] postNotificationName: @"DisconnectAll" object:nil userInfo:nil];
		}
		else {
			// call the disconnect method for one patch directly
			[currentPatch disconnectFromCurrentEventHeap];
		}
	// Independenty, the current patch will be disconnected
	// Change the state	
    [self disconnectedState];
}

- (IBAction)showAdvancedOptions:(id)sender{
	[listOfEventHeaps reloadData];
	[advancedConnectionOptions setHidden:![advancedConnectionOptions isHidden]];
}

- (IBAction)addEventHeap:(id)sender{
	[addEventHeapButton setEnabled:false]; // Avoid several clicks on that button
	iStuffPatch *currentPatch = [self patch];
	[[currentPatch specifiedEventHeaps] addObject:@""];
	[customListOfEventHeaps reloadData];
	if ([customListOfEventHeaps numberOfColumns] == 0)
		[customListOfEventHeaps selectRow:[customListOfEventHeaps numberOfRows]-1 byExtendingSelection:false];
	//sleep(1);
	[customListOfEventHeaps selectRow:[customListOfEventHeaps numberOfRows]-1 byExtendingSelection:false];
	[customListOfEventHeaps editColumn:0 row:[customListOfEventHeaps numberOfRows] -1 withEvent:nil select:true];
	[customListOfEventHeaps performClick:nil];
}

- (IBAction)removeEventHeap:(id)sender{
	iStuffPatch *currentPatch = [self patch];
	// Only if it is a custom event heap, it may be removed manually
	if ([customListOfEventHeaps selectedRow] != -1) {
		[[currentPatch specifiedEventHeaps] removeObjectAtIndex:[customListOfEventHeaps selectedRow]];
		[NSKeyedArchiver archiveRootObject:[currentPatch specifiedEventHeaps] toFile:[currentPatch prefsFile]];
	}
	[customListOfEventHeaps reloadData];
}

- (IBAction)changeProxyName:(id)sender{
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
	NSString *itemName = [NSString stringWithString:[[info userInfo] valueForKey:@"item"]];
	[[currentPatch specifiedEventHeaps] removeObject:@""];
	//Only if the textfield is not empty the new entry should be added
	if (! [itemName isEqualToString:@""]) {
		[[currentPatch specifiedEventHeaps] addObject:itemName];
	}
	[customListOfEventHeaps reloadData];
	[listOfEventHeaps selectRow:-1 byExtendingSelection:false];
	
	// Now the "addEventHeaps button can be reactivated
	[addEventHeapButton setEnabled:true];
	// Make the new host appear in the appropriate text field if the patch is not connected
	if (![currentPatch connected])
		[displayEventHeapName setStringValue:itemName];
	// Store the list in the prefs file
	[NSKeyedArchiver archiveRootObject:[currentPatch specifiedEventHeaps] toFile:[currentPatch prefsFile]];
}

- (void) tableViewSelectionDidChange:(NSNotification *) aNotification {
	iStuffPatch *currentPatch = [self patch];
	//[removeEventHeapButton setEnabled:false];
	// There are always two notifications triggered.
	// The first one has the priority.
	NSTableView *selectedTableView;
	selectedTableView = [aNotification valueForKey:@"object"];
	NSString *tableClassDescription;
	tableClassDescription = [[selectedTableView class] description];

	if ((!discoveredEventHeapsFirst) && (!specifiedEventHeapsFirst)) { // This is the first call
		if ([tableClassDescription isEqualToString:@"NSTableView"]) {
			discoveredEventHeapsFirst = true;
			specifiedEventHeapsFirst = false;
		}
		else {
			discoveredEventHeapsFirst = false;
			specifiedEventHeapsFirst = true;
		}
	}

	if ( ([tableClassDescription isEqualToString:@"NSTableView"]) && (discoveredEventHeapsFirst) ) {
	// deselect the user-specified list
		NSLog(@"In if branch - reset the customlist");
		[customListOfEventHeaps deselectAll:self];
		discoveredEventHeapsFirst = false;
		selectedList = 0; // The discovered EH list is selected
		// Reset the EH Name label to the current value. 
		if ( ([selectedTableView selectedRow] != -1) && (![currentPatch connected]) )
			[displayEventHeapName setStringValue:[[currentPatch foundEventHeaps] objectAtIndex:[selectedTableView selectedRow]]];
	}
	else if ( ([tableClassDescription isEqualToString:@"CustomTableView"]) && (specifiedEventHeapsFirst) ) {
		[listOfEventHeaps deselectAll:self];
		specifiedEventHeapsFirst = false;
		selectedList = 1; 
		// The user-specified list was selected.
		// Reset the EH Name label to the current value. 
		if ( ([selectedTableView selectedRow] != -1) && (![currentPatch connected]) )
			[displayEventHeapName setStringValue:[[currentPatch specifiedEventHeaps] objectAtIndex:[selectedTableView selectedRow]]];
	}
	else { // It was the second call --> Reset everything
		discoveredEventHeapsFirst = false;
		specifiedEventHeapsFirst = false;
		selectedList = -1;
	}
}

-(void) disconnectedState {
	iStuffPatch *currentPatch = [self patch];
	[displayConnectionStatus setStringValue:@"Not connected"];
	[displayEventHeapName setStringValue:@""];
	[displayEventHeapName setEditable:false];
	[displayConnectionStatus setBackgroundColor:[NSColor redColor]];
	[animationConnected stopAnimation:self];
	[animationConnected setHidden:true];
	[currentPatch disconnectFromCurrentEventHeap];
}

-(void) standbyState {
	iStuffPatch *currentPatch = [self patch];
	[listOfEventHeaps deselectAll:self];
	[displayEventHeapName setStringValue:[currentPatch ehName]];
	[displayEventHeapName setEditable:false];
	[animationConnected startAnimation:self];
	[animationConnected setHidden:false];
	[displayConnectionStatus setStringValue:@"Standby"];
	[displayConnectionStatus setBackgroundColor:[NSColor yellowColor]];

}

-(void) connectedState {
	iStuffPatch *currentPatch = [self patch];
	[animationConnected stopAnimation:self];
	[animationConnected setHidden:true];
	[displayEventHeapName setStringValue:[currentPatch ehName]];
	[displayEventHeapName setEditable:true];
	[displayConnectionStatus setStringValue:@"Connected"];
	[displayConnectionStatus setBackgroundColor:[NSColor greenColor]];
			
	// Save the new Event Heap in the patches' dictionary
	[[currentPatch userInfo] setValue:[displayEventHeapName stringValue] forKey:@"LastEHName"];
}	

// Delegate method for the NSTableViews
- (BOOL)tableView:(NSTableView *)aTableView shouldEditTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
NSLog(@"In the methos that chekcs forediting");
	return false; // Do not allow editing
}

@end
