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
	//NSLog (@"In initialize");
	[super nodeDidAddToGraph:fp8];
//	NSString *providedID = [[[self description] componentsSeparatedByString:@"_"] objectAtIndex:1];
	//[proxyName appendString:[[providedID componentsSeparatedByString:@"\""] objectAtIndex:0]];
	//if ([[inputProxyID stringValue] isEqualToString:@""]) // if the port has no value, insert the standard ProxyID
	//	[inputProxyID setStringValue:proxyName]; // <Listen To Everything> indicates that the patch processes every
	
																													// of the corresponding kind.
	//[inputProxyID setStringValue:[self key]];
	proxyName = [NSString stringWithString:[self key]];
	[proxyName retain];
	
	// Set the title and notes accordingly:
	// But only if the user has not entered something yet.
	NSMutableDictionary *nodeAttributes = [self userInfo];
	if ([nodeAttributes valueForKey:@"name"] == nil)
		[nodeAttributes setValue:[self key] forKey:@"name"];
	if ([nodeAttributes valueForKey:@"eventID"] == nil){
		eventID = [NSMutableString stringWithString:[nodeAttributes valueForKey:@"name"]];
		[nodeAttributes setValue:eventID forKey:@"eventID"];
	}
	else {file://localhost/Users/rene/Desktop/Installer%20Packages/iStuffLibrariesInstaller.pkg/
		eventID = [nodeAttributes valueForKey:@"eventID"];
	}
	[eventID retain];
	if ([[nodeAttributes valueForKey:@"listenToEverything"] isEqualToNumber:[NSNumber numberWithInt:NSOffState]])
		[self setListenToEverything:NSOffState];
	else
		[self setListenToEverything:NSOnState];
	if ([[nodeAttributes valueForKey:@"connectionStatus"] isEqualToString:@"connected"]) {
		standby = true;
	}
	else {
		standby = false;
	}
	hostName = [NSString stringWithString:[[NSHost currentHost] name]];
	[hostName retain];
	if ([nodeAttributes valueForKey:@"LastEHName"] == nil) {
	// Try to read the last name used from the file
	// If that fails, use the hostName
	NSMutableString *loadedEHName = [NSKeyedUnarchiver unarchiveObjectWithFile:[self lastEHNameFile]];
//	[[currentPatch specifiedEventHeaps] removeAllObjects];
		if (loadedEHName != nil)
			[self setEventHeapName:loadedEHName];
		else
			//[self setEventHeapName:[NSString stringWithString:hostName]];
			[self setEventHeapName:[NSString stringWithString:@""]];
	}
	else {
		[self setEventHeapName:[nodeAttributes valueForKey:@"LastEHName"]];
	}			
/* Patches should automatically connect

	if ([nodeAttributes valueForKey:@"automaticConnectionManagement"] == nil) {
	// Try to read the last name used from the file
	// If that fails, use the hostName
	NSNumber *flag = [NSKeyedUnarchiver unarchiveObjectWithFile:automaticConnectionFile];
	//NSLog(@"AutoConMan %i", [flag boolValue]);

//	[[currentPatch specifiedEventHeaps] removeAllObjects];
	//	if (flag != nil)
			automaticEHConnection = [flag boolValue];
			
	//}
	//else {
	//NSLog(@"No values found");
	//automaticEHConnection = true;
	}
	else if ([[nodeAttributes valueForKey:@"automaticConnectionManagement"] isEqualToString:@"true"]) {
		NSLog(@"It was true");
		[self setAutomaticEHConnection:true];
	}
	else{
	NSLog(@"It was false");
		[self setAutomaticEHConnection:false];		
	}
	*/
	
	[self setAutomaticEHConnection:true];
	
//	NSLog(@"XML Attributes:%@", [[[self xmlAttributes] valueForKey:@"nodeAttributes"] valueForKey:@"description"]);
	//	NSLog(@"IN ADD TO GRAPH W I: %@",[ [self key] description]);
	//	NSLog(@"IN ADD TO GHRraph W I: %@", [[self userInfo] description]);
	
}
	
- (id)initWithIdentifier:(id)fp8
{	
	prefsFile = [NSString stringWithString:@"/Users/rene/Library/Preferences/QCiStuffPluginEHList.ehl"];
	lastEHNameFile = [NSString stringWithString:@"/Users/rene/Library/Preferences/QCiStuffPluginLastEHName.ehn"]; 
	automaticConnectionFile = [NSString stringWithString:@"/Users/rene/Library/Preferences/QCiStuffPluginAutomaticConnectionSettig.ehn"]; 

	[prefsFile retain];
	[lastEHNameFile retain];
	[automaticConnectionFile retain];
	advancedOptionsHidden = true;
	//standby = true;
	connectedToEventHeap = false;
	char domainname[1024];
	getdomainname( &domainname[0], sizeof(domainname) );
	//printf( "Domainname=%s\n", &domainname[0] );
	domainName = [NSString stringWithUTF8String:domainname];
	[domainName retain];
	// Register object with Notification Center

	//NSLog(@"DomainName variable: %@", domainName); 
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(disconnectFromCurrentEventHeap) name:@"DisconnectAll" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(manageEHConnection:) name:@"ConnectAll" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(automaticEHConnection) name:@"NetServicesUpdate" object:nil];
	
	netServices = [[NSMutableArray alloc] initWithCapacity:5];
	[netServices retain];
	specifiedEventHeaps = [[NSMutableArray alloc] initWithCapacity:5];
	[specifiedEventHeaps retain];
    netServiceBrowser = [[NSNetServiceBrowser alloc] init];
	// If setDelegate is not sent, no new service will be discovered.
	[netServiceBrowser setDelegate:self];
    [netServiceBrowser searchForServicesOfType:@"_eheap._tcp." inDomain:@""]; 
	[netServiceBrowser retain];
			// DHCP is recommended! Then the EH service returns reasonable service and host names.
			// Make sure that IPv4 is used. And ipv6 is turned off
			// A NameServer must run if different OS are to be intermingled.

	eh2_init ("iStuffQuartzPlugin","localhost");//[hostName UTF8String]);	// Names that are provided with each event posted to the heap.
	return [super initWithIdentifier:fp8];
}
		
- (void) manageEHConnection:(NSNotification *) notification {
NSLog (@"In Manage Connection - NOTIFICATIION: %@", notification);
	//if (notification != nil) {
	//	NSLog(@"In manageConnection and disconnecting in: %@",self);
		[self disconnectFromCurrentEventHeap]; // needed here, such that running threads are ended.
		NSDictionary *dict = [notification userInfo];
		NSString *newEHServerName = [NSString stringWithString:[dict valueForKey:@"newEHName"]];
		//NSLog(@"In MANAGE CONNECTION: %@", newEHServerName);
		// Check wether the specified host is reachable at all
//		NSHost *hostWithName = [NSHost hostWithName:newEHServerName];
//		NSHost *hostWithAddress = [NSHost hostWithAddress:newEHServerName];
		// The user can specify both, a name and a network address.
		// This cannot be checked, but therefore both initializations were made.
		// If both of the following checks reveal null pointers, that means
		// that the specified hosts are not reachable
//		if ( ([hostWithName addresses] != nil) || ([hostWithAddress names] != nil) ) {
			[self setEventHeapName:newEHServerName];
			[self connectToEventHeap];
		//}
	//}
}

- (void) automaticEHConnection {
	NSLog(@"RECEIVED UPDATE MESSAGE");
	// If the connections should be automatically managed, perform this method
	if ( (!connectedToEventHeap) && (automaticEHConnection) ) {
		if ([netServices containsObject:eventHeapName])
			[self connectToEventHeap];
		else { // Connect to the first in the list
			[self setEventHeapName:[netServices objectAtIndex:0]];
			[self connectToEventHeap];
		}
		NSLog(@"Established an automaitc connection");
	}
}
		
- (id)setup:(id)fp8
{

//	NSLog(@"IN SETUP W I: %@",[ [self key] description]);
	//	NSLog(@"INSETUP W I: %@", [[self userInfo] description]);
  // fp8 is the QCOpenGLContext
	// setup vars here
        return fp8;
}

// create the Event Heap instance for the client
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *) serverName atPort:(int)port
{
	// first, get the Event Heap factory
	// you are not responsible of releasing the reference to it
	eh2_EventHeapFactory *factory = eh2_EventHeapFactory::cs_getInstance ();
	// then, ask the factory for creating the Event Heap client instance
	// you have the ownership of the returned object, so you have to keep it in a smart pointer
	// specify source name, event heap host (e.g., "localhost"), and default port
	// allocate memory for Event Heap client

	eh = new (eh2_EventHeapPtr);

	//(*eh) = factory->createEventHeap (NULL, "localhost", 4535);
	//NSLog(@"VALUE FOR THE NEW CONNECTION: %@", serverName);
	//if ([serverName isEqualToString:@"localhost.local."])
//		(*eh) = factory->createEventHeap ([sourceName cString],"localhost", port);	
	//else
		//(*eh) = factory->createEventHeap ([sourceName cString],[serverName cString], port);
	//	NSLog(@"Before creating EH pointer:%@",self);
		(*eh) = factory->createEventHeap ([sourceName cString],[serverName cString], port);
}

- (void) connectToEventHeap {
//	sleep(1);
	//[self stopReceivingEvents];
	[self createEventHeap:NULL atServer:eventHeapName atPort:4535];
	connectedToEventHeap = true;

	[self startReceivingEvents];
	standby = true;
	[[self userInfo] setValue:@"connected" forKey:@"connectionStatus"];
	NSMutableDictionary *ehInfo = [NSMutableDictionary dictionaryWithObject:@"connected" forKey:@"connectionStatus"];
	[ehInfo setValue:self forKey:@"Identity"];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:self userInfo:ehInfo];	
	
	// Store the last name in a file such that new instances make use of the same EH name
	[NSKeyedArchiver archiveRootObject:[self ehName] toFile:[self lastEHNameFile]];

	
	
	//[eventHeapName retain];
		//sleep(1); // Also prevents crash if proxy is still running but only the event heap crashed
}


- (void) disconnectFromCurrentEventHeap {
	//eh = nil;
	[self stopReceivingEvents];
	connectedToEventHeap = false;
	standby = false;
	//NSMutableDictionary *ehInfo = [NSMutableDictionary dictionaryWithObject:@"disconnected" forKey:@"connectionStatus"];
	//[ehInfo setValue:self forKey:@"Identity"];
//	[[self userInfo] setValue:@"disconnected" forKey:@"connectionStatus"];
//	[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:nil userInfo:ehInfo];
}
- (void) netServiceBrowser:(NSNetServiceBrowser*)aNetServiceBrowser didFindService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
//NSLog(@"In didFindService %@ and domain:%@", [aNetService name], [aNetService domain]);
	// Construction of the fully qualified name
	NSString *serviceName = [NSString stringWithString:[aNetService name]];
/*	NSString *serviceDomain = [NSString stringWithString:[aNetService domain]];
	NSMutableString *fullServerName = [NSMutableString stringWithString:serviceName];
	if (! [[aNetService domain] isEqualToString:@""]) {
		[fullServerName appendString:@"."];
		[fullServerName appendString:serviceDomain];	
	}
*/	
	if ([hostName isEqualToString:serviceName])
		//[netServices insertObject:fullServerName atIndex:0];
		[netServices insertObject:serviceName atIndex:0];
	else
		[netServices addObject:serviceName];

	/*if ((![self connected]) && !standby && ([eventHeapName isEqualToString:serviceName])){
		[self setEventHeapName: serviceName];
		[self connectToEventHeap]; // Not connected, not standby --> Connect to localhost if possible. Otherwise wait.
	} */
//else
	if (standby && [serviceName isEqual: eventHeapName]) {
		[self connectToEventHeap]; // reconnect.
	}
	//NSLog(@"In didFindService %@ %i", [aNetService name], [[aNetService addresses] count]);

    if (!moreComing) [self sendEHSListUpdate];
//NSLog(@"NEW VALUES in didFindService %@ and domain:%@", serviceName, serviceDomain);
[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:nil]; // That lets the view reload the list data
}

- (void) netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
	// Construction of the fully qualified name
	NSString *serviceName = [NSString stringWithString:[aNetService name]];
	NSString *serviceDomain = [NSString stringWithString:[aNetService domain]];
	NSMutableString *fullServerName = [NSMutableString stringWithString:serviceName];
	if (! [[aNetService domain] isEqualToString:@""]) {
		[fullServerName appendString:@"."];
		[fullServerName appendString:serviceDomain];	
	}

    NSEnumerator *enumerator = [netServices objectEnumerator];
	NSString *currentNetServiceName;

	while (currentNetServiceName = [enumerator nextObject]) {
        if ([currentNetServiceName isEqual:serviceName]) {
            [netServices removeObject:currentNetServiceName];
            break;
        }
    }
	if ( ([serviceName isEqual:eventHeapName]) && (standby) ){
		connectedToEventHeap = false;
		//standby = true;
		// post a notification that signifies that the view has to be uodated
		NSMutableDictionary *ehInfo = [NSMutableDictionary dictionaryWithObject:@"standby" forKey:@"connectionStatus"];
		[ehInfo setValue:self forKey:@"Identity"];
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHListChange" object: nil userInfo:ehInfo];
		[self stopReceivingEvents];
	}
	else {
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHListChange" object: nil userInfo:nil];
	}
		//NSLog(@"In didRemoveService: %@", [aNetService name]);
    if (!moreComing) [self sendEHSListUpdate];
}

- (void)sendEHSListUpdate
{
   // NSDictionary *message = [NSDictionary dictionaryWithObject:netServices
     //                                                  forKey:@"EventHeapServiceList"];

    //[[NSNotificationCenter defaultCenter] postNotificationName:@"ESEventHeapServiceListUpdate" object:nil userInfo:message];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"NetServicesUpdate" object:nil userInfo:nil];
			NSLog(@"JUST SENT AN EVENT");
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

- (BOOL) connected
{
	return connectedToEventHeap;
}

- (BOOL) standby
{
	return standby;
}

- (void) nodeWillRemoveFromGraph{
//- (void)dealloc
	[netServiceBrowser release];
	[netServices release];
	[specifiedEventHeaps release];
	[hostName release];
	[eventHeapName release];
	[proxyName release];
	[eventID release];
	[prefsFile release];
	[lastEHNameFile release];
	[automaticConnectionFile release];
	[[NSNotificationCenter defaultCenter] removeObserver:self];

	// Now disconnect from the Event Heap
	//delete eh;
	//eh2_finalize (); // This line actually causes crashes when deleting connected patches without a pause. Maybe it can be removed?
	NSLog(@"All operations in NODEWILL REMOVE were finished");
//	[super dealloc];
	[super nodeWillRemoveFromGraph];
}

-(void) dealloc{
	NSLog(@"IN ISTUFFPATCH DEALLOC");
	eh2_finalize ();
	[super dealloc];
}

- (NSMutableArray *) foundEventHeaps{
	return netServices;
}

-(void) setEventHeapName:(NSString *)newEventHeapName{
	[eventHeapName release];
	  eventHeapName = [NSString stringWithString:newEventHeapName];
	[eventHeapName retain];
	//NSLog(@"IN SET EVENT HEAP NAME:%@ and %@",  newEventHeapName, eventHeapName);
}

-(NSString *) ehName {
	return [NSString stringWithString:eventHeapName];
}

-(BOOL) advancedOptionsHidden
{
	return advancedOptionsHidden;
}

-(void) setAdvancedOptionsHidden:(BOOL) flag
{
	advancedOptionsHidden = flag;
}
-(BOOL) suspended {
	return standby;
}

- (void) setRadioButtonIndex:(int)index{
	radioButtonIndex = index;
}

- (void) setListenToEverything:(int)state{
	listenToEverything = state;
	[[self userInfo] setValue:[NSNumber numberWithInt:state] forKey:@"listenToEverything"];

	//if (state == 1)
//		[eventID setString:@"<Listen To Everything>"];
	//else
	//	[inputProxyID setStringValue:proxyName];
}

- (int) radioButtonIndex {
	return radioButtonIndex;
}

- (int) listenToEverything {
	return (int) listenToEverything;
}

- (NSString* ) proxyName {
	//return proxyName;
	return eventID;
}

- (NSMutableString* ) eventID {
	return eventID;
}

- (void) setEventID:(NSString *) name {
	[eventID release];
	[eventID setString: name];
	[eventID retain];
	//[inputProxyID setStringValue:name];
}

- (NSMutableArray *) specifiedEventHeaps {
	return specifiedEventHeaps;
}

// This method is needed for Provider patches
- (void) startReceivingEvents
{

}

- (void) stopReceivingEvents
{
}

// thread waiting for EH events, so we won't block the recognition system
// the function call (*eh)->waitForEvent is blocking !
// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
- (void) waitForEvents
{
// This method has to be implemented in a subclass.
}

-(NSString *) prefsFile {
	return prefsFile;
}

-(NSString *) lastEHNameFile {
	return lastEHNameFile;
}

- (BOOL) automaticConnection {
	return automaticEHConnection;
}

- (void) setAutomaticEHConnection:(BOOL) flag {
	automaticEHConnection = flag;
//	[NSKeyedArchiver archiveRootObject:[NSNumber numberWithBool:flag] toFile:automaticConnectionFile];
	// And store the information inside the User Info of the node (For restoring purposes)
	if (flag)
		[[self userInfo] setValue:@"true" forKey:@"automaticConnectionManagement"];
	else
		[[self userInfo] setValue:@"false" forKey:@"automaticConnectionManagement"];
}

@end