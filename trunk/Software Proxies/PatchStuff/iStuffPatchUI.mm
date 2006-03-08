//
//  iStuffPatchUI.m
//  QCiStuff
//
//  Created by RenŽ Reiners in Feb/March 2006.
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
	arrayOfEventHeaps = [currentPatch foundEventHeaps];
	if ([currentPatch connected]){
	  [animationConnected startAnimation:self];
	  [displayEventHeap setStringValue:[currentPatch ehName]];
	  [displayEventHeap setTextColor:[NSColor greenColor]]; 

	  int index = [[currentPatch foundEventHeaps] indexOfObject:[currentPatch ehName]];
		NSLog (@"INDEX: %i:", index);
	  [listOfEventHeaps selectRowIndexes:[NSIndexSet indexSetWithIndex:index] byExtendingSelection:false];
	}
	else  {
		[animationConnected stopAnimation:self];
		if ([currentPatch suspended]) {
			[displayEventHeap setStringValue:@"Standby until reconnect or new EH is chosen"];
			[displayEventHeap setTextColor:[NSColor orangeColor]];
		}
		else {
			[displayEventHeap setStringValue:@"Currently not connected"];
			[displayEventHeap setTextColor:[NSColor redColor]];
		}
	}
	
	// Restore the Radio Buttons' status
	NSLog (@"Restored Index value: %i", [currentPatch radioButtonIndex]);
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
	if (![advancedConnectionOptions isHidden]){
		[listOfEventHeaps reloadData];		
	}
		
	NSLog(@"JUST RELOADED THE DATA");
	iStuffPatch *currentPatch = [self patch];
	NSLog(@"Current Patch: %@",currentPatch);
	if (([notification userInfo] != nil) && (currentPatch !=nil)) {
		NSDictionary *ehStatusInfo = [notification userInfo];
		NSString *status = [ehStatusInfo valueForKey:@"connectionStatus"];
		if ([status isEqualToString:@"connected"]){
			NSLog(@"Status IN USERINFO NOT NIL Connected : %@", status);
			//int index = [[currentPatch foundEventHeaps] indexOfObject:[currentPatch ehName]];
			//[listOfEventHeaps selectRowIndexes:[NSIndexSet indexSetWithIndex:index] byExtendingSelection:false];
			[animationConnected startAnimation:self];
			[displayEventHeap setStringValue:[currentPatch ehName]];
			[displayEventHeap setTextColor:[NSColor greenColor]]; 
			NSLog (@"Notification New Connection reeceived");
		}
		else if ([status isEqualToString:@"standby"]){
			NSLog(@"Status STANDBY : %@", status);
			[listOfEventHeaps deselectAll:self];
			//selectRowIndexes:[NSIndexSet indexSetWithIndex:index] byExtendingSelection:false];
			[animationConnected stopAnimation:self];
			[displayEventHeap setStringValue:@"Standby until reconnect or new EH is chosen"];
			[displayEventHeap setTextColor:[NSColor orangeColor]];
			NSLog(@"Notification standby received");
		}
	}
}

- (id)init{

// Detach a thread that automatically refreshed the view every x seconds
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshView:) name:@"EHListChange" object:nil];
	return [super init];
}


// The resetView method is called when the current patch is deselected
- (void)resetView{
NSLog(@"In resetView");
 // Here the currently specified data in the view has to be stored inside the model if that did not already happen inside IBActions.
 // --> Saving of what is not saved yet.
 
 iStuffPatch *currentPatch = [self patch];
 [currentPatch setAdvancedOptionsHidden:[advancedConnectionOptions isHidden]];
 [currentPatch setRadioButtonIndex:[allOrOneRadioGroup selectedRow]];
 NSLog(@"Seleceted row: %i", [allOrOneRadioGroup selectedRow]);
  [super resetView];

}


// **************UI Specific methods*********************


- (IBAction)connectToEventHeap:(id)sender{
	if ([listOfEventHeaps selectedRow] != -1) {
		// depending on the status of the radio buttons, all or only one patch has to reconnect
		iStuffPatch *currentPatch = [self patch];
		//global change for all patches
		if ([allOrOneRadioGroup selectedRow] == 0){
		// Create a one key dictionary that contains the new Event Heap name
		// get the selected entry from the EH list;
			int rowIndex = [listOfEventHeaps selectedRow];
				NSString *selectedEventHeap = [[currentPatch foundEventHeaps] objectAtIndex:rowIndex];
				NSLog(@"Value of the list: %@", selectedEventHeap);
				NSDictionary *ehInfo = [NSDictionary dictionaryWithObject:selectedEventHeap forKey:@"newEHName"];
				//NSLog(@"In all patches branch -- selected: %i", [allOrOneRadioGroup selectedRow]);
				[[NSNotificationCenter defaultCenter] postNotificationName: @"ReconnectAll" object:nil userInfo:ehInfo];
				NSLog(@"ConnectToEH notif sent");
		}
		else {
			// local change for one patch
			NSLog(@"In one patch branch");
			NSString *newEventHeap;
			newEventHeap = [arrayOfEventHeaps objectAtIndex:[listOfEventHeaps selectedRow]];
			NSLog(@"The new EH name is: %@", newEventHeap);
			[currentPatch connectToEventHeap:newEventHeap];
		}
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

@end
