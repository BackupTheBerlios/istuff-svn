//
//  iStuffPatchUI.h
//  QCiStuff
//
//  Created by René Reiners in Feb/March 2006.
//  Copyright 2006 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "QCInspector.h"
#import "iStuffPatch.h"
#import "CustomTableView.h"

@interface iStuffPatchUI : QCInspector
{
	IBOutlet NSTextField *displayConnectionStatus;
	IBOutlet NSProgressIndicator *animationConnected;
	IBOutlet NSButton *advancedOptionsButton;
	IBOutlet NSBox *advancedConnectionOptions;
//	IBOutlet NSTableView *listOfEventHeaps;
	IBOutlet NSTableView *listOfEventHeaps;
	IBOutlet CustomTableView *customListOfEventHeaps;
	IBOutlet NSMatrix *allOrOneRadioGroup;
	IBOutlet NSButton *performConnection;
	IBOutlet NSButton *listenToEverything;
	IBOutlet NSTextField *proxyIDTextField;
	IBOutlet NSTextField *displayEventHeapName;
	IBOutlet NSButton *addEventHeapButton;
	IBOutlet NSButton *removeEventHeapButton;
	IBOutlet NSButton *toggleAutomaticConnectionManagement;
	
	NSMutableArray *arrayOfEventHeaps; // serves as the data source for the NSTableView.
	BOOL allowRowEdit;
	BOOL discoveredEHListWasSelected;
	BOOL discoveredEventHeapsFirst;
	BOOL specifiedEventHeapsFirst;
	BOOL firstCall;
	int selectedList; // -1= no list selected 0=discovered EH list selected
						// 1 = user-specified EH list selected
						

}
// ********* QCInspector standard methods that are extended *********
+ (id)viewNibName;
- (id)init;
- (void)setupViewForPatch:(id)fp8; // load data from the model (QCPatch)
- (void) resetView; // store data in the model (QCPatch)

// ********* NSTableView management *****************
-(int)numberOfRowsInTableView: (NSTableView *) Table;
-(id)tableView:(NSTableView *) Table
	objectValueForTableColumn:(NSTableColumn *) Column
	row: (int) Row;

// ************Methods to change the display state *******
-(void) connectedState;
-(void) standbyState;
-(void) disconnectedState;

// ********* Interface Builder Actions **************
- (IBAction)connectToEventHeap:(id)sender;
- (IBAction)disconnectFromEventHeap:(id)sender;
- (IBAction)showAdvancedOptions:(id)sender;
- (IBAction)enableListenToEverything:(id)sender;
- (IBAction)toggleEHConnectionManagement:(id)sender;
- (IBAction)addEventHeap:(id)sender;
- (IBAction)removeEventHeap:(id)sender;
- (IBAction)changeProxyName:(id)sender;

@end
