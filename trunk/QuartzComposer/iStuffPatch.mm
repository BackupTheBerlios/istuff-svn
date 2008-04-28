//
//  iStuffPatch.mm
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//
// This is an abstract class for the development of iStuff patches.
// Concrete patches must also supply a UI class.

#import "iStuffPatch.h"
	
@interface iStuffPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation iStuffPatch(QCInspector)

+ (Class)inspectorClassWithIdentifier:(id)fp8
{	
	return [iStuffPatchUI class];
}
@end


@implementation iStuffPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
        return nil; // Standard is 2 - nil should point out that this class is an abstraction which does not provide all the functionality
}
	
+ (BOOL)allowsSubpatches
{
        // If your patch is a parent patch, like 3D Transformation,
        // you will allow subpatches, otherwise FALSE.
	return FALSE;
}

- (void)nodeDidAddToGraph:(id)fp8{
	[super nodeDidAddToGraph:fp8];
  
	configDictionary = [NSMutableDictionary dictionaryWithContentsOfFile:[prefsFile stringByExpandingTildeInPath]];
	[configDictionary retain];

	// Set the title and notes accordingly:
	// But only if the user has not entered something yet.
	NSMutableDictionary *nodeAttributes = [self userInfo];
	if ([nodeAttributes valueForKey:@"name"] == nil)
		[nodeAttributes setValue:[self key] forKey:@"name"];

	// If the Event ID is not specified yet, generate it from the patch's name
	if ([nodeAttributes valueForKey:@"eventID"] == nil){
		[self setEventID:[nodeAttributes valueForKey:@"name"]];
	}
	
	if ([[nodeAttributes valueForKey:@"listenToEverything"] isEqualToNumber:[NSNumber numberWithInt:NSOffState]])
		[self setListenToEverything:NSOffState];
	else
		[self setListenToEverything:NSOnState];
	//if ([[nodeAttributes valueForKey:@"connectionStatus"] isEqualToString:@"connected"]) {
	//	standby = true;
	//}
	//else {
	//	standby = false;
	//}
	standby = true;
	hostName = [NSString stringWithString:[[NSHost currentHost] name]];
	[hostName retain];
	
	// Try to read the last name used from the file
	// If that fails, use the hostName

// Here seems to be an error - the part with the last Event Heap name should be reworked
//	NSMutableString *loadedEHName = [configDictionary valueForKey:@"LastEHName"];
//	if (loadedEHName != nil){
//		NSLog(@"EH Name found: %@", loadedEHName);
//		[self setEventHeapName:loadedEHName];
//		}
//	else
		//[self setEventHeapName:[NSString stringWithString:hostName]];
		[self setEventHeapName:[NSString stringWithString:@""]];

	[self setAutomaticEHConnection:true];
		
}
	
- (id)initWithIdentifier:(id)fp8 {	
	// Specify the preferences files for initial values
	prefsFile = [NSString stringWithString:@"~/Library/Preferences/QCiStuffPluginEHList.plist"];
	[prefsFile retain];
	
	advancedOptionsHidden = true; // By default. the advanced options are hidden for a new patch
	connectedToEventHeap = false;
	readyToReconnect = true;
	
	// Specify notifications to react to
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(disconnectFromCurrentEventHeap) name:@"DisconnectAll" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(manageEHConnection:) name:@"ConnectAll" object:nil];
	//[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(automaticEHConnection) name:@"NetServicesUpdate" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(connectToEventHeap) name:@"ReadyToConnect" object:nil];		
	
	// Initialize the netServiceBrowser object
	netServices = [[NSMutableArray alloc] initWithCapacity:5];
	[netServices retain];
	specifiedEventHeaps = [[NSMutableArray alloc] initWithCapacity:5];
	[specifiedEventHeaps retain];
    netServiceBrowser = [[NSNetServiceBrowser alloc] init];
	[netServiceBrowser setDelegate:self]; 	// If setDelegate is not sent, no new service will be discovered.
    [netServiceBrowser searchForServicesOfType:@"_eheap._tcp." inDomain:@""]; 
	[netServiceBrowser retain];

	eh2_init ("iStuffQuartzPlugin",[[[NSHost currentHost] name] UTF8String]);	// Names that are provided with each event posted to the heap.
	
	return [super initWithIdentifier:fp8];
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// This is where the execution of your patch happens.
        // Everything in this method gets executed once
        // per 'clock cycle', which is available in fp12 (time).
	
        // fp8 is the QCOpenGLContext*.  Don't forget to set
        // it before you start drawing.  
	
        // Read/Write any ports in here too.
		
		// Take the inport value of ProxyID for the new name.
        return TRUE;
}

- (void) manageEHConnection:(NSNotification *) notification {
	// End running threads first --> Disconnect *if necessary
	[self disconnectFromCurrentEventHeap]; // needed here, such that running threads are ended.
	NSDictionary *dict = [notification userInfo];
	NSString *newEHServerName = [NSString stringWithString:[dict valueForKey:@"newEHName"]];

	[self setEventHeapName:newEHServerName];
	[self connectToEventHeap];
}

- (void) automaticEHConnection {
	// If the connections should be automatically managed, perform this method
	if (standby) {
		if ([netServices containsObject:eventHeapName])
			[self connectToEventHeap];
		else { 
			// Connect to the first in the list
			[self setEventHeapName:[netServices objectAtIndex:0]];
			[self connectToEventHeap];
		}
		// Send a notification to update the current view
		NSMutableDictionary *connectionStatus = [[NSMutableDictionary alloc]init];
		[connectionStatus setValue:@"connected" forKey:@"connectionStatus"];
		[[NSNotificationCenter defaultCenter] postNotificationName:@"RefreshView" object:nil userInfo:connectionStatus];
	}
}
		
- (id)setup:(id)fp8 {
	// fp8 is the QCOpenGLContext
	// setup vars here
	return fp8;
}

- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *) serverName atPort:(int)port {
	// create the Event Heap instance for the client

	// first, get the Event Heap factory
	// you are not responsible of releasing the reference to it
	eh2_EventHeapFactory *factory = eh2_EventHeapFactory::cs_getInstance ();

	// then, ask the factory for creating the Event Heap client instance
	// you have the ownership of the returned object, so you have to keep it in a smart pointer
	// specify source name, event heap host (e.g., "localhost"), and default port
	// allocate memory for Event Heap client

	eh = new (eh2_EventHeapPtr);
	(*eh) = factory->createEventHeap ([sourceName cString],[serverName cString], port);
}

- (void) connectToEventHeap {
	NSLog(@"Trying to connect to Event Heap %@", eventHeapName);
	[self createEventHeap:NULL atServer:eventHeapName atPort:4535];
	connectedToEventHeap = true;
	[self startReceivingEvents];
	standby = true;
	// Prepare a notification for the UI such that the settings panel is updated
	[[self userInfo] setValue:@"connected" forKey:@"connectionStatus"];
	NSMutableDictionary *ehInfo = [NSMutableDictionary dictionaryWithObject:@"connected" forKey:@"connectionStatus"];
	[ehInfo setValue:self forKey:@"Identity"];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:self userInfo:ehInfo];	
	
	// Store the last name in the configuratin dictionary such that new instances make use of the same EH name
	[configDictionary setValue:[self ehName] forKey:@"LastEHName"];
}

- (void) disconnectFromCurrentEventHeap {
	[self stopReceivingEvents];
	connectedToEventHeap = false;
	standby = false;
}

- (void) netServiceBrowser:(NSNetServiceBrowser*)aNetServiceBrowser didFindService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
	NSLog(@"netServiceBrowser is called with %@, %@, %@", [aNetService domain], [aNetService hostName], [aNetService name]);
	NSString *formattedServiceName = [NSString stringWithString:[aNetService name]];
	NSMutableString *mServiceName = [[NSMutableString alloc] initWithCapacity:[formattedServiceName length]];
	[mServiceName setString:formattedServiceName];
	//[mServiceName replaceOccurrencesOfString:@"_" withString:@"." options:0 range:NSMakeRange(0, [formattedServiceName length])];
	NSString *serviceName = [NSString stringWithString:mServiceName];
	NSLog(@"netServiceBrowser is called with %@", serviceName);
	
	if ([hostName isEqualToString:serviceName])
		// the localhost should always be displayed at the top of the list
		[netServices insertObject:serviceName atIndex:0];
	else
		// Other names are appended to the list
		[netServices addObject:serviceName];

	if (standby && [serviceName isEqual: eventHeapName]) {
		// In case that the conncetion was lost and the patch is in standby mode --> reconnect if the 
		// service was restarted
		[self connectToEventHeap]; 
	}
	
	// Wait to notify until the detection process is completed
	if (!moreComing) { 
		[self sendEHSListUpdate:nil]; 
		// This notification initiates the reloading the list containing the detected Event Heaps
		[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:nil];
		// Automatically connect the new patch to an Event Heap as soon as available (standard)
		// If the user manually disconnected the patch, no automatic connection will be established
		[self automaticEHConnection]; 
	}
}

- (void) netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
	// Construction of the fully qualified name
	NSString *serviceName = [NSString stringWithString:[aNetService name]];
	NSString *serviceDomain = [NSString stringWithString:[aNetService domain]];
    NSEnumerator *enumerator = [netServices objectEnumerator];
	NSString *currentNetServiceName;
	
	// Find the removed service in the list and remove it
	while (currentNetServiceName = [enumerator nextObject]) {
        if ([currentNetServiceName isEqual:serviceName]) {
            [netServices removeObject:currentNetServiceName];
            break;
        }
    }
	
	NSMutableDictionary *connectionStatus = nil;
	// In case that the patch was connected to the removed Event Heap go to standby mode
	if ( ([serviceName isEqual:eventHeapName]) && (standby) ){
		connectedToEventHeap = false;
		// post a notification that signifies that the view has to be updated
		connectionStatus = [NSMutableDictionary dictionaryWithObject:@"standby" forKey:@"connectionStatus"];
		[[NSNotificationCenter defaultCenter] postNotificationName:@"RefreshView" object:nil userInfo:connectionStatus];
		[self stopReceivingEvents];
	}
	
	// Wait to notify until the detection process is completed
    if (!moreComing) 
		// Send a notification to update the lists and the view
		[self sendEHSListUpdate:connectionStatus];
}

- (void)sendEHSListUpdate:(NSDictionary *) connectionStatus {
    [[NSNotificationCenter defaultCenter] postNotificationName:@"NetServicesUpdate" object:nil userInfo:nil];
}

- (void) nodeWillRemoveFromGraph{
	// This method gets called directly when a node is removed
	// instead of dealloc which is only invoked when Quartz Composer quits
	[self disconnectFromCurrentEventHeap];
	[netServiceBrowser release];
	[netServices release];
	[specifiedEventHeaps release];
	[hostName release];
	[eventHeapName release];
	[prefsFile release];
	[configDictionary release];
	[[NSNotificationCenter defaultCenter] removeObserver:self];

	[super nodeWillRemoveFromGraph];
}

-(void) dealloc{
	eh2_finalize ();
	[super dealloc];
}

// *********** Methods for changing instance variables ******************
-(void) setEventHeapName:(NSString *)newEventHeapName{
	[eventHeapName release];
	eventHeapName = [NSString stringWithString:newEventHeapName];
	[eventHeapName retain];
}

- (void) setEventID:(NSString *) name {
	[[self userInfo] setValue:name forKey:@"EventID"];
}

-(void) setAdvancedOptionsHidden:(BOOL) flag
{
	advancedOptionsHidden = flag;
}

- (void) setRadioButtonIndex:(int)index{
	radioButtonIndex = index;
}

- (void) setListenToEverything:(int)state{
	listenToEverything = state;
	[[self userInfo] setValue:[NSNumber numberWithInt:state] forKey:@"listenToEverything"];
}

// ********** Methods providing instance variables ************
- (NSMutableArray *) foundEventHeaps{
	return netServices;
}

-(NSString *) ehName {
	return [NSString stringWithString:eventHeapName];
}

-(BOOL) advancedOptionsHidden
{
	return advancedOptionsHidden;
}

-(BOOL) suspended {
	return standby;
}

- (int) radioButtonIndex {
	return radioButtonIndex;
}

- (int) listenToEverything {
	return (int) listenToEverything;
}

- (NSMutableString* ) eventID {
	return 	[[self userInfo] valueForKey:@"EventID"];
}

- (NSMutableArray *) specifiedEventHeaps {
	return specifiedEventHeaps;
}

- (NSMutableDictionary *) configuration {
NSLog(@"configuration");
//	NSMutableDictionary *dict=  ([NSMutableDictionary dictionaryWithContentsOfFile:[prefsFile stringByExpandingTildeInPath]]);
//	NSLog(@"What was loaded?: %@",dict);
	return ([NSMutableDictionary dictionaryWithContentsOfFile:[prefsFile stringByExpandingTildeInPath]]);
}

- (void) saveConfiguration {
  [configDictionary setValue:specifiedEventHeaps forKey:@"userSpecifiedEventHeaps"];
  if ([configDictionary writeToFile:[prefsFile stringByExpandingTildeInPath] atomically:YES])
	NSLog(@"File was successfully written: %@", configDictionary);
  else
	NSLog(@"Error writing file!!! %@ PRINT CONFIG:%@", [prefsFile stringByExpandingTildeInPath] ,configDictionary);
}

- (NSMutableArray *) storedEventHeaps {
	return [configDictionary valueForKey:@"userSpecifiedEHList"];
}

// This method is needed for Provider patches
- (void) startReceivingEvents
{

}

// This method is needed for Provider patches
- (void) stopReceivingEvents
{
}

// This method is needed for Provider patches

- (void) waitForEvents
{
	// thread waiting for EH events, so we won't block the recognition system
	// the function call (*eh)->waitForEvent is blocking !
	// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
	// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
}

-(NSString *) prefsFile {
	return prefsFile;
}

- (BOOL) automaticConnection {
	return automaticEHConnection;
}

- (void) setAutomaticEHConnection:(BOOL) flag {
	automaticEHConnection = flag;
	if (flag)
		[[self userInfo] setValue:@"true" forKey:@"automaticConnectionManagement"];
	else
		[[self userInfo] setValue:@"false" forKey:@"automaticConnectionManagement"];
}

- (BOOL) connected
{
	return connectedToEventHeap;
}

- (BOOL) standby
{
	return standby;
}

@end