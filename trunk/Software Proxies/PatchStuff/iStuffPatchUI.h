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

@interface iStuffPatchUI : QCInspector
{
	IBOutlet NSTextField *displayEventHeap;
	IBOutlet NSProgressIndicator *animationConnected;
	IBOutlet NSButton *advancedOptionsButton;
	IBOutlet NSView *advancedConnectionOptions;
	IBOutlet NSTableView *listOfEventHeaps;
	IBOutlet NSMatrix *allOrOneRadioGroup;
	IBOutlet NSButton *performConnection;
	IBOutlet NSButton *listenToEverything;
	IBOutlet NSTextField *proxyIDTextField;
	
	NSMutableArray *arrayOfEventHeaps; // serves as the data source for the NSTableView.
	BOOL allowRowEdit;

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


// ********* Interface Builder Actions **************
- (IBAction)connectToEventHeap:(id)sender;
- (IBAction)disconnectFromEventHeap:(id)sender;
- (IBAction)showAdvancedOptions:(id)sender;
- (IBAction)enableListenToEverything:(id)sender;
- (IBAction)addEventHeap:(id)sender;
- (IBAction)removeEventHeap:(id)sender;
- (IBAction)changeProxyName:(id)sender;

@end
